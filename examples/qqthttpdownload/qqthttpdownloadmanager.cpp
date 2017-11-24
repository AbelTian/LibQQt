#include "qqthttpdownloadmanager.h"

QQtHttpDownloadManager::QQtHttpDownloadManager ( QObject* parent ) : QQtWebAccessManager ( parent )
{
    connect ( this, SIGNAL ( readyRead ( QQtWebAccessSession* ) ),
              this, SLOT ( replyReadyRead ( QQtWebAccessSession* ) ) );

    QFile file ( "/Users/abel/Develop/c2-test/aa" );
    file.open ( QFile::Truncate | QFile::WriteOnly );
    file.close();
}

void QQtHttpDownloadManager::sendRequest ( QString strUrl, QString filename )
{
    QQtHttpDownloadWebWorkSession* session = new QQtHttpDownloadWebWorkSession ( this );
    session->filename = filename;
    session->setWebAccessUrl ( strUrl );
    session->setWebAccessSessionName ( QUuid::createUuid().toString() );
    getWebAccessSessionManager()->addWebAccessSession ( session );
    sendGetRequest ( session );
}

void QQtHttpDownloadManager::replyReadyRead ( QQtWebAccessSession* session )
{
    pline() << session->getWebAccessReply()->url();
    QByteArray data = session->getWebAccessReply()->readAll();
    pline() << data;
    QFile file ( "/Users/abel/Develop/c2-test/aa" );
    file.open ( QFile::Append );
    file.write ( data );
    file.close();
}
