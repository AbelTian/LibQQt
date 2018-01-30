#ifndef CEDIANUDPPROTOCOL_H
#define CEDIANUDPPROTOCOL_H

#include <qqtudpprotocol.h>
#include <cedianudpmessage.h>
#include <qqtcore.h>
#include <cedianudpserver.h>

class CedianUdpProtocol : public QQtUdpProtocol
{
    Q_OBJECT
public:
    explicit CedianUdpProtocol(QObject *parent = nullptr);
    virtual ~CedianUdpProtocol() {}

    QNetworkDatagram& dataGram() { return mDG; }
    QHostAddress& address() { return mAddress; }
    qint32& port() { return mPort; }
    qint32& localPort() { return mLocalPort; }
    CedianUdpMessage& msg() { return mMsg; }

signals:
    void msgIncoming();
public slots:

    // QQtUdpProtocol interface
protected:
    virtual bool dispatcher(const QNetworkDatagram &) override;

private:
    /*发送者IP 端口 这个IP比较重要，但是在程序中没有用*/
    QHostAddress mAddress;
    qint32 mPort;
    /*这个端口是重点*/
    qint32 mLocalPort;
    CedianUdpMessage mMsg;
    QNetworkDatagram mDG;
};

/*建议空调用一次，赋值parent，进行初始化*/
CedianUdpProtocol* cedianUdpServer(QObject* parent = 0);
qint32 cedianUdpPort(int siteID, qint32* portList = 0);

#endif // CEDIANUDPPROTOCOL_H
