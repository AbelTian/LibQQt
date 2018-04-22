#ifndef QQTUDPSERVER_H
#define QQTUDPSERVER_H

#include <QUdpSocket>
#include "qqtudpprotocol.h"
#include "qqtudpclient.h"
#include "qqt-local.h"
#include "qqtcore.h"

/*
 * Udp通信服务器
 *
 * Udp通信服务器和客户端操作区别：服务器需要绑定本地端口。
 * 区别很小。
 * 可是在服务器端，和TCP一样需要处理多个客户端通信，在这里处理。
 * 假如不处理，一个服务器会同时和多个客户端通信。
 *
 * 默认情况下，就可以接收发送数据了。在协议里处理接收、发送。
 * 只有绑定本地IP、端口才能进行接收
 */
class QQtUdpServer : public QUdpSocket
{
    Q_OBJECT
public:
    explicit QQtUdpServer ( QObject* parent = nullptr );
    virtual ~QQtUdpServer() {}

    void installProtocol ( QQtUdpProtocol* stack );
    void uninstallProtocol ( QQtUdpProtocol* stack );
    QQtUdpProtocol* installedProtocol();

    QList<QQtUdpClient*> getClientList() const {
        return m_client_list;
    }

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
    //如果有一个同名的槽，参数不同，并且被用宏控制起来，Qt编译不过。
    //Qt的元对象系统，解析信号和槽函数，不支持宏。
    //QtUdpSocket，writeDatagram不是个槽。
    qint64 slotWriteDatagram ( const QByteArray& datagram,
                               const QHostAddress& host, quint16 port );

private:
    QQtUdpProtocol* m_protocol;
    QList<QQtUdpClient*> m_client_list;
};

#endif // QQTUDPSERVER_H
