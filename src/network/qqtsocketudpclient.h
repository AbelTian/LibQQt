#ifndef QQTUDPCLIENT_H
#define QQTUDPCLIENT_H

#include <QUdpSocket>
#include "qqtudpprotocol.h"
#include "qqt-local.h"
#include "qqtcore.h"

/*
 * Udp通信不区分服务器和客户端，都用这个就行啊。操作区别：服务器需要绑定本地端口。
 * 默认情况下，就可以发送数据了，在协议里发送。
 * 只有绑定本地IP、端口才能进行接收
 */
class QQtSocketUdpClient : public QUdpSocket
{
    Q_OBJECT
public:
    explicit QQtSocketUdpClient ( QObject* parent = nullptr );
    virtual ~QQtSocketUdpClient() {}

    void installProtocol ( QQtUdpProtocol* stack );
    void uninstallProtocol ( QQtUdpProtocol* stack );
    QQtUdpProtocol* installedProtocol();

signals:
    void signalConnecting();
    void signalConnectSucc();
    void signalConnectFail();//
    void signalDisConnectSucc();//maybe
    void signalDisConnectFail();//
    void signalUpdateProgress ( qint64 value );
public slots:

protected slots:
    void readyReadData();
private slots:
    void domainHostFound();
    void socketStateChanged ( QAbstractSocket::SocketState );
    void socketErrorOccured ( QAbstractSocket::SocketError );
    void socketConnected();
    void socketDisconnect();
    void updateProgress ( qint64 bytes );
    qint64 slotWriteDatagram ( const QNetworkDatagram& datagram );

private:
    QQtUdpProtocol* m_protocol;
};

#endif // QQTUDPCLIENT_H
