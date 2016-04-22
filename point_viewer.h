#include <QObject>
#include <boost/thread/thread.hpp>
#include <pcl/common/common_headers.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/point_types.h>
class PointViewer: public QObject{
	Q_OBJECT
private:
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloudptr;
	pcl::PointCloud<pcl::PointXYZRGB> cloud;
	int size;
	
public:
	PointViewer();
	~PointViewer();
	PointViewer(int size);
	void* data;
public slots:
	void init();
	void update();

};