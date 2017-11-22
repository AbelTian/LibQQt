#ifndef QQTWEBPROTOCOL_H
#define QQTWEBPROTOCOL_H

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSslError>
#include <qqt-local.h>
#include <qqtprotocol.h>

class QQTSHARED_EXPORT QQtWebSocketProtocol : public QQtProtocol
{
    Q_OBJECT
public:
    explicit QQtWebSocketProtocol ( QObject* parent = 0 );

signals:

public slots:
};

#endif // QQTWEBPROTOCOL_H
