#include <QCoreApplication>
#include "frame_processor.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
	FrameProcessor p;
    return a.exec();
}
