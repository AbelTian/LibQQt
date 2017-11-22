#ifndef QQTSERVER_H
#define QQTSERVER_H

#include <QTcpServer>
#include "qqtprotocol.h"
#include "qqtsockettcpclient.h"
#include "qqt-local.h"
#include "qqtcore.h"

class QQTSHARED_EXPORT QQtSocketTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit QQtSocketTcpServer ( QObject* parent = 0 );
    ~QQtSocketTcpServer();

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
