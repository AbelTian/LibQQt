#ifndef QQTHGTCPSERVER_H
#define QQTHGTCPSERVER_H

#include <QTcpServer>
#include "qqthgprotocolmanager.h"
#include "qqthgtcpclient.h"
#include "qqt-local.h"
#include "qqtcore.h"

/**
 * @brief The QQtHgTcpServer class
 * 这个类相当于QQtHgTcpClient管理器，相当于Socket管理器，它包含很多Socket。
 *
 * 概述：
 * 在这里安装HgProtocolManager以后，用户可以通过PM来进行通信。如果有必要的话。如果没有必要通知用户，在用户的Protocol里面实现通信就可以足够了。
 * 如果这个程序主要任务就是当作服务器节点，那么就把命令传给业务层好了，如果仅仅是包含一个服务器模块，那么不必要把客户端命令非要传给上层。
 *
 * 安装一个HgProtocolManager，包含很多的HgProtocol
 */
class QQTSHARED_EXPORT QQtHgTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit QQtHgTcpServer ( QObject* parent = 0 );
    ~QQtHgTcpServer();

    void installProtocolManager ( QQtHgProtocolManager* stackGroup );
    void uninstallProtocolManager ( QQtHgProtocolManager* stackGroup );
    QQtHgProtocolManager* installedProtocolManager();

signals:

    // QTcpServer interface
protected:
    virtual void incomingConnection ( qintptr handle ) override;

private slots:
    void clientSocketDisConnected();
private:
    QQtHgProtocolManager* m_protocolManager;
};


#endif // QQTHGTCPSERVER_H
