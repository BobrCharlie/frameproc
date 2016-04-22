#include <QObject>
#include <QtNetwork>
#include <QTcpSocket>

class NetAdapter : public QObject{

	Q_OBJECT

	QTcpSocket socket;
	int collectedBytes, dataSize, frameIndex;
public:
	NetAdapter();
	~NetAdapter();

public slots:
	void readyRead();
	void answer();
signals:
	void frameIsReady(QByteArray, int);

};