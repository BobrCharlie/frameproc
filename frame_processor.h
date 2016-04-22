#include <opencv2\opencv.hpp>
#include "paralel_device.h"
#include "point_viewer.h"
#include "net_adapter.h"
 using namespace cv;

class FrameProcessor: public QObject{

	Q_OBJECT

		NetAdapter net;
		ParalelDevice dev;
		PointViewer* pv;
		Mat left, right, out;
public:
		FrameProcessor();
public slots:
		void prepareData(QByteArray data, int frameIndex);
	signals:
		void answer();
};