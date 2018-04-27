/**************************************************
 * QQtHgTcpClient
 * 在一个工程当中仅仅存在一个实例，通过调用QQtHgTcpClient实现。
 **************************************************/
#ifndef QQTHGTCPCLIENT_H
#define QQTHGTCPCLIENT_H

#include <QTcpSocket>
#include "QStringList"
#include "qqthgprotocolmanager.h"

#include "qqt-local.h"
#include "qqtcore.h"

#define QQT_TCP_SOCKET 0
#define QQT_SOCKET 1
#define QQT_THREAD 0
#define _TCP_BLOCKDATA_SIZE                    0x400
#define _TCP_RECVBUFF_SIZE                      0x800

/**
 * @brief 客户端决定和协议的交互关系;只跟协议打交道；
 * 处理粘包，数少包。
 * 通过安装协议，支持客户通信
 * 打开，
 * 发送，接收，splitter，dispatcher
 * 关闭。
 */
class QQTSHARED_EXPORT QQtHgTcpClient : public QTcpSocket
{
    Q_OBJECT
public:
    explicit QQtHgTcpClient ( QObject* parent = 0 );
    virtual ~QQtHgTcpClient();

    void SetServerIPAddress ( QStringList ip ) { m_serverIP = ip; }
    void SetServerPort ( quint32 p = 7079 ) { m_PORT = p; }

    void installProtocolManager ( QQtHgProtocolManager* stackGroup );
    void uninstallProtocolManager ( QQtHgProtocolManager* stackGroup );
    QQtHgProtocolManager* installedProtocolManager();

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
    void writeData ( const QByteArray& );

private:
    void connectToSingelHost();

    /*
     * TODO:如果文件传输影响到了UI线程，那么需要将QTcpSocket局部变量化
     * 阻塞UI不必考虑此处
     * 非阻塞UI，UI却工作很慢，考虑此处。
     */
    //QTcpSocket* m_sock;

private:
    QQtHgProtocolManager* m_protocolManager;
    quint32 eConType;
    QStringList m_serverIP;
    quint32 m_PORT;
};


#endif // QQTHGTCPCLIENT_H
