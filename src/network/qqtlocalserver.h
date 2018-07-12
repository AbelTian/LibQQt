#ifndef QQTLOCALSERVER_H
#define QQTLOCALSERVER_H

#include <QLocalServer>
#include "qqtprotocolmanager.h"
#include "qqtlocalclient.h"
#include "qqt-local.h"
#include "qqtcore.h"

/**
 * @brief The QQtLocalServer class
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
