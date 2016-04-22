#include "point_viewer.h"

PointViewer::PointViewer(){
	
}
PointViewer::PointViewer(int _size){
	size = _size;
	init();
	
}

void PointViewer::init(){

	viewer = boost::shared_ptr<pcl::visualization::PCLVisualizer>(new pcl::visualization::PCLVisualizer("3D Viewer"));
	viewer->setBackgroundColor(0, 0, 0);
	cloudptr = pcl::PointCloud<pcl::PointXYZRGB>::Ptr(&cloud);
	pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb(cloudptr);
	viewer->addPointCloud<pcl::PointXYZRGB>(cloudptr, rgb, "sample cloud");
	viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud");
	viewer->addCoordinateSystem(1.0);
	viewer->initCameraParameters();

	
	cloud.resize(size);
	data = (void*)&cloud.points[0];
}


PointViewer::~PointViewer(){
	
}

void PointViewer::update(){
	
	viewer->spinOnce(100);
	viewer->updatePointCloud(cloudptr, "sample cloud");
	
}