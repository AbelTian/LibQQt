#ifndef CEDIANUDPSERVER_H
#define CEDIANUDPSERVER_H

#include <qqtudpclient.h>
#include <qqtcore.h>

class CedianUdpServer : public QQtUdpClient
{
    Q_OBJECT
public:
    explicit CedianUdpServer ( QObject* parent = nullptr );
    virtual ~CedianUdpServer() {}

signals:

public slots:
};

#endif // CEDIANUDPSERVER_H
