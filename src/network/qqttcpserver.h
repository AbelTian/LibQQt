#ifndef QQTTCPSERVER_H
#define QQTTCPSERVER_H

#include <QTcpServer>
#include "qqtprotocol.h"
#include "qqttcpclient.h"
#include "qqt-local.h"
#include "qqtcore.h"

/**
 * @brief The QQtTcpServer class
 * 这个是群发Server，
 * 给一个客户端发一个信息，多个客户端，这一个信息会群发。
 */
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


#endif // QQTTCPSERVER_H
