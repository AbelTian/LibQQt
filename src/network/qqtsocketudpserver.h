#ifndef QQTUDPSERVER_H
#define QQTUDPSERVER_H

#include <QUdpSocket>
#include "qqtprotocol.h"
#include "qqtsocketudpclient.h"
#include "qqt-local.h"
#include "qqtcore.h"
#include <QThread>

class QQtSocketUdpServer : public QUdpSocket
{
    Q_OBJECT
public:
    explicit QQtSocketUdpServer ( QObject* parent = nullptr );
    virtual ~QQtSocketUdpServer();

    void installProtocol ( QQtProtocol* stack );
    void uninstallProtocol ( QQtProtocol* stack );
    QQtProtocol* installedProtocol();

    /*必须在安装协议之后调用，否则崩溃*/
    void startListening();

    /*在虚构函数里调用了，客户不调用没关系*/
    void stopListening();

signals:

public slots:
private:
    QQtProtocol* m_protocol;
    QThread* m_thread;
};

#endif // QQTUDPSERVER_H
