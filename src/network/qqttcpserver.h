#ifndef QQTSERVER_H
#define QQTSERVER_H

#include <QTcpServer>
#include "qqtprotocol.h"
#include "qqttcpclient.h"
#include "qqt-local.h"
#include "qqtcore.h"

class QQTSHARED_EXPORT QQtTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit QQtTcpServer ( QObject* parent = 0 );
    ~QQtTcpServer();

    void installProtocol ( QQtProtocol* stack );
    void uninstallProtocol ( QQtProtocol* stack );
    QQtProtocol* installedProtocol();

signals:
    // QTcpServer interface
protected:
    virtual void incomingConnection ( qintptr handle ) override;
private:
    QQtProtocol* m_protocol;
};


#endif // QQTSERVER_H
