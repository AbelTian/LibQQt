#ifndef QQTUDPCLIENT_H
#define QQTUDPCLIENT_H

#include <QUdpSocket>
#include "qqtprotocol.h"
#include "qqt-local.h"
#include "qqtcore.h"

#define QT_VERSION_DATAGRAM QT_VERSION_CHECK(5,8,0)

#if QT_VERSION > QT_VERSION_DATAGRAM
#include <QNetworkDatagram>
#endif

/*
 * Udp通信客户端
 *
 * 和服务器操作区别：服务器需要绑定本地端口。
 *
 * 默认情况下，就可以接收发送数据了。在协议里处理接收、发送。
 * 只有绑定本地IP、端口才能进行接收
 *
 */
class QQTSHARED_EXPORT QQtUdpClient : public QUdpSocket
{
    Q_OBJECT
public:
    explicit QQtUdpClient ( QObject* parent = nullptr );
    virtual ~QQtUdpClient() {}

    void setServer ( QString ip, quint16 port ) {
        mHostAddress = QHostAddress ( ip );
        mPort = port;
    }
    void getServer ( QString& ip, quint16& port ) {
        ip = mHostAddress.toString();
        port = mPort;
    }

    void setServerAddress ( const QHostAddress& address, quint16& port ) {
        mHostAddress = address;
        mPort = port;
    }

    void installProtocol ( QQtProtocol* stack );
    void uninstallProtocol ( QQtProtocol* stack );
    QQtProtocol* installedProtocol();

signals:
    void signalConnecting();
    void signalConnectSucc();
    void signalConnectFail();//
    void signalDisConnectSucc();//maybe
    void signalDisConnectFail();//
    void signalUpdateProgress ( qint64 value );
public slots:
    void slotWriteData ( const QByteArray& );

protected slots:
    virtual void readyReadData();
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

public:
    /**
     * @brief translator
     * 用于拆分和分发数据报
     * @param bytes
     */
    void translator ( const QByteArray& bytes );

protected:
    virtual void recvDatagram ( QByteArray& bytes, QHostAddress& address, quint16& port );
private:
    QQtProtocol* m_protocol;
    QHostAddress mHostAddress;
    quint16 mPort;
};

#endif // QQTUDPCLIENT_H
