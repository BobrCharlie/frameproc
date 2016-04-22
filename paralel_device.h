#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <CL/cl.hpp>
#include <vector>
#include <map>

class ParalelDevice{
	int devId;

	int width, height, size, defaultHeight=480, defaultWidth=640;

	std::string kernelFile, defaultKernelFile="kernels.cl";
	cl::Kernel *defaultKernel;
	cl::CommandQueue *defaultDeviceQueue;

	int err;
	
	
	
	void init();
	void printInfo();
public:
	ParalelDevice();
	ParalelDevice(std::string _kernelFile, int _width, int _height);
	void process(cl_uchar* inLeft, cl_uchar* inRight, void* out);
};