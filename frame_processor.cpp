#include "frame_processor.h"

FrameProcessor::FrameProcessor()
{

	connect(&net, SIGNAL(frameIsReady(QByteArray, int)), this, SLOT(prepareData(QByteArray, int)));
	connect(this, SIGNAL(answer()), &net, SLOT(answer()));
	left = Mat(480, 640, CV_8UC1);
	right = Mat(480, 640, CV_8UC1);
	out = Mat(480, 640, CV_8UC3);
	pv = new PointViewer(640*480);
	cv::VideoCapture cap(0);
	while (1)
	{
		cap >> left;
		dev.process(left.data, left.data, pv->data);
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