#ifndef QQTSERVER_H
#define QQTSERVER_H

#include <QTcpServer>
#include "qqtprotocol.h"
#include "qqtclient.h"
#include "qqt-local.h"

class QQTSHARED_EXPORT QQTServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit QQTServer(QObject *parent = 0);
    ~QQTServer();

    void installProtocol(QQTProtocol* stack);
    void uninstallProtocol(QQTProtocol* stack);
    QQTProtocol* installedProtocol();

signals:
    // QTcpServer interface
protected:
    void incomingConnection(int handle);
private:
    QQTProtocol* m_protocol;
};


#endif // QQTSERVER_H
