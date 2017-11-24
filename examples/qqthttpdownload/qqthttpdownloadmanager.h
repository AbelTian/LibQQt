#ifndef QQTHTTPDOWNLOADPROTOCOL_H
#define QQTHTTPDOWNLOADPROTOCOL_H

#include <qqtwebaccessmanager.h>

class QQtHttpDownloadWebWorkSession: public QQtWebAccessSession
{
    Q_OBJECT
public:
    explicit QQtHttpDownloadWebWorkSession ( QObject* parent = 0 ) :
        QQtWebAccessSession ( parent ) {
        filename = "tmp.download";
    }
    virtual ~QQtHttpDownloadWebWorkSession() {}

    QString filename;
};

class QQtHttpDownloadManager : public QQtWebAccessManager
{
    Q_OBJECT
public:
    explicit QQtHttpDownloadManager ( QObject* parent = nullptr );
    virtual ~QQtHttpDownloadManager() {}

    void sendRequest ( QString strUrl, QString filename );
signals:

public slots:

private slots:
    void replyReadyRead ( QQtWebAccessSession* session );
private:
};

#endif // QQTHTTPDOWNLOADPROTOCOL_H
