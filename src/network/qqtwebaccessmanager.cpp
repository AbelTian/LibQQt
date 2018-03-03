#include "qqtwebaccessmanager.h"
#include "qqtcore.h"


QQtWebAccessManager::QQtWebAccessManager ( QObject* parent ) : QNetworkAccessManager ( parent )
{
    manager = new QQtWebAccessSessionManager ( this );

    connect ( this, SIGNAL ( finished ( QNetworkReply* ) ),
              this, SLOT ( finished ( QNetworkReply* ) ) );

    connect ( this, SIGNAL ( authenticationRequired ( QNetworkReply*, QAuthenticator* ) ),
              this, SLOT ( authenticationRequired ( QNetworkReply*, QAuthenticator* ) ) );

    connect ( this, SIGNAL ( proxyAuthenticationRequired ( QNetworkProxy, QAuthenticator* ) ),
              this, SLOT ( proxyAuthenticationRequired ( QNetworkProxy, QAuthenticator* ) ) );

    connect ( this,  SIGNAL ( sslErrors ( QNetworkReply*, QList<QSslError> ) ),
              this, SLOT ( sslErrors ( QNetworkReply*, QList<QSslError> ) ) );

    connect ( this, SIGNAL ( networkAccessibleChanged ( QNetworkAccessManager::NetworkAccessibility ) ),
              this, SLOT ( networkAccessibleChanged ( QNetworkAccessManager::NetworkAccessibility ) ) );

    connect ( this, SIGNAL ( networkSessionConnected() ),
              this, SLOT ( networkSessionConnected() ) );

    //在用户业务当中，如果有必要setCookieJar ( cookieJar );
}

QQtWebAccessSessionManager* QQtWebAccessManager::getWebAccessSessionManager()
{
    return manager;
}

void QQtWebAccessManager::sendGetRequest ( QQtWebAccessSession* session )
{
    QTimer* timer = session->getTimer();
    connect ( timer, SIGNAL ( timeout() ),
              this, SLOT ( localReplyTimeOut() ) ); //超时信号

    QNetworkRequest& netRequest = session->webAccessRequest();
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
    netRequest.setHeader ( QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded" );
    netRequest.setUrl ( QUrl ( strUrl ) ); //地址信息

    if ( strUrl.toLower().startsWith ( "https" ) ) //https请求，需ssl支持(下载openssl拷贝libeay32.dll和ssleay32.dll文件至Qt bin目录或程序运行目录)
    {
        QSslConfiguration sslConfig;
        sslConfig.setPeerVerifyMode ( QSslSocket::VerifyNone );
        sslConfig.setProtocol ( QSsl::TlsV1_1 );
        netRequest.setSslConfiguration ( sslConfig );
    }

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
    connect ( timer, SIGNAL ( timeout() ),
              this, SLOT ( localReplyTimeOut() ) ); //超时信号

    QNetworkRequest& netRequest = session->webAccessRequest();
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
}

QQtWebAccessSession* QQtWebAccessManager::sendPostRequest ( const QNetworkRequest& request, QIODevice* data )
{
    QQtWebAccessSession* session = manager->newWebAccessSession();
    session->webAccessRequest() = request;

    QTimer* timer = session->getTimer();
    connect ( timer, SIGNAL ( timeout() ),
              this, SLOT ( localReplyTimeOut() ) ); //超时信号

    QNetworkRequest& netRequest = session->webAccessRequest();
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
}

QQtWebAccessSession* QQtWebAccessManager::sendPostRequest ( const QNetworkRequest& request, const QByteArray& data )
{
    QQtWebAccessSession* session = manager->newWebAccessSession();
    session->webAccessRequest() = request;

    QTimer* timer = session->getTimer();
    connect ( timer, SIGNAL ( timeout() ),
              this, SLOT ( localReplyTimeOut() ) ); //超时信号

    QNetworkRequest& netRequest = session->webAccessRequest();
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
}

QQtWebAccessSession* QQtWebAccessManager::sendPostRequest ( const QNetworkRequest& request, QHttpMultiPart* multiPart )
{
    QQtWebAccessSession* session = manager->newWebAccessSession();
    session->webAccessRequest() = request;

    QTimer* timer = session->getTimer();
    connect ( timer, SIGNAL ( timeout() ),
              this, SLOT ( localReplyTimeOut() ) ); //超时信号

    QNetworkRequest& netRequest = session->webAccessRequest();
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
}

QQtWebAccessSession* QQtWebAccessManager::sendPutRequest ( const QNetworkRequest& request, QIODevice* data )
{
    QQtWebAccessSession* session = manager->newWebAccessSession();
    session->webAccessRequest() = request;

    QTimer* timer = session->getTimer();
    connect ( timer, SIGNAL ( timeout() ),
              this, SLOT ( localReplyTimeOut() ) ); //超时信号

    QNetworkRequest& netRequest = session->webAccessRequest();
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
}

QQtWebAccessSession* QQtWebAccessManager::sendPutRequest ( const QNetworkRequest& request, const QByteArray& data )
{
    QQtWebAccessSession* session = manager->newWebAccessSession();
    session->webAccessRequest() = request;

    QTimer* timer = session->getTimer();
    connect ( timer, SIGNAL ( timeout() ),
              this, SLOT ( localReplyTimeOut() ) ); //超时信号

    QNetworkRequest& netRequest = session->webAccessRequest();
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
}

QQtWebAccessSession* QQtWebAccessManager::sendPutRequest ( const QNetworkRequest& request, QHttpMultiPart* multiPart )
{
    QQtWebAccessSession* session = manager->newWebAccessSession();
    session->webAccessRequest() = request;

    QTimer* timer = session->getTimer();
    connect ( timer, SIGNAL ( timeout() ),
              this, SLOT ( localReplyTimeOut() ) ); //超时信号

    QNetworkRequest& netRequest = session->webAccessRequest();
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
}

QQtWebAccessSession* QQtWebAccessManager::sendDeleteResourceRequest ( const QNetworkRequest& request )
{
    QQtWebAccessSession* session = manager->newWebAccessSession();
    session->webAccessRequest() = request;

    QTimer* timer = session->getTimer();
    connect ( timer, SIGNAL ( timeout() ),
              this, SLOT ( localReplyTimeOut() ) ); //超时信号

    QNetworkRequest& netRequest = session->webAccessRequest();
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
}

QQtWebAccessSession* QQtWebAccessManager::sendCustomRequest ( const QNetworkRequest& request, const QByteArray& verb,
                                                              QIODevice* data )
{
    QQtWebAccessSession* session = manager->newWebAccessSession();
    session->webAccessRequest() = request;

    QTimer* timer = session->getTimer();
    connect ( timer, SIGNAL ( timeout() ),
              this, SLOT ( localReplyTimeOut() ) ); //超时信号

    QNetworkRequest& netRequest = session->webAccessRequest();
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
}

QQtWebAccessSession* QQtWebAccessManager::sendCustomRequest ( const QNetworkRequest& request, const QByteArray& verb,
                                                              const QByteArray& data )
{
    QQtWebAccessSession* session = manager->newWebAccessSession();
    session->webAccessRequest() = request;

    QTimer* timer = session->getTimer();
    connect ( timer, SIGNAL ( timeout() ),
              this, SLOT ( localReplyTimeOut() ) ); //超时信号

    QNetworkRequest& netRequest = session->webAccessRequest();
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
}

QQtWebAccessSession* QQtWebAccessManager::sendCustomRequest ( const QNetworkRequest& request, const QByteArray& verb,
                                                              QHttpMultiPart* multiPart )
{
    QQtWebAccessSession* session = manager->newWebAccessSession();
    session->webAccessRequest() = request;

    QTimer* timer = session->getTimer();
    connect ( timer, SIGNAL ( timeout() ),
              this, SLOT ( localReplyTimeOut() ) ); //超时信号

    QNetworkRequest& netRequest = session->webAccessRequest();
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
}

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

void QQtWebAccessManager::sslErrors ( QNetworkReply* r, QList<QSslError> e )
{
    //pline() << r << e.size();
}

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

QQtWebAccessSession* QQtWebAccessSessionManager::newWebAccessSession()
{
    QUuid uuid = QUuid::createUuid();
    QQtWebAccessSession* session = new QQtWebAccessSession ( this );
    session->setWebAccessSessionName ( uuid.toString() );
    m_listWebAccessSession.push_back ( session );
    return session;
}

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
