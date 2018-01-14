#ifndef QQTUDPSERVER_H
#define QQTUDPSERVER_H

#include <QUdpSocket>
#include "qqtudpprotocol.h"
#include "qqt-local.h"
#include "qqtcore.h"
#include <QThread>

/*QQtSocketUdpServer和QQtSocketUdpClient功能相同，实现方法不同。*/
class QQtSocketUdpServer : public QUdpSocket
{
    Q_OBJECT
public:
    explicit QQtSocketUdpServer ( QObject* parent = nullptr );
    virtual ~QQtSocketUdpServer();

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

private slots:
    void domainHostFound();
    void socketStateChanged ( QAbstractSocket::SocketState );
    void socketErrorOccured ( QAbstractSocket::SocketError );
    void socketConnected();
    void socketDisconnect();
    void updateProgress ( qint64 bytes );
    qint64 slotWriteDatagram ( const QNetworkDatagram& datagram );

private:
    /*默认情况下，就可以发送数据了，在协议里发送。*/
    /*只有启动了监听才能进行接收，而且需要绑定本地IP、端口*/
    /*必须在安装协议之后调用，否则崩溃*/
    void startListening();
    /*在虚构函数里调用了，客户不调用没关系*/
    void stopListening();

signals:
    void signalRunListening();
private slots:
    void slotRunListening();

private:
    QQtUdpProtocol* m_protocol;
    QThread* m_thread;
};

#endif // QQTUDPSERVER_H
