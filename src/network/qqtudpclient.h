#ifndef QQTUDPCLIENT_H
#define QQTUDPCLIENT_H

#include <QUdpSocket>

class QQtUdpClient : public QUdpSocket
{
    Q_OBJECT
public:
    explicit QQtUdpClient(QObject* parent = nullptr);

signals:

public slots:
};

#endif // QQTUDPCLIENT_H
