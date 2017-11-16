#ifndef QQTSERVER_H
#define QQTSERVER_H

#include <QTcpServer>
#include "qqtprotocol.h"
#include "qqtclient.h"
#include "qqt-local.h"
#include "qqtcore.h"

class QQTSHARED_EXPORT QQTServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit QQTServer(QObject* parent = 0);
    ~QQTServer();

    void installProtocol(QQtProtocol* stack);
    void uninstallProtocol(QQtProtocol* stack);
    QQtProtocol* installedProtocol();

signals:
    // QTcpServer interface
protected:
    virtual void incomingConnection(qintptr handle) Q_DECL_OVERRIDE;
private:
    QQtProtocol* m_protocol;
};


#endif // QQTSERVER_H
