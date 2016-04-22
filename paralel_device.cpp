#include "paralel_device.h"
ParalelDevice::ParalelDevice(){
	kernelFile = defaultKernelFile;
	width = defaultWidth;
	height = defaultHeight;
	init();
}

ParalelDevice::ParalelDevice(std::string _kernelFile, int _width, int _height){
	kernelFile = _kernelFile;
	width = _width;
	height = _height;
	init();
}

void ParalelDevice::init(){
	printInfo();
	size = width*height;
	std::ifstream file(kernelFile);
	std::string programCode(std::istreambuf_iterator<char>(file), (std::istreambuf_iterator<char>()));
	
	
	cl::Program program(programCode);
	program.build();
	cl_int buildErr;
	//program.getBuildInfo(cl::Device::getDefault());
	
	defaultDeviceQueue=new cl::CommandQueue(cl::Context::getDefault(), cl::Device::getDefault());
	
	defaultKernel = new cl::Kernel(program, "gradient", &err);
}
void ParalelDevice::printInfo(){
	std::cout << "work group"<<cl::Device::getDefault().getInfo<CL_DEVICE_MAX_WORK_GROUP_SIZE>()<<std::endl;
	std::cout << "compute units"<<cl::Device::getDefault().getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>() << std::endl;
	auto sizes = cl::Device::getDefault().getInfo<CL_DEVICE_MAX_WORK_ITEM_SIZES >();
	std::cout << "compute units" << sizes[0]<<":"<<sizes[1]<<":"<<sizes[2] << std::endl;
}
void ParalelDevice::process(cl_uchar* inLeft, cl_uchar* inRight, void* out){

	
	cl::Buffer leftBuffer(CL_MEM_READ_WRITE, size);
	cl::Buffer rightBuffer(CL_MEM_READ_WRITE, size);
	cl::enqueueWriteBuffer(leftBuffer, CL_TRUE, 0, size, inLeft);
	cl::enqueueWriteBuffer(rightBuffer, CL_TRUE, 0, size, inRight);
	cl::Event event;
	cl::Buffer outBuffer(CL_MEM_READ_WRITE, size*20);
	defaultKernel->setArg(0, leftBuffer);
	defaultKernel->setArg(1, rightBuffer);
	defaultKernel->setArg(2, outBuffer);
	defaultDeviceQueue->enqueueNDRangeKernel(*defaultKernel,cl::NDRange(640, 480),cl::NDRange(8,8),cl::NullRange,NULL,&event);
	enqueueReadBuffer(outBuffer, CL_TRUE, 0, size*20, out);
	
	
}
