#ifndef QQTWEBPROTOCOL_H
#define QQTWEBPROTOCOL_H

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <qqt-local.h>

class QQTSHARED_EXPORT QQtWebProtocol : public QObject
{
    Q_OBJECT
public:
    explicit QQtWebProtocol(QObject *parent = 0);

signals:

public slots:
};

#endif // QQTWEBPROTOCOL_H
