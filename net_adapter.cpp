#include "net_adapter.h"

NetAdapter::NetAdapter(){
	connect(&socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

	socket.connectToHost(QHostAddress::LocalHost, 8080);

	dataSize = 0;
}

void NetAdapter::readyRead(){

	if (!dataSize){
		memcpy(&dataSize, socket.read(4).data(), 4);
		memcpy(&frameIndex, socket.read(4).data(), 4);
	}

	if (socket.bytesAvailable() < dataSize)
		return;

	QByteArray buf;
	buf.resize(dataSize);
	buf=socket.read(dataSize);

	emit frameIsReady(buf, frameIndex);

	dataSize = 0;

}

void NetAdapter::answer()
{
	QByteArray b;
	b.resize(4);
	memcpy(b.data(), &frameIndex, 4);
	socket.write(b);
}

NetAdapter::~NetAdapter(){
	socket.close();
}