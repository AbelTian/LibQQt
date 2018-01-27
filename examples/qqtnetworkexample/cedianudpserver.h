#ifndef CEDIANUDPSERVER_H
#define CEDIANUDPSERVER_H

#include <qqtsocketudpclient.h>
#include <qqtcore.h>

class CedianUdpServer : public QQtSocketUdpClient
{
    Q_OBJECT
public:
    explicit CedianUdpServer ( QObject* parent = nullptr );
    virtual ~CedianUdpServer() {}

signals:

public slots:
};

#endif // CEDIANUDPSERVER_H
