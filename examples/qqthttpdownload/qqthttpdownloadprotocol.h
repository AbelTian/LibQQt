#ifndef QQTHTTPDOWNLOADPROTOCOL_H
#define QQTHTTPDOWNLOADPROTOCOL_H

#include <qqtwebaccessmanager.h>

class QQtHttpDownloadWebWorkSession: public QQtWebAccessSession
{
    Q_OBJECT
public:
    explicit QQtHttpDownloadWebWorkSession(QObject* parent = 0) : QQtWebAccessSession(parent) {}
    virtual ~QQtHttpDownloadWebWorkSession() {}
};

class QQtHttpDownloadProtocol : public QQtWebAccessManager
{
    Q_OBJECT
public:
    explicit QQtHttpDownloadProtocol(QObject* parent = nullptr);
    virtual ~QQtHttpDownloadProtocol() {}

    void sendRequstUrl(QString& url)
    {
        m_url = url;

    }
signals:

public slots:
private:
    QString m_url;
};

#endif // QQTHTTPDOWNLOADPROTOCOL_H
