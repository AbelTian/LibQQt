#ifndef QQTWEBSOCKETSERVER_H
#define QQTWEBSOCKETSERVER_H

#include <QWebSocketServer>
#include <qqtcore.h>

class QQtWebSocketServer : public QWebSocketServer
{
    Q_OBJECT
public:
    explicit QQtWebSocketServer ( QObject* parent = nullptr );

signals:

public slots:
};

#endif // QQTWEBSOCKETSERVER_H
