#ifndef QQTLOCALSERVER_H
#define QQTLOCALSERVER_H

#include <QLocalServer>
#include "qqtprotocolmanager.h"
#include "qqtlocalclient.h"
#include "qqt-local.h"
#include "qqtcore.h"

/**
 * @brief The QQtLocalServer class
 * 把Pipe封装成了Socket的模样。
 * Server管理Pipe的创建和销毁，listen可以调用多次，但是相同的key只有开始的一次可以成功listen。
 */
class QQTSHARED_EXPORT QQtLocalServer : public QLocalServer
{
    Q_OBJECT
public:
    explicit QQtLocalServer ( QObject* parent = 0 );
    ~QQtLocalServer();

    void installProtocolManager ( QQtProtocolManager* stackGroup );
    void uninstallProtocolManager ( QQtProtocolManager* stackGroup );
    QQtProtocolManager* installedProtocolManager();

public:
    QQtLocalClient* findClientByProtocolInstance ( QQtProtocol* protocol );
    //输入的不是serverIP是客户端Name。
    QQtLocalClient* findClientByIPAddress ( QString ip );
    QList<QQtLocalClient*>& clientList() { return m_clientList; }

signals:
    // QQtLocalServer interface
public slots:
    void clientSocketDisConnected();
private slots:
    void comingNewConnection();
private:
    QQtProtocolManager* m_protocolManager;
    QList<QQtLocalClient*> m_clientList;
};


#endif // QQTLOCALSERVER_H
