/**************************************************
 * QQtSocketTcpClient
 * 在一个工程当中仅仅存在一个实例，通过调用QQtSocketTcpClient实现。
 **************************************************/
#ifndef QQT_CLIENT_H
#define QQT_CLIENT_H

#include <QTcpSocket>
#include "QStringList"
#include "qqtprotocol.h"
#include "qqt-local.h"
#include "qqtcore.h"

#define QQT_TCP_SOCKET 0
#define QQT_SOCKET 1
#define QQT_THREAD 0
#define _TCP_BLOCKDATA_SIZE                    0x400
#define _TCP_RECVBUFF_SIZE                      0x800

/**
 * @brief 客户端决定和协议的交互关系;只跟协议打交道；
 */
class QQTSHARED_EXPORT QQtSocketTcpClient : public QTcpSocket
{
    Q_OBJECT
public:
    explicit QQtSocketTcpClient ( QObject* parent = 0 );
    virtual ~QQtSocketTcpClient();

    void SetServerIPAddress ( QStringList ip ) { m_serverIP = ip; }
    void SetServerPort ( quint32 p = 7079 ) { m_PORT = p; }

    void installProtocol ( QQtProtocol* stack );
    void uninstallProtocol ( QQtProtocol* stack );
    QQtProtocol* installedProtocol();

    void SendConnectMessage();
    int SendDisConnectFromHost();

signals:
    void signalConnecting();
    void signalConnectSucc();
    void signalConnectFail();//
    void signalDisConnectSucc();//maybe
    void signalDisConnectFail();//
    void signalUpdateProgress ( qint64 value );


private slots:
    void domainHostFound();
    void socketStateChanged ( QAbstractSocket::SocketState );
    void socketErrorOccured ( QAbstractSocket::SocketError );
    void socketConnected();
    void socketDisconnect();
    void updateProgress ( qint64 );

protected slots:
    void readyReadData();

private:
    void connectToSingelHost();

    /*
     * TODO:如果文件传输影响到了UI线程，那么需要将QTcpSocket局部变量化
     * 阻塞UI不必考虑此处
     * 非阻塞UI，UI却工作很慢，考虑此处。
     */
    //QTcpSocket* m_sock;

    QQtProtocol* m_protocol;
    quint32 eConType;
    QStringList m_serverIP;
    quint32 m_PORT;
};


#endif // QQT_CLIENT_H
