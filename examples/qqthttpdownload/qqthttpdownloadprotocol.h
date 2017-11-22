#ifndef QQTHTTPDOWNLOADPROTOCOL_H
#define QQTHTTPDOWNLOADPROTOCOL_H

#include <qqtwebsocketprotocol.h>
#include <qqtwebprotocolmanager.h>

class QQtHttpDownloadWebWorkSession: public QQtWebWorkSession
{
    Q_OBJECT
public:
    explicit QQtHttpDownloadWebWorkSession ( QObject* parent = 0 ) : QQtWebWorkSession ( parent ) {}
    virtual ~QQtHttpDownloadWebWorkSession() {}
};

class QQtHttpDownloadProtocol : public QQtWebSocketProtocol
{
    Q_OBJECT
public:
    explicit QQtHttpDownloadProtocol ( QObject* parent = nullptr );
    virtual ~QQtHttpDownloadProtocol() {}

    void sendRequstUrl ( QString& url ) {
        m_url = url;

    }
signals:

public slots:
private:
    QString m_url;
};

#endif // QQTHTTPDOWNLOADPROTOCOL_H
