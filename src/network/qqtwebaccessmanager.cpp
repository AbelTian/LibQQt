#include "qqtwebaccessmanager.h"
#include "qqtcore.h"

/**
 *  QQtWebAccessCookieJar
 */

QQtWebAccessCookieJar::QQtWebAccessCookieJar ( QObject* parent ) : QNetworkCookieJar ( parent )
{

}

QQtWebAccessCookieJar::~QQtWebAccessCookieJar()
{

}

void QQtWebAccessCookieJar::setCookieJarName ( const QString& name )
{
    setObjectName ( name );
}

QString QQtWebAccessCookieJar::cookieJarName() const
{
    return objectName();
}

bool QQtWebAccessCookieJar::hasCookieForUrl ( const QNetworkCookie& cookie, const QUrl& url )
{
    QList<QNetworkCookie> cookieList = cookiesForUrl ( url );
    QListIterator<QNetworkCookie> itor ( cookieList );
    bool hasCookieName = false;

    while ( itor.hasNext() )
    {
        QNetworkCookie c0 = itor.next();

        if ( c0.name() == cookie.name() )
        {
            hasCookieName = true;
            break;
        }
    }

    return hasCookieName;
}

bool QQtWebAccessCookieJar::insertCookieForUrl ( const QNetworkCookie& cookie, const QUrl& url )
{
    QList<QNetworkCookie> cookieList = cookiesForUrl ( url );

    QListIterator<QNetworkCookie> itor ( cookieList );
    bool hasCookieName = false;

    while ( itor.hasNext() )
    {
        QNetworkCookie c0 = itor.next();

        if ( c0.name() == cookie.name() )
        {
            hasCookieName = true;
            break;
        }
    }

    if ( hasCookieName )
        //if contains cookie [name]
        updateCookieForUrl ( cookie, url );
    else
        //if not contains cookie [name]
        cookieList.push_back ( cookie );

    return setCookiesForUrl ( cookieList, url );
}

bool QQtWebAccessCookieJar::updateCookieForUrl ( const QNetworkCookie& cookie, const QUrl& url )
{
    QList<QNetworkCookie> cookieList = cookiesForUrl ( url );

    QMutableListIterator<QNetworkCookie> itor ( cookieList );

    while ( itor.hasNext() )
    {
        QNetworkCookie& c0 = itor.next();

        if ( c0.name() == cookie.name() )
        {
            c0.setValue ( cookie.value() );
            break;
        }
    }

    return setCookiesForUrl ( cookieList, url );
}

bool QQtWebAccessCookieJar::deleteCookieForUrl ( const QNetworkCookie& cookie, const QUrl& url )
{
    QList<QNetworkCookie> cookieList = cookiesForUrl ( url );

    QListIterator<QNetworkCookie> itor ( cookieList );

    bool hasCookieName = false;
    QNetworkCookie c0;

    while ( itor.hasNext() )
    {
        //这里不可以用引用，否则空引用，引发remove失败。
        c0 = itor.next();

        if ( c0.name() == cookie.name() )
        {
            hasCookieName = true;
            break;
        }
    }

    if ( hasCookieName )
        cookieList.removeOne ( c0 );

    return setCookiesForUrl ( cookieList, url );
}

bool QQtWebAccessCookieJar::setCookiesForUrl ( const QList<QNetworkCookie>& cookieList, const QUrl& url )
{
    return setCookiesFromUrl ( cookieList, url );
}

QList<QNetworkCookie> QQtWebAccessCookieJar::parseCookies ( const QByteArray& cookieString )
{
    QList<QByteArray> cookieBytesList = cookieString.split ( ';' );
    QList<QNetworkCookie> cookieList;
    QListIterator<QByteArray> itor ( cookieBytesList );

    while ( itor.hasNext() )
    {
        QByteArray cookieBytes = itor.next();
        QList<QByteArray> cookieNameAndValue = cookieBytes.split ( '=' );
        QNetworkCookie cookie;
        cookie.setName ( cookieNameAndValue[0].trimmed() );

        //HttpOnly;
        if ( cookieNameAndValue.size() > 1 )
            cookie.setValue ( cookieNameAndValue[1].trimmed() );

        cookieList.push_back ( cookie );
    }

    return cookieList;
}

/**
 *  QQtWebAccessSession
 */

QQtWebAccessSession::QQtWebAccessSession ( QObject* parent ) :
    QObject ( parent )
{
    m_pTimer = new QTimer ( this );
    m_pTimer->setSingleShot ( true );
    m_pTimer->setInterval ( 10000 );

    mErrorCode = QNetworkReply::NoError;
}

QQtWebAccessSession::~QQtWebAccessSession() {}


QTimer* QQtWebAccessSession::getTimer()
{
    return m_pTimer;
}

QString QQtWebAccessSession::getWebAccessUrl()
{
    return mNetworkRequest.url().toString();
}

void QQtWebAccessSession::setWebAccessUrl ( QString strUrl )
{
    m_strUrl = strUrl;
    mNetworkRequest.setUrl ( QUrl ( m_strUrl ) );
}

QNetworkRequest& QQtWebAccessSession::webAccessRequest()
{
    return mNetworkRequest;
}

QNetworkReply* QQtWebAccessSession::getWebAccessReply()
{
    return m_pNetworkReply;
}

void QQtWebAccessSession::setWebAccessReply ( QNetworkReply* reply )
{
    m_pNetworkReply = reply;
}

QString QQtWebAccessSession::getWebAccessSessionName()
{
    return m_strSessionName;
}

void QQtWebAccessSession::setWebAccessSessionName ( QString strSessionName )
{
    m_strSessionName = strSessionName;
}

QNetworkReply::NetworkError QQtWebAccessSession::getErrorCode()
{
    return mErrorCode;
}

void QQtWebAccessSession::setErrorCode ( QNetworkReply::NetworkError error )
{
    mErrorCode = error;
}

/**
 *  QQtWebAccessSessionManager
 */

QNetworkReply* QQtWebAccessSessionManager::getReplyHandlerByUrl ( QString& strUrl )
{
    QQtWebAccessSession* s0 = NULL;
    QListIterator<QQtWebAccessSession*> itor ( m_listWebAccessSession );

    while ( itor.hasNext() )
    {
        QQtWebAccessSession* s1 = itor.next();

        if ( s1->getWebAccessUrl() == strUrl )
        {
            s0 = s1;
            break;
        }
    }

    if ( !s0 )
        return NULL;

    return s0->getWebAccessReply();
}

QString QQtWebAccessSessionManager::getSessionNameByUrl ( QString& strUrl )
{
    QQtWebAccessSession* s0 = NULL;
    QListIterator<QQtWebAccessSession*> itor ( m_listWebAccessSession );

    while ( itor.hasNext() )
    {
        QQtWebAccessSession* s1 = itor.next();

        if ( s1->getWebAccessUrl() == strUrl )
        {
            s0 = s1;
            break;
        }
    }

    if ( !s0 )
        return QString();

    return s0->getWebAccessSessionName();
}

QQtWebAccessSession* QQtWebAccessSessionManager::getSessionByUrl ( QString& strUrl )
{
    QQtWebAccessSession* s0 = NULL;
    QListIterator<QQtWebAccessSession*> itor ( m_listWebAccessSession );

    while ( itor.hasNext() )
    {
        QQtWebAccessSession* s1 = itor.next();

        if ( s1->getWebAccessUrl() == strUrl )
        {
            s0 = s1;
            break;
        }
    }

    return s0;
}

QString QQtWebAccessSessionManager::getRequestUrlByReply ( QNetworkReply* reply )
{
    QQtWebAccessSession* s0 = NULL;
    QListIterator<QQtWebAccessSession*> itor ( m_listWebAccessSession );

    while ( itor.hasNext() )
    {
        QQtWebAccessSession* s1 = itor.next();

        if ( s1->getWebAccessReply() == reply )
        {
            s0 = s1;
            break;
        }
    }

    if ( !s0 )
        return QString();

    return s0->getWebAccessUrl();
}

QString QQtWebAccessSessionManager::getSessionNameByReply ( QNetworkReply* reply )
{
    QQtWebAccessSession* s0 = NULL;
    QListIterator<QQtWebAccessSession*> itor ( m_listWebAccessSession );

    while ( itor.hasNext() )
    {
        QQtWebAccessSession* s1 = itor.next();

        if ( s1->getWebAccessReply() == reply )
        {
            s0 = s1;
            break;
        }
    }

    if ( !s0 )
        return QString();

    return s0->getWebAccessSessionName();
}

QQtWebAccessSession* QQtWebAccessSessionManager::getSessionByReply ( QNetworkReply* reply )
{
    QQtWebAccessSession* s0 = NULL;
    QListIterator<QQtWebAccessSession*> itor ( m_listWebAccessSession );

    while ( itor.hasNext() )
    {
        QQtWebAccessSession* s1 = itor.next();

        if ( s1->getWebAccessReply() == reply )
        {
            s0 = s1;
            break;
        }
    }

    return s0;
}

QNetworkReply* QQtWebAccessSessionManager::getReplyHandlerBySessionName ( QString& strSessionName )
{
    QQtWebAccessSession* s0 = NULL;
    QListIterator<QQtWebAccessSession*> itor ( m_listWebAccessSession );

    while ( itor.hasNext() )
    {
        QQtWebAccessSession* s1 = itor.next();

        if ( s1->getWebAccessSessionName() == strSessionName )
        {
            s0 = s1;
            break;
        }
    }

    if ( !s0 )
        return NULL;

    return s0->getWebAccessReply();
}

QString QQtWebAccessSessionManager::getRequestUrlBySessionName ( QString& strSessionName )
{
    QQtWebAccessSession* s0 = NULL;
    QListIterator<QQtWebAccessSession*> itor ( m_listWebAccessSession );

    while ( itor.hasNext() )
    {
        QQtWebAccessSession* s1 = itor.next();

        if ( s1->getWebAccessSessionName() == strSessionName )
        {
            s0 = s1;
            break;
        }
    }

    if ( !s0 )
        return QString();

    return s0->getWebAccessUrl();
}

QQtWebAccessSession* QQtWebAccessSessionManager::getSessionBySessionName ( QString& strSessionName )
{
    QQtWebAccessSession* s0 = NULL;
    QListIterator<QQtWebAccessSession*> itor ( m_listWebAccessSession );

    while ( itor.hasNext() )
    {
        QQtWebAccessSession* s1 = itor.next();

        if ( s1->getWebAccessSessionName() == strSessionName )
        {
            s0 = s1;
            break;
        }
    }

    return s0;
}

QNetworkReply* QQtWebAccessSessionManager::getReplyHandlerByTimer ( QTimer* timer )
{
    QQtWebAccessSession* s0 = NULL;
    QListIterator<QQtWebAccessSession*> itor ( m_listWebAccessSession );

    while ( itor.hasNext() )
    {
        QQtWebAccessSession* s1 = itor.next();

        if ( s1->getTimer() == timer )
        {
            s0 = s1;
            break;
        }
    }

    if ( !s0 )
        return NULL;

    return s0->getWebAccessReply();
}

QString QQtWebAccessSessionManager::getRequestUrlByTimer ( QTimer* timer )
{
    QQtWebAccessSession* s0 = NULL;
    QListIterator<QQtWebAccessSession*> itor ( m_listWebAccessSession );

    while ( itor.hasNext() )
    {
        QQtWebAccessSession* s1 = itor.next();

        if ( s1->getTimer() == timer )
        {
            s0 = s1;
            break;
        }
    }

    if ( !s0 )
        return NULL;

    return s0->getWebAccessUrl();
}

QQtWebAccessSession* QQtWebAccessSessionManager::getSessionByTimer ( QTimer* timer )
{
    QQtWebAccessSession* s0 = NULL;
    QListIterator<QQtWebAccessSession*> itor ( m_listWebAccessSession );

    while ( itor.hasNext() )
    {
        QQtWebAccessSession* s1 = itor.next();

        if ( s1->getTimer() == timer )
        {
            s0 = s1;
            break;
        }
    }

    return s0;
}

QNetworkReply* QQtWebAccessSessionManager::getReplyHandler ( QQtWebAccessSession* session )
{
    if ( !session )
        return NULL;

    return session->getWebAccessReply();
}

QString QQtWebAccessSessionManager::getRequestUrl ( QQtWebAccessSession* session )
{
    if ( !session )
        return QString();

    return session->getWebAccessUrl();
}

QString QQtWebAccessSessionManager::getSessionName ( QQtWebAccessSession* session )
{
    if ( !session )
        return QString();

    return session->getWebAccessSessionName();
}

/**
 *  QQtWebAccessManager
 */
QQtWebAccessManager::QQtWebAccessManager ( QObject* parent ) : QNetworkAccessManager ( parent )
{
    manager = new QQtWebAccessSessionManager ( this );

    connect ( this, SIGNAL ( finished ( QNetworkReply* ) ),
              this, SLOT ( finished ( QNetworkReply* ) ) );

    connect ( this, SIGNAL ( authenticationRequired ( QNetworkReply*, QAuthenticator* ) ),
              this, SLOT ( authenticationRequired ( QNetworkReply*, QAuthenticator* ) ) );

    connect ( this, SIGNAL ( proxyAuthenticationRequired ( QNetworkProxy, QAuthenticator* ) ),
              this, SLOT ( proxyAuthenticationRequired ( QNetworkProxy, QAuthenticator* ) ) );

#ifdef __SSLSUPPORT__
    connect ( this,  SIGNAL ( sslErrors ( QNetworkReply*, QList<QSslError> ) ),
              this, SLOT ( sslErrors ( QNetworkReply*, QList<QSslError> ) ) );
#endif

    connect ( this, SIGNAL ( networkAccessibleChanged ( QNetworkAccessManager::NetworkAccessibility ) ),
              this, SLOT ( networkAccessibleChanged ( QNetworkAccessManager::NetworkAccessibility ) ) );

    connect ( this, SIGNAL ( networkSessionConnected() ),
              this, SLOT ( networkSessionConnected() ) );

    initUserAgent();
    initContentType();

    setTimerInterval();

    //在用户业务当中，如果有必要setCookieJar ( cookieJar );
}

QQtWebAccessSessionManager* QQtWebAccessManager::getWebAccessSessionManager()
{
    return manager;
}

void QQtWebAccessManager::sendGetRequest ( QQtWebAccessSession* session )
{
    QTimer* timer = session->getTimer();
    timer->setInterval ( mTimerInterval );
    connect ( timer, SIGNAL ( timeout() ),
              this, SLOT ( localReplyTimeOut() ) ); //超时信号

    QNetworkRequest& netRequest = session->webAccessRequest();
    setRequestHeader ( netRequest );

    QNetworkReply* reply = get ( netRequest );
    session->setWebAccessReply ( reply ); //发起get请求
    /*下面关联信号和槽*/

    /*下载完成后开始一阵一阵堆取数据*/
    connect ( reply, SIGNAL ( readyRead() ),
              this, SLOT ( localReadyRead() ) );

    /*有可用数据时 */
    connect ( reply, SIGNAL ( downloadProgress ( qint64, qint64 ) ),
              this, SLOT ( localUpdateDownloadProgress ( qint64, qint64 ) ) );
    connect ( reply, SIGNAL ( uploadProgress ( qint64, qint64 ) ),
              this, SLOT ( localUpdateUploadProgress ( qint64, qint64 ) ) );

    //ignore
//    connect ( s0->m_pNetworkReply, SIGNAL ( finished() ),
//              this, SLOT ( finished(QNetworkReply*); ) ); //请求完成信号

    timer->start();
}

QQtWebAccessSession* QQtWebAccessManager::sendGetRequest ( QString strUrl )
{
    QNetworkRequest netRequest;
    netRequest.setUrl ( QUrl ( strUrl ) ); //地址信息
    QQtWebAccessSession* session = sendGetRequest ( netRequest );
    return session;
}

//当即使用有效，后续使用无效。
QList<QQtWebAccessSession*> QQtWebAccessManager::sendGetRequests ( QStringList& strUrl )
{
    QStringListIterator itor ( strUrl );
    QList<QQtWebAccessSession*> sessionList;

    while ( itor.hasNext() )
    {
        QString  url = itor.next();
        QQtWebAccessSession* session = sendGetRequest ( url );
        sessionList.push_back ( session );
    }

    return sessionList;
}

QQtWebAccessSession* QQtWebAccessManager::sendGetRequest ( const QNetworkRequest& netRequest )
{
    QQtWebAccessSession* session = manager->newWebAccessSession();
    session->webAccessRequest() = netRequest;
    sendGetRequest ( session );
    return session;
}

//当即使用有效，后续使用无效。
QList<QQtWebAccessSession*> QQtWebAccessManager::sendGetRequests ( const QList<QNetworkRequest>& netRequests )
{
    QListIterator<QNetworkRequest> itor ( netRequests );
    QList<QQtWebAccessSession*> sessionList;

    while ( itor.hasNext() )
    {
        QNetworkRequest  req = itor.next();
        QQtWebAccessSession* session = sendGetRequest ( req );
        sessionList.push_back ( session );
    }

    return sessionList;
}

QQtWebAccessSession* QQtWebAccessManager::sendHeadRequest ( const QNetworkRequest& request )
{
    QQtWebAccessSession* session = manager->newWebAccessSession();
    session->webAccessRequest() = request;

    QTimer* timer = session->getTimer();
    timer->setInterval ( mTimerInterval );
    connect ( timer, SIGNAL ( timeout() ),
              this, SLOT ( localReplyTimeOut() ) ); //超时信号

    QNetworkRequest& netRequest = session->webAccessRequest();
    setRequestHeader ( netRequest );

    QNetworkReply* reply = head ( netRequest );
    session->setWebAccessReply ( reply ); //发起get请求
    /*下面关联信号和槽*/

    /*下载完成后开始一阵一阵堆取数据*/
    connect ( reply, SIGNAL ( readyRead() ),
              this, SLOT ( localReadyRead() ) );

    /*有可用数据时 */
    connect ( reply, SIGNAL ( downloadProgress ( qint64, qint64 ) ),
              this, SLOT ( localUpdateDownloadProgress ( qint64, qint64 ) ) );
    connect ( reply, SIGNAL ( uploadProgress ( qint64, qint64 ) ),
              this, SLOT ( localUpdateUploadProgress ( qint64, qint64 ) ) );

    //ignore
//    connect ( s0->m_pNetworkReply, SIGNAL ( finished() ),
//              this, SLOT ( finished(QNetworkReply*); ) ); //请求完成信号

    timer->start();

    return session;
}

QQtWebAccessSession* QQtWebAccessManager::sendPostRequest ( const QNetworkRequest& request, QIODevice* data )
{
    QQtWebAccessSession* session = manager->newWebAccessSession();
    session->webAccessRequest() = request;

    QTimer* timer = session->getTimer();
    timer->setInterval ( mTimerInterval );
    connect ( timer, SIGNAL ( timeout() ),
              this, SLOT ( localReplyTimeOut() ) ); //超时信号

    QNetworkRequest& netRequest = session->webAccessRequest();
    setRequestHeader ( netRequest );

    QNetworkReply* reply = post ( netRequest, data );
    session->setWebAccessReply ( reply ); //发起get请求
    /*下面关联信号和槽*/

    /*下载完成后开始一阵一阵堆取数据*/
    connect ( reply, SIGNAL ( readyRead() ),
              this, SLOT ( localReadyRead() ) );

    /*有可用数据时 */
    connect ( reply, SIGNAL ( downloadProgress ( qint64, qint64 ) ),
              this, SLOT ( localUpdateDownloadProgress ( qint64, qint64 ) ) );
    connect ( reply, SIGNAL ( uploadProgress ( qint64, qint64 ) ),
              this, SLOT ( localUpdateUploadProgress ( qint64, qint64 ) ) );

    //ignore
//    connect ( s0->m_pNetworkReply, SIGNAL ( finished() ),
//              this, SLOT ( finished(QNetworkReply*); ) ); //请求完成信号

    timer->start();

    return session;
}

QQtWebAccessSession* QQtWebAccessManager::sendPostRequest ( const QNetworkRequest& request, const QByteArray& data )
{
    QQtWebAccessSession* session = manager->newWebAccessSession();
    session->webAccessRequest() = request;

    QTimer* timer = session->getTimer();
    timer->setInterval ( mTimerInterval );
    connect ( timer, SIGNAL ( timeout() ),
              this, SLOT ( localReplyTimeOut() ) ); //超时信号

    QNetworkRequest& netRequest = session->webAccessRequest();
    setRequestHeader ( netRequest );

    ////http body部分，可封装参数信息
    QNetworkReply* reply = post ( netRequest, data );
    session->setWebAccessReply ( reply ); //发起get请求
    /*下面关联信号和槽*/

    /*下载完成后开始一阵一阵堆取数据*/
    connect ( reply, SIGNAL ( readyRead() ),
              this, SLOT ( localReadyRead() ) );

    /*有可用数据时 */
    connect ( reply, SIGNAL ( downloadProgress ( qint64, qint64 ) ),
              this, SLOT ( localUpdateDownloadProgress ( qint64, qint64 ) ) );
    connect ( reply, SIGNAL ( uploadProgress ( qint64, qint64 ) ),
              this, SLOT ( localUpdateUploadProgress ( qint64, qint64 ) ) );

    //ignore
//    connect ( s0->m_pNetworkReply, SIGNAL ( finished() ),
//              this, SLOT ( finished(QNetworkReply*); ) ); //请求完成信号

    timer->start();

    return session;
}

QQtWebAccessSession* QQtWebAccessManager::sendPostRequest ( const QNetworkRequest& request, QHttpMultiPart* multiPart )
{
    QQtWebAccessSession* session = manager->newWebAccessSession();
    session->webAccessRequest() = request;

    QTimer* timer = session->getTimer();
    timer->setInterval ( mTimerInterval );
    connect ( timer, SIGNAL ( timeout() ),
              this, SLOT ( localReplyTimeOut() ) ); //超时信号

    QNetworkRequest& netRequest = session->webAccessRequest();
    setRequestHeader ( netRequest );

    QNetworkReply* reply = post ( netRequest, multiPart );
    session->setWebAccessReply ( reply ); //发起get请求
    /*下面关联信号和槽*/

    /*下载完成后开始一阵一阵堆取数据*/
    connect ( reply, SIGNAL ( readyRead() ),
              this, SLOT ( localReadyRead() ) );

    /*有可用数据时 */
    connect ( reply, SIGNAL ( downloadProgress ( qint64, qint64 ) ),
              this, SLOT ( localUpdateDownloadProgress ( qint64, qint64 ) ) );
    connect ( reply, SIGNAL ( uploadProgress ( qint64, qint64 ) ),
              this, SLOT ( localUpdateUploadProgress ( qint64, qint64 ) ) );

    //ignore
//    connect ( s0->m_pNetworkReply, SIGNAL ( finished() ),
//              this, SLOT ( finished(QNetworkReply*); ) ); //请求完成信号

    timer->start();

    return session;
}

QQtWebAccessSession* QQtWebAccessManager::sendPutRequest ( const QNetworkRequest& request, QIODevice* data )
{
    QQtWebAccessSession* session = manager->newWebAccessSession();
    session->webAccessRequest() = request;

    QTimer* timer = session->getTimer();
    timer->setInterval ( mTimerInterval );
    connect ( timer, SIGNAL ( timeout() ),
              this, SLOT ( localReplyTimeOut() ) ); //超时信号

    QNetworkRequest& netRequest = session->webAccessRequest();
    setRequestHeader ( netRequest );

    QNetworkReply* reply = put ( netRequest, data );
    session->setWebAccessReply ( reply ); //发起get请求
    /*下面关联信号和槽*/

    /*下载完成后开始一阵一阵堆取数据*/
    connect ( reply, SIGNAL ( readyRead() ),
              this, SLOT ( localReadyRead() ) );

    /*有可用数据时 */
    connect ( reply, SIGNAL ( downloadProgress ( qint64, qint64 ) ),
              this, SLOT ( localUpdateDownloadProgress ( qint64, qint64 ) ) );
    connect ( reply, SIGNAL ( uploadProgress ( qint64, qint64 ) ),
              this, SLOT ( localUpdateUploadProgress ( qint64, qint64 ) ) );

    //ignore
//    connect ( s0->m_pNetworkReply, SIGNAL ( finished() ),
//              this, SLOT ( finished(QNetworkReply*); ) ); //请求完成信号

    timer->start();

    return session;
}

QQtWebAccessSession* QQtWebAccessManager::sendPutRequest ( const QNetworkRequest& request, const QByteArray& data )
{
    QQtWebAccessSession* session = manager->newWebAccessSession();
    session->webAccessRequest() = request;

    QTimer* timer = session->getTimer();
    timer->setInterval ( mTimerInterval );
    connect ( timer, SIGNAL ( timeout() ),
              this, SLOT ( localReplyTimeOut() ) ); //超时信号

    QNetworkRequest& netRequest = session->webAccessRequest();
    setRequestHeader ( netRequest );

    QNetworkReply* reply = put ( netRequest, data );
    session->setWebAccessReply ( reply ); //发起get请求
    /*下面关联信号和槽*/

    /*下载完成后开始一阵一阵堆取数据*/
    connect ( reply, SIGNAL ( readyRead() ),
              this, SLOT ( localReadyRead() ) );

    /*有可用数据时 */
    connect ( reply, SIGNAL ( downloadProgress ( qint64, qint64 ) ),
              this, SLOT ( localUpdateDownloadProgress ( qint64, qint64 ) ) );
    connect ( reply, SIGNAL ( uploadProgress ( qint64, qint64 ) ),
              this, SLOT ( localUpdateUploadProgress ( qint64, qint64 ) ) );

    //ignore
//    connect ( s0->m_pNetworkReply, SIGNAL ( finished() ),
//              this, SLOT ( finished(QNetworkReply*); ) ); //请求完成信号

    timer->start();

    return session;
}

QQtWebAccessSession* QQtWebAccessManager::sendPutRequest ( const QNetworkRequest& request, QHttpMultiPart* multiPart )
{
    QQtWebAccessSession* session = manager->newWebAccessSession();
    session->webAccessRequest() = request;

    QTimer* timer = session->getTimer();
    timer->setInterval ( mTimerInterval );
    connect ( timer, SIGNAL ( timeout() ),
              this, SLOT ( localReplyTimeOut() ) ); //超时信号

    QNetworkRequest& netRequest = session->webAccessRequest();
    setRequestHeader ( netRequest );

    QNetworkReply* reply = put ( netRequest, multiPart );
    session->setWebAccessReply ( reply ); //发起get请求
    /*下面关联信号和槽*/

    /*下载完成后开始一阵一阵堆取数据*/
    connect ( reply, SIGNAL ( readyRead() ),
              this, SLOT ( localReadyRead() ) );

    /*有可用数据时 */
    connect ( reply, SIGNAL ( downloadProgress ( qint64, qint64 ) ),
              this, SLOT ( localUpdateDownloadProgress ( qint64, qint64 ) ) );
    connect ( reply, SIGNAL ( uploadProgress ( qint64, qint64 ) ),
              this, SLOT ( localUpdateUploadProgress ( qint64, qint64 ) ) );

    //ignore
//    connect ( s0->m_pNetworkReply, SIGNAL ( finished() ),
//              this, SLOT ( finished(QNetworkReply*); ) ); //请求完成信号

    timer->start();

    return session;
}

QQtWebAccessSession* QQtWebAccessManager::sendDeleteResourceRequest ( const QNetworkRequest& request )
{
    QQtWebAccessSession* session = manager->newWebAccessSession();
    session->webAccessRequest() = request;

    QTimer* timer = session->getTimer();
    timer->setInterval ( mTimerInterval );
    connect ( timer, SIGNAL ( timeout() ),
              this, SLOT ( localReplyTimeOut() ) ); //超时信号

    QNetworkRequest& netRequest = session->webAccessRequest();
    setRequestHeader ( netRequest );

    QNetworkReply* reply = deleteResource ( netRequest );
    session->setWebAccessReply ( reply ); //发起get请求
    /*下面关联信号和槽*/

    /*下载完成后开始一阵一阵堆取数据*/
    connect ( reply, SIGNAL ( readyRead() ),
              this, SLOT ( localReadyRead() ) );

    /*有可用数据时 */
    connect ( reply, SIGNAL ( downloadProgress ( qint64, qint64 ) ),
              this, SLOT ( localUpdateDownloadProgress ( qint64, qint64 ) ) );
    connect ( reply, SIGNAL ( uploadProgress ( qint64, qint64 ) ),
              this, SLOT ( localUpdateUploadProgress ( qint64, qint64 ) ) );

    //ignore
//    connect ( s0->m_pNetworkReply, SIGNAL ( finished() ),
//              this, SLOT ( finished(QNetworkReply*); ) ); //请求完成信号

    timer->start();

    return session;
}

QQtWebAccessSession* QQtWebAccessManager::sendCustomRequest ( const QNetworkRequest& request, const QByteArray& verb,
                                                              QIODevice* data )
{
    QQtWebAccessSession* session = manager->newWebAccessSession();
    session->webAccessRequest() = request;

    QTimer* timer = session->getTimer();
    timer->setInterval ( mTimerInterval );
    connect ( timer, SIGNAL ( timeout() ),
              this, SLOT ( localReplyTimeOut() ) ); //超时信号

    QNetworkRequest& netRequest = session->webAccessRequest();
    setRequestHeader ( netRequest );

    QNetworkReply* reply = QNetworkAccessManager::sendCustomRequest ( netRequest, verb, data );
    session->setWebAccessReply ( reply ); //发起get请求
    /*下面关联信号和槽*/

    /*下载完成后开始一阵一阵堆取数据*/
    connect ( reply, SIGNAL ( readyRead() ),
              this, SLOT ( localReadyRead() ) );

    /*有可用数据时 */
    connect ( reply, SIGNAL ( downloadProgress ( qint64, qint64 ) ),
              this, SLOT ( localUpdateDownloadProgress ( qint64, qint64 ) ) );
    connect ( reply, SIGNAL ( uploadProgress ( qint64, qint64 ) ),
              this, SLOT ( localUpdateUploadProgress ( qint64, qint64 ) ) );

    //ignore
//    connect ( s0->m_pNetworkReply, SIGNAL ( finished() ),
//              this, SLOT ( finished(QNetworkReply*); ) ); //请求完成信号

    timer->start();

    return session;
}

int QQtWebAccessManager::getUserAgentCount()
{
    return mUserAgentList.size();
}

QList<QByteArray> QQtWebAccessManager::getUserAgentList()
{
    return mUserAgentList;
}

QByteArray QQtWebAccessManager::getUserAgent ( int index )
{
    if ( index < 0 || index > mUserAgentList.size() - 1 )
    {
        return mUserAgentList[0];
    }
    return mUserAgentList[index];
}

void QQtWebAccessManager::setUserAgent ( int index )
{
    if ( index < 0 || index > mUserAgentList.size() - 1 )
    {
        mUserAgent = mUserAgentList[0];
        return;
    }
    mUserAgent = mUserAgentList[index];
}

void QQtWebAccessManager::setUserAgent ( const QByteArray& agent )
{
    mUserAgent = agent;
}

QByteArray QQtWebAccessManager::userAgent()
{
    return mUserAgent;
}

int QQtWebAccessManager::getContentTypeCount()
{
    return mContentTypeList.size();
}

QList<QByteArray> QQtWebAccessManager::getContentTypeList()
{
    return mContentTypeList;
}

QByteArray QQtWebAccessManager::getContentType ( int index )
{
    if ( index < 0 || index > mContentTypeList.size() - 1 )
    {
        return mContentTypeList[0];
    }
    return mContentTypeList[index];
}

void QQtWebAccessManager::setContentType ( int index )
{
    if ( index < 0 || index > mContentTypeList.size() - 1 )
    {
        mContentType = mContentTypeList[0];
        return;
    }
    mContentType = mContentTypeList[index];
}

void QQtWebAccessManager::setContentType ( const QByteArray& type )
{
    mContentType = type;
}

QByteArray QQtWebAccessManager::contentType()
{
    return mContentType;
}

void QQtWebAccessManager::setTimerInterval ( int millsecond )
{
    mTimerInterval = millsecond;
}

int QQtWebAccessManager::timerInterval()
{
    return mTimerInterval;
}

#if defined( __DARWIN__ ) || defined( __LINUX__ )
#if QT_VERSION > QT_VERSION_CHECK(5,7,1)

QQtWebAccessSession* QQtWebAccessManager::sendCustomRequest ( const QNetworkRequest& request, const QByteArray& verb,
                                                              const QByteArray& data )
{
    QQtWebAccessSession* session = manager->newWebAccessSession();
    session->webAccessRequest() = request;

    QTimer* timer = session->getTimer();
    timer->setInterval ( mTimerInterval );
    connect ( timer, SIGNAL ( timeout() ),
              this, SLOT ( localReplyTimeOut() ) ); //超时信号

    QNetworkRequest& netRequest = session->webAccessRequest();
    setRequestHeader ( netRequest );

    QNetworkReply* reply = QNetworkAccessManager::sendCustomRequest ( netRequest, verb, data );
    session->setWebAccessReply ( reply ); //发起get请求
    /*下面关联信号和槽*/

    /*下载完成后开始一阵一阵堆取数据*/
    connect ( reply, SIGNAL ( readyRead() ),
              this, SLOT ( localReadyRead() ) );

    /*有可用数据时 */
    connect ( reply, SIGNAL ( downloadProgress ( qint64, qint64 ) ),
              this, SLOT ( localUpdateDownloadProgress ( qint64, qint64 ) ) );
    connect ( reply, SIGNAL ( uploadProgress ( qint64, qint64 ) ),
              this, SLOT ( localUpdateUploadProgress ( qint64, qint64 ) ) );

    //ignore
//    connect ( s0->m_pNetworkReply, SIGNAL ( finished() ),
//              this, SLOT ( finished(QNetworkReply*); ) ); //请求完成信号

    timer->start();

    return session;
}

QQtWebAccessSession* QQtWebAccessManager::sendCustomRequest ( const QNetworkRequest& request, const QByteArray& verb,
                                                              QHttpMultiPart* multiPart )
{
    QQtWebAccessSession* session = manager->newWebAccessSession();
    session->webAccessRequest() = request;

    QTimer* timer = session->getTimer();
    timer->setInterval ( mTimerInterval );
    connect ( timer, SIGNAL ( timeout() ),
              this, SLOT ( localReplyTimeOut() ) ); //超时信号

    QNetworkRequest& netRequest = session->webAccessRequest();
    setRequestHeader ( netRequest );

    QNetworkReply* reply = QNetworkAccessManager::sendCustomRequest ( netRequest, verb, multiPart );
    session->setWebAccessReply ( reply ); //发起get请求
    /*下面关联信号和槽*/

    /*下载完成后开始一阵一阵堆取数据*/
    connect ( reply, SIGNAL ( readyRead() ),
              this, SLOT ( localReadyRead() ) );

    /*有可用数据时 */
    connect ( reply, SIGNAL ( downloadProgress ( qint64, qint64 ) ),
              this, SLOT ( localUpdateDownloadProgress ( qint64, qint64 ) ) );
    connect ( reply, SIGNAL ( uploadProgress ( qint64, qint64 ) ),
              this, SLOT ( localUpdateUploadProgress ( qint64, qint64 ) ) );

    //ignore
//    connect ( s0->m_pNetworkReply, SIGNAL ( finished() ),
//              this, SLOT ( finished(QNetworkReply*); ) ); //请求完成信号

    timer->start();

    return session;
}
#endif
#endif

void QQtWebAccessManager::finished ( QNetworkReply* reply )
{
    //clear resource
    QQtWebAccessSession* s0 = manager->getSessionByReply ( reply );
    //pline() << reply << s0;

    if ( !s0 )
        return;

    //pline() << s0->getWebAccessReply() << s0->getTimer();
    emit replyFinished ( s0 );

    s0->getTimer()->stop();
    s0->getWebAccessReply()->deleteLater();
    manager->removeWebAccessSession ( s0 );
}

void QQtWebAccessManager::authenticationRequired ( QNetworkReply* r, QAuthenticator* a )
{
    pline() << r << a;
}

void QQtWebAccessManager::proxyAuthenticationRequired ( QNetworkProxy p, QAuthenticator* a )
{
    //pline() << p.hostName() << a;
}

#ifdef __SSLSUPPORT__
void QQtWebAccessManager::sslErrors ( QNetworkReply* r, QList<QSslError> e )
{
    //pline() << r << e.size();
}
#endif

void QQtWebAccessManager::networkAccessibleChanged ( QNetworkAccessManager::NetworkAccessibility a )
{
    //pline() << a;
}

void QQtWebAccessManager::networkSessionConnected()
{
    //pline();
}

void QQtWebAccessManager::localReplyTimeOut()
{
    QTimer* timer = ( QTimer* ) sender();
    pline() << timer;

    QQtWebAccessSession* s0 = manager->getSessionByTimer ( timer );

    if ( !s0 )
        return;

    s0->setErrorCode ( QNetworkReply::TimeoutError );

    emit replyTimeOut ( s0 ); //请求失败

    s0->getWebAccessReply()->abort();
    s0->getWebAccessReply()->deleteLater();
    manager->removeWebAccessSession ( s0 );
}

void QQtWebAccessManager::localReadyRead()
{
    QNetworkReply* obj = ( QNetworkReply* ) sender();
    //pline() << obj;
    QQtWebAccessSession* session = manager->getSessionByReply ( obj );
    emit readyRead ( session );
}

void QQtWebAccessManager::localUpdateUploadProgress ( qint64 bytesSent, qint64 bytesTotal )
{
    QNetworkReply* obj = ( QNetworkReply* ) sender();
    //pline() << obj;
    QQtWebAccessSession* session = manager->getSessionByReply ( obj );
    emit updateUploadProgress ( session, bytesSent, bytesTotal );
}

void QQtWebAccessManager::localUpdateDownloadProgress ( qint64 bytesReceived, qint64 bytesTotal )
{
    QNetworkReply* obj = ( QNetworkReply* ) sender();
    //pline() << obj;
    QQtWebAccessSession* session = manager->getSessionByReply ( obj );
    emit updateDownloadProgress ( session, bytesReceived, bytesTotal );
}

void QQtWebAccessManager::initUserAgent()
{
    mUserAgentList =
    {
        "",
        "Mozilla/5.0 (Macintosh; U; Intel Mac OS X 10_6_8; en-us) AppleWebKit/534.50 (KHTML, like Gecko) Version/5.1 Safari/534.50",
        "Mozilla/5.0 (Windows; U; Windows NT 6.1; en-us) AppleWebKit/534.50 (KHTML, like Gecko) Version/5.1 Safari/534.50",
        "Mozilla/5.0 (Windows NT 10.0; WOW64; rv:38.0) Gecko/20100101 Firefox/38.0",
        "Mozilla/5.0 (Windows NT 10.0; WOW64; Trident/7.0; .NET4.0C; .NET4.0E; .NET CLR 2.0.50727; .NET CLR 3.0.30729; .NET CLR 3.5.30729; InfoPath.3; rv:11.0) like Gecko",
        "Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; Trident/5.0)",
        "Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.0; Trident/4.0)",
        "Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.0)",
        "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1)",
        "Mozilla/5.0 (Macintosh; Intel Mac OS X 10.6; rv:2.0.1) Gecko/20100101 Firefox/4.0.1",
        "Mozilla/5.0 (Windows NT 6.1; rv:2.0.1) Gecko/20100101 Firefox/4.0.1",
        "Opera/9.80 (Macintosh; Intel Mac OS X 10.6.8; U; en) Presto/2.8.131 Version/11.11",
        "Opera/9.80 (Windows NT 6.1; U; en) Presto/2.8.131 Version/11.11",
        "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_7_0) AppleWebKit/535.11 (KHTML, like Gecko) Chrome/17.0.963.56 Safari/535.11",
        "Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1; Maxthon 2.0)",
        "Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1; TencentTraveler 4.0)",
        "Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1)",
        "Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1; The World)",
        "Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1; Trident/4.0; SE 2.X MetaSr 1.0; SE 2.X MetaSr 1.0; .NET CLR 2.0.50727; SE 2.X MetaSr 1.0)",
        "Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1; 360SE)",
        "Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1; Avant Browser)",
        "Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1)",
        "Mozilla/5.0 (iPhone; U; CPU iPhone OS 4_3_3 like Mac OS X; en-us) AppleWebKit/533.17.9 (KHTML, like Gecko) Version/5.0.2 Mobile/8J2 Safari/6533.18.5",
        "Mozilla/5.0 (iPod; U; CPU iPhone OS 4_3_3 like Mac OS X; en-us) AppleWebKit/533.17.9 (KHTML, like Gecko) Version/5.0.2 Mobile/8J2 Safari/6533.18.5",
        "Mozilla/5.0 (iPad; U; CPU OS 4_3_3 like Mac OS X; en-us) AppleWebKit/533.17.9 (KHTML, like Gecko) Version/5.0.2 Mobile/8J2 Safari/6533.18.5",
        "Mozilla/5.0 (Linux; U; Android 2.3.7; en-us; Nexus One Build/FRF91) AppleWebKit/533.1 (KHTML, like Gecko) Version/4.0 Mobile Safari/533.1",
        "MQQBrowser/26 Mozilla/5.0 (Linux; U; Android 2.3.7; zh-cn; MB200 Build/GRJ22; CyanogenMod-7) AppleWebKit/533.1 (KHTML, like Gecko) Version/4.0 Mobile Safari/533.1",
        "Opera/9.80 (Android 2.3.4; Linux; Opera Mobi/build-1107180945; U; en-GB) Presto/2.8.149 Version/11.10",
        "Mozilla/5.0 (Linux; U; Android 3.0; en-us; Xoom Build/HRI39) AppleWebKit/534.13 (KHTML, like Gecko) Version/4.0 Safari/534.13",
        "Mozilla/5.0 (BlackBerry; U; BlackBerry 9800; en) AppleWebKit/534.1+ (KHTML, like Gecko) Version/6.0.0.337 Mobile Safari/534.1+",
        "Mozilla/5.0 (hp-tablet; Linux; hpwOS/3.0.0; U; en-US) AppleWebKit/534.6 (KHTML, like Gecko) wOSBrowser/233.70 Safari/534.6 TouchPad/1.0",
        "Mozilla/5.0 (SymbianOS/9.4; Series60/5.0 NokiaN97-1/20.0.019; Profile/MIDP-2.1 Configuration/CLDC-1.1) AppleWebKit/525 (KHTML, like Gecko) BrowserNG/7.1.18124",
        "Mozilla/5.0 (compatible; MSIE 9.0; Windows Phone OS 7.5; Trident/5.0; IEMobile/9.0; HTC; Titan)",
        "UCWEB7.0.2.37/28/999",
        "NOKIA5700/ UCWEB7.0.2.37/28/999",
        "Openwave/ UCWEB7.0.2.37/28/999",
        "Mozilla/4.0 (compatible; MSIE 6.0; ) Opera/UCWEB7.0.2.37/28/999",
        //iPhone 6
        "Mozilla/6.0 (iPhone; CPU iPhone OS 8_0 like Mac OS X) AppleWebKit/536.26 (KHTML, like Gecko) Version/8.0 Mobile/10A5376e Safari/8536.25",
        //新版移动ua
        "Mozilla/5.0 (Linux;u;Android 4.2.2;zh-cn;) AppleWebKit/534.46 (KHTML,like Gecko) Version/5.1 Mobile Safari/10600.6.3 (compatible; Baiduspider/2.0; +http://www.baidu.com/search/spider.html)"
    };
    mUserAgent = mUserAgentList[0];
}

void QQtWebAccessManager::initContentType()
{
    mContentTypeList =
    {
        "application/x-www-form-urlencoded",
        "application/json",
        "application/xml",
        "multipart/form-data"
    };
    mContentType = mContentTypeList[0];
}

void QQtWebAccessManager::setRequestHeader ( QNetworkRequest& netRequest )
{

    QString strUrl = netRequest.url().toString();

    //ContentType
    netRequest.setHeader ( QNetworkRequest::ContentTypeHeader, mContentType );

    //User-Agent
    if ( !mUserAgent.isEmpty() )
        netRequest.setHeader ( QNetworkRequest::UserAgentHeader, mUserAgent );

    //CookieJar
    //getLocalCookieJar();
    //QWebAccessManager会自动处理CookieJar，用户留意内部数据即可。
    //Header、Body、CookieJar。

#ifdef __SSLSUPPORT__
    //SSL
    if ( strUrl.toLower().startsWith ( "https" ) ) //https请求，需ssl支持(下载openssl拷贝libeay32.dll和ssleay32.dll文件至Qt bin目录或程序运行目录)
    {
        QSslConfiguration sslConfig;
        sslConfig.setPeerVerifyMode ( QSslSocket::VerifyNone );
        sslConfig.setProtocol ( QSsl::TlsV1_1 );
        netRequest.setSslConfiguration ( sslConfig );
    }
#endif
}
