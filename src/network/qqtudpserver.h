#ifndef QQTUDPSERVER_H
#define QQTUDPSERVER_H

#include <QUdpSocket>

class QQtUdpServer : public QUdpSocket
{
    Q_OBJECT
public:
    explicit QQtUdpServer(QObject* parent = nullptr);

signals:

public slots:
};

#endif // QQTUDPSERVER_H
