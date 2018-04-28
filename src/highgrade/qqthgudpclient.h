#ifndef QQTHGUDPCLIENT_H
#define QQTHGUDPCLIENT_H

#include <QUdpSocket>
#include "qqthgprotocolmanager.h"
#include "qqt-local.h"
#include "qqtcore.h"

/*
 * Udp通信客户端
 *
 * 和服务器操作区别：服务器需要绑定本地端口。
 *
 * 默认情况下，就可以接收发送数据了。在协议里处理接收、发送。
 * 只有绑定本地IP、端口才能进行接收
 */
class QQTSHARED_EXPORT QQtHgUdpClient : public QUdpSocket
{
    Q_OBJECT
public:
    explicit QQtHgUdpClient ( QObject* parent = nullptr );
    virtual ~QQtHgUdpClient() {}

    void installProtocolManager ( QQtHgProtocolManager* stackGroup );
    void uninstallProtocolManager ( QQtHgProtocolManager* stackGroup );
    QQtHgProtocolManager* installedProtocolManager();

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
    QQtHgProtocolManager* m_protocolManager;
};

#endif // QQTUDPCLIENT_H
