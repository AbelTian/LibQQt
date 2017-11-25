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
    QString url;//?x
    QString filesize;
    QString filedownloaded;
    QString elipsedSize;

    QString downloadingTime;
    QString elipsedTime;
    QString wholeTime;
    QString speed;
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

protected:
    /* 字节转KB、MB、GB */
    QString getSize ( qint64 bytes );

    /* 速度转KB/S、MB/S、GB/S */
    QString getSpeed ( double speed );

    /* 秒转*d *h *m *s */
    QString getElipsedTime ( int seconds );
private slots:
    void replyReadyRead ( QQtWebAccessSession* session );
    void updateDownloadProgress ( QQtWebAccessSession* session, qint64 bytesReceived, qint64 bytesTotal );
private:
};

#endif // QQTHTTPDOWNLOADPROTOCOL_H
