#ifndef QQTNETWORKSERVER_H
#define QQTNETWORKSERVER_H

#include <QObject>

class QQtNetworkServer : public QObject
{
    Q_OBJECT
public:
    explicit QQtNetworkServer(QObject *parent = nullptr);

signals:

public slots:
};

#endif // QQTNETWORKSERVER_H