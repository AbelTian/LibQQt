#ifndef QQTNETWORKCLIENT_H
#define QQTNETWORKCLIENT_H

#include <QNetworkAccessManager>
//import this struct will not build fail
#include <QNetworkProxy>
#include <QSslError>
#include <qqt-qt.h>
#include <qqt-local.h>
/**
 * @brief The QQtNetworkClient class
 * One Ftp Http 单工...
 * Multi 半双工（客户端并发，服务器序列） QNetworkAccessManager
 * Multi New Protocol 全双工 QWebSocket
 */
class QQTSHARED_EXPORT QQtNetworkClient : public QNetworkAccessManager
{
    Q_OBJECT
public:
    explicit QQtNetworkClient(QObject* parent = 0);

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

#endif // QQTNETWORKCLIENT_H
