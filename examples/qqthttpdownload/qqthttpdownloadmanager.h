#ifndef QQTHTTPDOWNLOADPROTOCOL_H
#define QQTHTTPDOWNLOADPROTOCOL_H

#include <qqtwebaccessmanager.h>

class QQtHttpDownloadWebWorkSession: public QQtWebAccessSession
{
    Q_OBJECT
public:
    explicit QQtHttpDownloadWebWorkSession ( QObject* parent = 0 ) : QQtWebAccessSession ( parent ) {}
    virtual ~QQtHttpDownloadWebWorkSession() {}
};

class QQtHttpDownloadManager : public QQtWebAccessManager
{
    Q_OBJECT
public:
    explicit QQtHttpDownloadManager ( QObject* parent = nullptr );
    virtual ~QQtHttpDownloadManager() {}

    void sendRequest ( QString strUrl ) {
        QQtHttpDownloadWebWorkSession* session = new QQtHttpDownloadWebWorkSession ( this );
        session->setWebAccessUrl ( strUrl );
        session->setWebAccessSessionName ( QUuid::createUuid().toString() );
        getWebAccessSessionManager()->addWebAccessSession ( session );
        sendGetRequest ( session );
        connect ( this, SIGNAL ( readyRead ( QQtWebAccessSession* ) ),
                  this, SLOT ( replyReadyRead ( QQtWebAccessSession* ) ) );
    }
signals:

public slots:

private slots:
    void replyReadyRead ( QQtWebAccessSession* session );
private:
};

#endif // QQTHTTPDOWNLOADPROTOCOL_H
