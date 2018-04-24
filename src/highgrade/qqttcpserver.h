#ifndef QQTSERVER_H
#define QQTSERVER_H

#include <QTcpServer>
#include "qqtprotocolmanager.h"
#include "qqttcpclient.h"
#include "qqt-local.h"
#include "qqtcore.h"

/**
 * @brief The QQtTcpServer class
 * 这个类相当于QQtTcpClient管理器，相当于Socket管理器，它包含很多Socket。
 *
 * 概述：
 * 在这里安装ProtocolManager以后，用户可以通过PM来进行通信。如果有必要的话。如果没有必要通知用户，在用户的Protocol里面实现通信就可以足够了。
 * 如果这个程序主要任务就是当作服务器节点，那么就把命令传给业务层好了，如果仅仅是包含一个服务器模块，那么不必要把客户端命令非要传给上层。
 *
 */
class QQTSHARED_EXPORT QQtTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit QQtTcpServer ( QObject* parent = 0 );
    ~QQtTcpServer();

    void installProtocolManager ( QQtProtocolManager* stackGroup );
    void uninstallProtocolManager ( QQtProtocolManager* stackGroup );
    QQtProtocolManager* installedProtocolManager();

signals:
protected slots:
    void slotNewConnection();
    // QTcpServer interface
protected:
    virtual void incomingConnection ( qintptr handle ) override;
private:
    QQtProtocolManager* m_protocolManager;
};


#endif // QQTSERVER_H
