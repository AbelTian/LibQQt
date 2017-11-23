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

signals:

public slots:

private slots:
    //void replyReadyRead ( QNetworkReply* reply );
private:
};

#endif // QQTHTTPDOWNLOADPROTOCOL_H
