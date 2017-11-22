#ifndef QQTWEBSERVER_H
#define QQTWEBSERVER_H

#include <QObject>

class QQtWebSocketServer : public QObject
{
    Q_OBJECT
public:
    explicit QQtWebSocketServer ( QObject* parent = nullptr );

signals:

public slots:
};

#endif // QQTWEBSERVER_H
