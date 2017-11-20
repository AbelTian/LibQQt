#include "qqtwebworkclient.h"
#include "qqtcore.h"


QQtWebWorkClient::QQtWebWorkClient ( QObject* parent ) : QNetworkAccessManager ( parent )
{
    m_listWebWorkSession.clear();

    connect ( this, SIGNAL ( finished ( QNetworkReply* ) ),
              this, SLOT ( finished ( QNetworkReply* ) ) );

    connect ( this, SIGNAL ( finished ( QNetworkReply* ) ),
              this, SIGNAL ( replyFinished ( QNetworkReply* ) ) );

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

void QQtWebWorkClient::getRequest ( QString& strUrl )
{
    QQtWebWorkSession* s0 = new QQtWebWorkSession ( this );

    s0->m_strUrl = strUrl;
    s0->m_pTimer = new QTimer ( this );
    s0->m_pTimer->setSingleShot ( true );
    s0->m_pTimer->setInterval ( 10000 );
    connect ( s0->m_pTimer, SIGNAL ( timeout() ),
              this, SLOT ( localReplyTimeOut() ) ); //超时信号

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

    s0->m_pNetworkReply = get ( netRequest ); //发起get请求
    /*下面关联信号和槽*/

    /*下载完成后开始一阵一阵堆取数据*/
    connect ( s0->m_pNetworkReply, SIGNAL ( readyRead() ),
              this, SLOT ( localReadyRead() ) );

    /*有可用数据时 */
    connect ( s0->m_pNetworkReply, SIGNAL ( downloadProgress ( qint64, qint64 ) ),
              this, SLOT ( localUpdateDownloadProgress ( qint64, qint64 ) ) );
    connect ( s0->m_pNetworkReply, SIGNAL ( uploadProgress ( qint64, qint64 ) ),
              this, SLOT ( localUpdateUploadProgress ( qint64, qint64 ) ) );

    //ignore
//    connect ( s0->m_pNetworkReply, SIGNAL ( finished() ),
//              this, SLOT ( finished(QNetworkReply*); ) ); //请求完成信号

    s0->m_pTimer->start ( );
}

void QQtWebWorkClient::postRequest ( QString& strUrl )
{
    //post
//    QString strBody; //http body部分，可封装参数信息
//    QByteArray contentByteArray = strBody.toLatin1();//转成二进制
//    m_pNetworkReply = m_pNetworkManager->post(netRequest,contentByteArray);//发起post请求
}

void QQtWebWorkClient::finished ( QNetworkReply* reply )
{
    pline() << reply;

    //clear resource
    QQtWebWorkSession* s0 = NULL;
    QListIterator<QQtWebWorkSession*> itor ( m_listWebWorkSession );

    while ( itor.hasNext() )
    {
        QQtWebWorkSession* s1 = itor.next();

        if ( s1->m_pNetworkReply == reply )
        {
            s0 = s1;
            break;
        }
    }

    if ( !s0 )
        return;

    s0->m_pNetworkReply->deleteLater();
    m_listWebWorkSession.removeOne ( s0 );

}

void QQtWebWorkClient::authenticationRequired ( QNetworkReply* r, QAuthenticator* a )
{
    pline() << r << a;
}

void QQtWebWorkClient::proxyAuthenticationRequired ( QNetworkProxy p, QAuthenticator* a )
{
    pline() << p.hostName() << a;
}

void QQtWebWorkClient::sslErrors ( QNetworkReply* r, QList<QSslError> e )
{
    pline() << r << e.size();
}

void QQtWebWorkClient::networkAccessibleChanged ( QNetworkAccessManager::NetworkAccessibility a )
{
    pline() << a;
}

void QQtWebWorkClient::networkSessionConnected()
{
    pline();
}

void QQtWebWorkClient::localReplyTimeOut()
{
    QTimer* obj = ( QTimer* ) sender();
    pline() << obj;

    QQtWebWorkSession* s0 = NULL;
    QListIterator<QQtWebWorkSession*> itor ( m_listWebWorkSession );

    while ( itor.hasNext() )
    {
        QQtWebWorkSession* s1 = itor.next();

        if ( s1->m_pTimer == obj )
        {
            s0 = s1;
            break;
        }
    }

    if ( !s0 )
        return;

    emit replyTimeOut ( s0->m_pNetworkReply ); //请求失败

    s0->m_pNetworkReply->deleteLater();
}

void QQtWebWorkClient::localReadyRead()
{
    QNetworkReply* obj = ( QNetworkReply* ) sender();
    pline() << obj;
    emit readyRead ( obj );
}

void QQtWebWorkClient::localUpdateUploadProgress ( qint64 bytesSent, qint64 bytesTotal )
{
    QNetworkReply* obj = ( QNetworkReply* ) sender();
    pline() << obj;
    emit updateUploadProgress ( obj, bytesSent, bytesTotal );
}

void QQtWebWorkClient::localUpdateDownloadProgress ( qint64 bytesReceived, qint64 bytesTotal )
{
    QNetworkReply* obj = ( QNetworkReply* ) sender();
    pline() << obj;
    emit updateDownloadProgress ( obj, bytesReceived, bytesTotal );
}
