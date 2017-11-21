#ifndef QQTSERVER_H
#define QQTSERVER_H

#include <QTcpServer>
#include "qqtprotocol.h"
#include "qqtclient.h"
#include "qqt-local.h"
#include "qqtcore.h"

class QQTSHARED_EXPORT QQtServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit QQtServer ( QObject* parent = 0 );
    ~QQtServer();

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
