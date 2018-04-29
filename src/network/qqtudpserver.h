#ifndef QQTUDPSERVER_H
#define QQTUDPSERVER_H

#include "qqtprotocolmanager.h"
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
 *
 * 注意
 * Server
 * bind 固定port recv
 * 句柄1 动态port sendTo Client必须绑定才能接收。
 * 句柄1 不能接收
 * Server端发出信息的肯定是动态端口。
 * Client
 * no bind 动态端口 sendTo
 * bind    固定端口 sendTo 而且可以recv
 *
 * 特点
 * Server发出去的时候，本地端口是动态端口。
 * 经过分析，Client一般都会忽视这个端口，只重视Server的IP和bind port。
 * 所以，Client端一定不会混淆服务器的。
 * 既然可以发回去，那么Client一定bind port了。Client bind port的时候，发出消息的本地端口是个固定值。:)
 *
 * 继承于QQtUdpClient
 * 说明有一套特殊的协议，用于一个特殊的目标，一般为组播服务器。
 */
class QQTSHARED_EXPORT QQtUdpServer : public QQtUdpClient
{
    Q_OBJECT
public:
    explicit QQtUdpServer ( QObject* parent = nullptr );
    virtual ~QQtUdpServer() {}

    void installProtocolManager ( QQtProtocolManager* stackGroup );
    void uninstallProtocolManager ( QQtProtocolManager* stackGroup );
    QQtProtocolManager* installedProtocolManager();

public:
    QQtUdpClient* findClientByProtocolInstance ( QQtProtocol* protocol );
    QQtUdpClient* findClientByIPAddress ( QString ip, quint16 port );
    QList<QQtUdpClient*>& clientList() { return m_clientList; }

    /**
     * 以下和用户无关
     */
protected slots:
    void readyReadData();
    /**
     * 这个函数，在UDP Server里面没有用。Client句柄安装的Protocol会从Client句柄发出，不会从这里发出。
     * 我打算从这里往组播服务器发消息。
     * 用户可以在协议里面定义组播服务器的位置，并且定义获取组播地址的命令。
     * 注意哦，组播服务器一定要设置为仅仅识别为有数的几个服务器的接收，包括本服务器，否则会风暴的。
     */
    //

public slots:
    void clientSocketDisConnected();

protected:
private:
    QQtProtocolManager* m_protocolManager;
    QList<QQtUdpClient*> m_clientList;
};

#endif // QQTUDPSERVER_H
