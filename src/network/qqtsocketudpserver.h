#ifndef QQTUDPSERVER_H
#define QQTUDPSERVER_H

#include <QUdpSocket>
#include <qqtcore.h>

class QQtSocketUdpServer : public QUdpSocket
{
    Q_OBJECT
public:
    explicit QQtSocketUdpServer ( QObject* parent = nullptr );
    virtual ~QQtSocketUdpServer() {}

signals:

public slots:
};

#endif // QQTUDPSERVER_H
