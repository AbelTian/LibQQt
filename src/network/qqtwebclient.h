#ifndef QQTWEBCLIENT_H
#define QQTWEBCLIENT_H

#include <QNetworkAccessManager>
//import this struct will not build fail
#include <QNetworkProxy>
#include <QSslError>
#include <qqt-qt.h>
#include <qqt-local.h>

class QQTSHARED_EXPORT QQtWebClient : public QNetworkAccessManager
{
    Q_OBJECT
public:
    explicit QQtWebClient(QObject* parent = 0);

    //void installProtocol();
    //void uninstallProtocol();

signals:

public slots:

private slots:
    void finished(QNetworkReply* reply);
    void authenticationRequired(QNetworkReply*, QAuthenticator*);
    void proxyAuthenticationRequired(QNetworkProxy, QAuthenticator*);
    void sslErrors(QNetworkReply*, QList<QSslError>);
    void networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility);
    void networkSessionConnected();
};

#endif // QQTWEBCLIENT_H
