#include "qqtwebclient.h"
#include "qqtcore.h"

QQtWebClient::QQtWebClient(QObject* parent) : QNetworkAccessManager(parent)
{
    connect(this, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(finished(QNetworkReply*)));

    connect(this, SIGNAL(authenticationRequired(QNetworkReply*, QAuthenticator*)),
            this, SLOT(authenticationRequired(QNetworkReply*, QAuthenticator*)));

    connect(this, SIGNAL(proxyAuthenticationRequired(QNetworkProxy, QAuthenticator*)),
            this, SLOT(proxyAuthenticationRequired(QNetworkProxy, QAuthenticator*)));

    connect(this,  SIGNAL(sslErrors(QNetworkReply*, QList<QSslError>)),
            this, SLOT(sslErrors(QNetworkReply*, QList<QSslError>)));

    connect(this, SIGNAL(networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility)),
            this, SLOT(networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility)));

    connect(this, SIGNAL(networkSessionConnected()),
            this, SLOT(networkSessionConnected()));
}

void QQtWebClient::finished(QNetworkReply* reply)
{
    pline() << reply;
}

void QQtWebClient::authenticationRequired(QNetworkReply* r, QAuthenticator* a)
{
    pline() << r << a;
}

void QQtWebClient::proxyAuthenticationRequired(QNetworkProxy p, QAuthenticator* a)
{
    pline() << p.hostName() << a;
}

void QQtWebClient::sslErrors(QNetworkReply* r, QList<QSslError> e)
{
    pline() << r << e.size();
}

void QQtWebClient::networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility a)
{
    pline() << a;
}

void QQtWebClient::networkSessionConnected()
{
    pline();
}
