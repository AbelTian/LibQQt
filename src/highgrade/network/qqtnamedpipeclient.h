/**************************************************
 * QQtNamedPipeClient
 * 在一个工程当中仅仅存在一个实例，通过调用QQtNamedPipeClient实现。
 **************************************************/
#ifndef QQTNAMEDPIPECLIENT_H
#define QQTNAMEDPIPECLIENT_H

#include <QLocalSocket>
#include <QStringList>
#include "qqtprotocol.h"
#include "qqt-local.h"
#include "qqtcore.h"

/**
 * @brief 客户端决定和协议的交互关系;只跟协议打交道；
 * 处理粘包，数少包。
 * 通过安装协议，支持客户通信
 * 打开，
 * 发送，接收，splitter，dispatcher
 * 关闭。
 */
class QQTSHARED_EXPORT QQtNamedPipeClient : public QLocalSocket
{
    Q_OBJECT
public:
    explicit QQtNamedPipeClient ( QObject* parent = 0 );
    virtual ~QQtNamedPipeClient();

    //输入的不是serverIP是serverName。
    //如果连续设置两个不同的，代表依次连接，第二个是备用的。
    //注意：这里用的是命名的serverName，如果想使用不命名的接口，请用户自行是用setServerName。
    void setServerIPAddress ( QString ip ) {
        if ( m_serverIP.contains ( ip ) )
            return;
        m_serverIP.push_back ( ip );
    }
    QStringList& serverIPAddress() { return m_serverIP; }
    void setServerIPAddress ( QStringList ipList ) { m_serverIP = ipList; }

    void installProtocol ( QQtProtocol* stack );
    void uninstallProtocol ( QQtProtocol* stack );
    QQtProtocol* installedProtocol();

    void sendConnectToHost();
    int sendDisConnectFromHost();

    void setPeerName ( QString name ) { this->mPeerName = name; }
    QString peerName() { return mPeerName; }

signals:
    void signalConnecting();
    void signalConnectSucc();
    void signalConnectFail();//
    void signalConnectError();//
    void signalDisConnectSucc();//maybe
    void signalDisConnectFail();//
    void signalUpdateProgress ( qint64 value );


private slots:
    void socketStateChanged ( QLocalSocket::LocalSocketState );
    void socketErrorOccured ( QLocalSocket::LocalSocketError );
    void socketConnected();
    void socketDisconnect();
    void updateProgress ( qint64 );

protected slots:
    void readyReadData();
    void slotWriteData ( const QByteArray& );

protected:
    /**
     * @brief translator
     * 用于拆分和分发数据报
     * @param bytes
     */
    virtual void translator ( const QByteArray& bytes );
    void connectToSingelHost();

private:
    /*
     * TODO:如果文件传输影响到了UI线程，那么需要将QLocalSocket局部变量化
     * 阻塞UI不必考虑此处
     * 非阻塞UI，UI却工作很慢，考虑此处。
     */
    //QLocalSocket* m_sock;

    QQtProtocol* m_protocol;
    quint32 eConType;
    QStringList m_serverIP;
    QString mPeerName;
};


#endif // QQTNAMEDPIPECLIENT_H
