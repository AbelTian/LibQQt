#ifndef QQTUDPCLIENT_H
#define QQTUDPCLIENT_H

#include <QUdpSocket>
#include <qqtcore.h>

class QQtSocketUdpClient : public QUdpSocket
{
    Q_OBJECT
public:
    explicit QQtSocketUdpClient ( QObject* parent = nullptr );

signals:

public slots:
};

#endif // QQTUDPCLIENT_H
