 kernel void gradient(global const char* left, global const char* right, global float* output){
	
	
	int lx=get_local_id(0);
	int ly=get_local_id(1);
	int gx=get_group_id(0);
	int gy=get_group_id(1);
	int lsx=get_local_size(0);
	int lsy=get_local_size(1);
	int y=lsy*gy+ly;
	int x=lsx*gx+lx;
	int offset=y*640+x;

	char v=left[offset];
	char vd[4]={v,v,v,v};


	
	output[offset*8]	= (float)x;
	output[offset*8+1]	= (float)y;
	output[offset*8+2]	= 0.f;
	output[offset*8+3]	= 0.f;
	output[offset*8+4]	= *(float*)&vd;
	
	
}