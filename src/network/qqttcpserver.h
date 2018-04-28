#ifndef QQTTCPSERVER_H
#define QQTTCPSERVER_H

#include <QTcpServer>
#include "qqtprotocolmanager.h"
#include "qqttcpclient.h"
#include "qqt-local.h"
#include "qqtcore.h"

/**
 * @brief The QQtTcpServer class
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
    // QTcpServer interface
protected:
    virtual void incomingConnection ( qintptr handle ) override;
private:
    QQtProtocolManager* m_protocolManager;
public slots:
    void clientSocketDisConnected();
};


#endif // QQTTCPSERVER_H
