#ifndef QQTHGWEBPROTOCOL_H
#define QQTHGWEBPROTOCOL_H

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSslError>
#include <qqt-local.h>
#include <qqthgprotocol.h>

class QQTSHARED_EXPORT QQtHgWebSocketProtocol : public QQtHgProtocol
{
    Q_OBJECT
public:
    explicit QQtHgWebSocketProtocol ( QObject* parent = 0 );

signals:

public slots:
};

#endif // QQTHGWEBPROTOCOL_H
