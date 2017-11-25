#ifndef QQTWEBWORKCLIENT_H
#define QQTWEBWORKCLIENT_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
//import this struct will not build fail
#include <QNetworkProxy>
#include <QSslError>
#include <qqt-qt.h>
#include <qqt-local.h>
#include <qqtcore.h>
#include <QUuid>

class QQTSHARED_EXPORT QQtWebAccessSession : public QObject
{
    Q_OBJECT
public:
    explicit QQtWebAccessSession ( QObject* parent = 0 ) :
        QObject ( parent ) {
        m_pTimer = new QTimer ( this );
        m_pTimer->setSingleShot ( true );
        m_pTimer->setInterval ( 10000 );
    }
    virtual ~QQtWebAccessSession() {}

    void setTimeOut ( int timeout ) {
        m_pTimer->setInterval ( timeout );
    }
    QTimer* getTimer() {
        return m_pTimer;
    }
    QNetworkReply* getWebAccessReply() {
        return m_pNetworkReply;
    }
    void setWebAccessReply ( QNetworkReply* reply ) {
        m_pNetworkReply = reply;
    }
    QString getWebAccessUrl() {
        return m_strUrl;
    }
    void setWebAccessUrl ( QString strUrl ) {
        m_strUrl = strUrl;
    }
    QString getWebAccessSessionName() {
        return m_strSessionName;
    }
    void setWebAccessSessionName ( QString strSessionName ) {
        m_strSessionName = strSessionName;
    }

private:
    //call back
    QNetworkReply* m_pNetworkReply;
    //call time out
    QTimer* m_pTimer;
    //calling url [user set]
    QString m_strUrl;
    /**
     * @brief m_sessionName be a uuid [user set or auto]
     * talk with whom, which protocol, req content, all represented by this name;
     */
    QString m_strSessionName;
} ;

class QQTSHARED_EXPORT QQtWebAccessSessionManager : public QObject
{
    Q_OBJECT
public:
    explicit QQtWebAccessSessionManager ( QObject* parent = 0 ) :
        QObject ( parent ) {}
    virtual ~QQtWebAccessSessionManager() {}

    /**
     * @brief addWebAccessSession user new custom session and
     * please set session name different.
     * @return session name
     */
    QString addWebAccessSession ( QQtWebAccessSession* session ) {
        if ( !session )
            return QString();

        m_listWebAccessSession.push_back ( session );
        return session->getWebAccessSessionName();
    }
    void removeWebAccessSession ( QQtWebAccessSession* session ) {
        if ( !session )
            return;

        m_listWebAccessSession.removeOne ( session );
    }
    /**
     * @brief newWebAccessSession
     * QQtWebAccessSessionManager create this session and
     * user set
     * @return
     */
    QQtWebAccessSession* newWebAccessSession();

    int getSessionCount() const {
        return m_listWebAccessSession.count();
    }

    QNetworkReply* getReplyHandlerByUrl ( QString& strUrl );
    QString getSessionNameByUrl ( QString& strUrl );
    QQtWebAccessSession* getSessionByUrl ( QString& strUrl );

    QString getRequestUrlByReply ( QNetworkReply* reply );
    QString getSessionNameByReply ( QNetworkReply* reply );
    QQtWebAccessSession* getSessionByReply ( QNetworkReply* reply );

    QNetworkReply* getReplyHandlerBySessionName ( QString& strSessionName );
    QString getRequestUrlBySessionName ( QString& strSessionName );
    QQtWebAccessSession* getSessionBySessionName ( QString& strSessionName );

    QNetworkReply* getReplyHandlerByTimer ( QTimer* timer );
    QString getRequestUrlByTimer ( QTimer* timer );
    QQtWebAccessSession* getSessionByTimer ( QTimer* timer );


    QNetworkReply* getReplyHandler ( QQtWebAccessSession* session );
    QString getRequestUrl ( QQtWebAccessSession* session );
    QString getSessionName ( QQtWebAccessSession* session );

protected:

private:
    QList<QQtWebAccessSession*> m_listWebAccessSession;
    friend class QQtWebAccessManager;
} ;


/**
 * @brief The QQtWebAccessManager class
 * XXProtocol One Ftp Http QWebSocket(Custom Web Protocol) 单工...(全双工通信)
 * Multi 半双工（客户端并发，服务器序列） QNetworkAccessManager
 * Multi 全双工 QNetworkAccessManager
 * need ssl
 * Qt team 实现了几种协议的管理，就能进行几种协议的通讯。supportedSchemes
 * 用户输入的session，还可以被完整返回来，所以不必自己再实现一个链表进行管理，在session当中完整的保存就好了。
 */
class QQTSHARED_EXPORT QQtWebAccessManager : public QNetworkAccessManager
{
    Q_OBJECT
public:
    explicit QQtWebAccessManager ( QObject* parent = 0 );

    QQtWebAccessSessionManager* getWebAccessSessionManager() {
        return manager;
    }
    /**
     * @brief sendGetRequest
     * use for custom session;
     * @param session
     */
    void sendGetRequest ( QQtWebAccessSession* session );

    QQtWebAccessSession* sendGetRequest ( QString strUrl );
    QQtWebAccessSession* sendGetRequests ( QStringList& strUrls );
    QQtWebAccessSession* sendGetRequest ( QNetworkRequest& netRequest );
    QQtWebAccessSession* sendGetRequests ( QList<QNetworkRequest*>& netRequests );

    QQtWebAccessSession* sendPostRequest ( QString strUrl );

signals:
    void updateUploadProgress ( QQtWebAccessSession* session, qint64 bytesSent, qint64 bytesTotal );
    void updateDownloadProgress ( QQtWebAccessSession* session, qint64 bytesReceived, qint64 bytesTotal );
    //reply->readAll but maybe not all data once
    void readyRead ( QQtWebAccessSession* session );
    //reply->readAll all data once in theory
    void replyFinished ( QQtWebAccessSession* session );
    void replyTimeOut ( QQtWebAccessSession* session );

public slots:

private slots:
    void finished ( QNetworkReply* reply );
    void authenticationRequired ( QNetworkReply*, QAuthenticator* );
    void proxyAuthenticationRequired ( QNetworkProxy, QAuthenticator* );
    void sslErrors ( QNetworkReply*, QList<QSslError> );
    void networkAccessibleChanged ( QNetworkAccessManager::NetworkAccessibility );
    void networkSessionConnected();

    void localReplyTimeOut();
    void localReadyRead();
    void localUpdateUploadProgress ( qint64 bytesSent, qint64 bytesTotal );
    void localUpdateDownloadProgress ( qint64 bytesReceived, qint64 bytesTotal );

private:
    QQtWebAccessSessionManager* manager;

    friend class QQtWebAccessSessionManager;
};

#endif // QQTWEBWORKCLIENT_H
