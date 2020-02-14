#ifndef QQTWEBWORKCLIENT_H
#define QQTWEBWORKCLIENT_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

//import this struct will not build fail
#include <QNetworkProxy>
#ifdef __SSLSUPPORT__
#include <QSslError>
#endif
#include <QStringList>
#include <QUuid>

#include <QNetworkCookie>
#include <QNetworkCookieJar>


#include <qqt-qt.h>
#include <qqt-local.h>
#include <qqtcore.h>

/**
 * @brief QQtWebAccessCookie
 * QNetworkCookie parseCookie函数有错误，在QQtWebAccessCookieJar里面重新实现
 * QQtWebAccessCookie沿用QNetworkCookie。
 * 一个cookie包括name和value，和其他信息。
 */
typedef QNetworkCookie QQtWebAccessCookie;

/**
 * @brief The QQtWebAccessCookieJar class
 * 一个QQtWebAccessManager对应一个cookieJar
 * 这个CookieJar是具名的CookieJar。
 * QNetworkCookieJar可以保存多个网址的Cookie组
 * 添加一些函数丰富QQtWebAccessCookieJar的功能
 */
class QQTSHARED_EXPORT QQtWebAccessCookieJar: public QNetworkCookieJar
{
    Q_OBJECT

public:
    explicit QQtWebAccessCookieJar ( QObject* parent = Q_NULLPTR );
    virtual ~QQtWebAccessCookieJar();

    void setCookieJarName ( const QString& name );
    QString cookieJarName() const;

    //这几个函数的作用不明确，在此改写。[或许影响所有url的cookie组]
    //virtual bool insertCookie(const QNetworkCookie &cookie);
    //virtual bool updateCookie(const QNetworkCookie &cookie);
    //virtual bool deleteCookie(const QNetworkCookie &cookie);

    virtual bool hasCookieForUrl ( const QNetworkCookie& cookie, const QUrl& url );
    //行为：不存在cookie[name]时插入，存在cookie[name]时改写。(这样做省却了一个判定步骤。)
    virtual bool insertCookieForUrl ( const QNetworkCookie& cookie, const QUrl& url );
    virtual bool updateCookieForUrl ( const QNetworkCookie& cookie, const QUrl& url );
    virtual bool deleteCookieForUrl ( const QNetworkCookie& cookie, const QUrl& url );

    //一个网址对应一组cookie [网址相当于组cookie的名字]
    //给这个函数改改名字
    virtual bool setCookiesForUrl ( const QList<QNetworkCookie>& cookieList, const QUrl& url );

    //QNetworkCookie里面的这个函数是个废物。
    static QList<QNetworkCookie> parseCookies ( const QByteArray& cookieString );
};

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

    //timer
    void setTimeOut ( int timeout ) {
        m_pTimer->setInterval ( timeout );
    }
    QTimer* getTimer() {
        return m_pTimer;
    }

    //request
    QString getWebAccessUrl() {
        return mNetworkRequest.url().toString();
    }
    void setWebAccessUrl ( QString strUrl ) {
        m_strUrl = strUrl;
        mNetworkRequest.setUrl ( QUrl ( m_strUrl ) );
    }
    QNetworkRequest& webAccessRequest() {
        return mNetworkRequest;
    }

    //reply
    QNetworkReply* getWebAccessReply() {
        return m_pNetworkReply;
    }
    void setWebAccessReply ( QNetworkReply* reply ) {
        m_pNetworkReply = reply;
    }

    //session name
    QString getWebAccessSessionName() {
        return m_strSessionName;
    }
    void setWebAccessSessionName ( QString strSessionName ) {
        m_strSessionName = strSessionName;
    }

private:
    //request
    QNetworkRequest mNetworkRequest;
    //call back
    QNetworkReply* m_pNetworkReply;
    //call time out
    QTimer* m_pTimer;
    //calling url [user set] to make request
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
    QQtWebAccessSession* newWebAccessSession() {
        QUuid uuid = QUuid::createUuid();
        QQtWebAccessSession* session = new QQtWebAccessSession ( this );
        session->setWebAccessSessionName ( uuid.toString() );
        m_listWebAccessSession.push_back ( session );
        return session;
    }

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
} ;

/**
 * @brief The QQtWebAccessManager class
 * XXProtocol One Ftp Http QWebSocket(Custom Web Protocol) 单工...(全双工通信)
 * Multi 半双工（客户端并发，服务器序列） QNetworkAccessManager
 * Multi 全双工 QNetworkAccessManager
 * 加密 need ssl
 * Qt team 实现了几种协议的管理，就能进行几种协议的通讯。supportedSchemes
 * 用户输入的session，还可以被完整返回来，所以不必自己再实现一个链表进行管理，在session当中完整的保存就好了。
 *
 * 支持cookie
 * 一个QQtWebAccessManager有一个cookieJar，一个cookieJar可以保存一组组针对网址的cookies。
 * 用户只需要知道cookie的通信过程，就可以使用QQtWebAccessManager的cookieJar了。
 */
class QQTSHARED_EXPORT QQtWebAccessManager : public QNetworkAccessManager
{
    Q_OBJECT
public:
    explicit QQtWebAccessManager ( QObject* parent = 0 );

    QQtWebAccessSessionManager* getWebAccessSessionManager();
    /**
     * @brief sendGetRequest
     * use for custom session;
     * 内部重要函数
     * @param session
     */
    void sendGetRequest ( QQtWebAccessSession* session );
    QQtWebAccessSession* sendGetRequest ( QString strUrl );
    QList<QQtWebAccessSession*> sendGetRequests ( QStringList& strUrls );
    QQtWebAccessSession* sendGetRequest ( const QNetworkRequest& netRequest );
    QList<QQtWebAccessSession*> sendGetRequests ( const QList<QNetworkRequest>& netRequests );

    QQtWebAccessSession* sendHeadRequest ( const QNetworkRequest& request );
    QQtWebAccessSession* sendPostRequest ( const QNetworkRequest& request, QIODevice* data );
    QQtWebAccessSession* sendPostRequest ( const QNetworkRequest& request, const QByteArray& data );
    QQtWebAccessSession* sendPostRequest ( const QNetworkRequest& request, QHttpMultiPart* multiPart );
    QQtWebAccessSession* sendPutRequest ( const QNetworkRequest& request, QIODevice* data );
    QQtWebAccessSession* sendPutRequest ( const QNetworkRequest& request, const QByteArray& data );
    QQtWebAccessSession* sendPutRequest ( const QNetworkRequest& request, QHttpMultiPart* multiPart );
    QQtWebAccessSession* sendDeleteResourceRequest ( const QNetworkRequest& request );
    QQtWebAccessSession* sendCustomRequest ( const QNetworkRequest& request, const QByteArray& verb,
                                             QIODevice* data = Q_NULLPTR );

    //win没有这几个函数
    //arm下5.5.1没有
    //macOS5.7.1没有，这个函数是新加的。

    //linux macOS下有.
#if defined( __DARWIN__ ) || defined( __LINUX__ )
#if QT_VERSION > QT_VERSION_CHECK(5,7,1)
    QQtWebAccessSession* sendCustomRequest ( const QNetworkRequest& request, const QByteArray& verb,
                                             const QByteArray& data );
    QQtWebAccessSession* sendCustomRequest ( const QNetworkRequest& request, const QByteArray& verb,
                                             QHttpMultiPart* multiPart );
#endif
#endif

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
#ifdef __SSLSUPPORT__
    void sslErrors ( QNetworkReply*, QList<QSslError> );
#endif
    void networkAccessibleChanged ( QNetworkAccessManager::NetworkAccessibility );
    void networkSessionConnected();

    void localReplyTimeOut();
    void localReadyRead();
    void localUpdateUploadProgress ( qint64 bytesSent, qint64 bytesTotal );
    void localUpdateDownloadProgress ( qint64 bytesReceived, qint64 bytesTotal );

private:
    QQtWebAccessSessionManager* manager;
};

#endif // QQTWEBWORKCLIENT_H
