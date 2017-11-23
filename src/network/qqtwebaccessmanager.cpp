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
}

void QQtWebAccessManager::sendGetRequest ( QQtWebAccessSession* session )
{
    QTimer* timer = session->getTimer();
    connect ( timer, SIGNAL ( timeout() ),
              this, SLOT ( localReplyTimeOut() ) ); //超时信号

    QNetworkRequest netRequest;
    netRequest.setHeader ( QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded" );
    netRequest.setUrl ( QUrl ( session->getWebAccessUrl() ) ); //地址信息

    if ( session->getWebAccessUrl().toLower().startsWith ( "https" ) ) //https请求，需ssl支持(下载openssl拷贝libeay32.dll和ssleay32.dll文件至Qt bin目录或程序运行目录)
    {
        QSslConfiguration sslConfig;
        sslConfig.setPeerVerifyMode ( QSslSocket::VerifyNone );
        sslConfig.setProtocol ( QSsl::TlsV1_1 );
        netRequest.setSslConfiguration ( sslConfig );
    }

    QNetworkReply* reply = NULL;
    reply = get ( netRequest );
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
    QQtWebAccessSession* session = manager->newWebAccessSession();
    session->setWebAccessUrl ( strUrl );
    sendGetRequest ( session );
}

QQtWebAccessSession* QQtWebAccessManager::sendGetRequests ( QStringList& strUrl )
{

}

QQtWebAccessSession* QQtWebAccessManager::sendGetRequest ( QNetworkRequest& netRequest )
{

}

QQtWebAccessSession* QQtWebAccessManager::sendGetRequests ( QList<QNetworkRequest*>& netRequests )
{

}

QQtWebAccessSession* QQtWebAccessManager::sendPostRequest ( QString strUrl )
{
    //post
//    QString strBody; //http body部分，可封装参数信息
//    QByteArray contentByteArray = strBody.toLatin1();//转成二进制
//    m_pNetworkReply = m_pNetworkManager->post(netRequest,contentByteArray);//发起post请求
}

void QQtWebAccessManager::finished ( QNetworkReply* reply )
{
    //pline() << reply;

    //clear resource
    QQtWebAccessSession* s0 = manager->getSessionByReply ( reply );

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
    //pline() << r << a;
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
