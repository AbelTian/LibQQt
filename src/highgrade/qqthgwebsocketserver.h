#ifndef QQTHGWEBSERVER_H
#define QQTHGWEBSERVER_H

#include <QObject>
#include <qqtcore.h>
#include <qqt-local.h>

class QQTSHARED_EXPORT QQtHgWebSocketServer : public QObject
{
    Q_OBJECT
public:
    explicit QQtHgWebSocketServer ( QObject* parent = nullptr );

signals:

public slots:
};

#endif // QQTHGWEBSERVER_H
