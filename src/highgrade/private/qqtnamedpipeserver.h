#ifndef QQTNAMEDPIPESERVER_H
#define QQTNAMEDPIPESERVER_H

#include <QLocalServer>
#include "qqtprotocolmanager.h"
#include "qqtnamedpipeclient.h"
#include "qqt-local.h"
#include "qqtcore.h"

/**
 * @brief The QQtNamedPipeServer class
 * 把Pipe封装成了Socket的模样。
 * Server管理Pipe的创建和销毁，listen可以调用多次，但是相同的key只有开始的一次可以成功listen。
 */
class QQTSHARED_EXPORT QQtNamedPipeServer : public QLocalServer
{
    Q_OBJECT
public:
    explicit QQtNamedPipeServer ( QObject* parent = 0 );
    virtual ~QQtNamedPipeServer();

    void installProtocolManager ( QQtProtocolManager* stackGroup );
    void uninstallProtocolManager ( QQtProtocolManager* stackGroup );
    QQtProtocolManager* installedProtocolManager();

public:
    QQtNamedPipeClient* findClientByProtocolInstance ( QQtProtocol* protocol );
    //输入的不是serverIP是客户端Name。
    QQtNamedPipeClient* findClientByIPAddress ( QString ip );
    QList<QQtNamedPipeClient*>& clientList() { return m_clientList; }

signals:
    // QQtNamedPipeServer interface
public slots:
    void clientSocketDisConnected();
private slots:
    void comingNewConnection();
private:
    QQtProtocolManager* m_protocolManager;
    QList<QQtNamedPipeClient*> m_clientList;
};


#endif // QQTNAMEDPIPESERVER_H
