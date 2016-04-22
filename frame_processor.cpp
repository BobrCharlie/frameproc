#include "frame_processor.h"

FrameProcessor::FrameProcessor()
{

	connect(&net, SIGNAL(frameIsReady(QByteArray, int)), this, SLOT(prepareData(QByteArray, int)));
	connect(this, SIGNAL(answer()), &net, SLOT(answer()));
	left = Mat(480, 640, CV_8UC3);
	right = Mat(480, 640, CV_8UC3);
	
	
	pv = new PointViewer(640*480);
	VideoCapture cap1(0);
	VideoCapture cap2(1);
	
	Ptr<StereoSGBM> sgbm = StereoSGBM::create(0, 16, 3);
	sgbm->setPreFilterCap(63);
	

	

	sgbm->setP1(8 * 9);
	sgbm->setP2(32 * 9);
	sgbm->setMinDisparity(0);
	sgbm->setNumDisparities(256);
	sgbm->setUniquenessRatio(10);
	sgbm->setSpeckleWindowSize(100);
	sgbm->setSpeckleRange(32);
	sgbm->setDisp12MaxDiff(1);
	sgbm->setMode(2);
	while (1)
	{
		cap1 >> left;
		cap2 >> right;

		sgbm->compute(right, left, out);
		imshow("left", left);
		imshow("right", right);
		imshow("out", out);
		waitKey(33);
		std::cout << "iteration" << std::endl;
		
	}
}

void FrameProcessor::prepareData(QByteArray data, int frameIndex)
{
	
	memcpy(left.data, data.data(), 480 * 640);
	int len = data.size();
	data = data.right(480 * 640);
	len = data.size();
	memcpy(right.data, data.data(), 480 * 640);
	flip(left, left, 0);
	flip(right, right, 0);
	
	dev.process(left.data, right.data, pv->data);

	imshow("a", left);
	pv->update();
	emit answer();
	std::cout << frameIndex << std::endl;
	
	
	
	
}