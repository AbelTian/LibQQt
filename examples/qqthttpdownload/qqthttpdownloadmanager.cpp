#include "qqthttpdownloadmanager.h"

QQtHttpDownloadManager::QQtHttpDownloadManager ( QObject* parent ) : QQtWebAccessManager ( parent )
{
    QFile file ( "/Users/abel/Develop/c2-test/aa" );
    file.open ( QFile::Truncate | QFile::WriteOnly );
    file.close();
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
