#ifndef QQTWEBLOADER_H
#define QQTWEBLOADER_H

#include <QObject>

#include <qqtwebaccessmanager.h>
#include <qqt-local.h>

class QQTSHARED_EXPORT QQtNetworkReply : public QNetworkReply
{
    Q_OBJECT
public:
    explicit QQtNetworkReply ( QObject* parent = 0 );
    virtual ~QQtNetworkReply();

    QQtNetworkReply ( const QQtNetworkReply& other );
    QQtNetworkReply& operator = ( const QNetworkReply& other );

    // QIODevice interface
protected:
    virtual qint64 readData ( char* data, qint64 maxlen ) override;

    // QIODevice interface
protected:
    virtual qint64 writeData ( const char* data, qint64 len ) override;

    // QNetworkReply interface
public slots:
    virtual void abort() override;

private:
    QByteArray mBytes;
};

/**
 * @brief The QQtWebLoader class
 * 当前线程内使用，不会阻塞GUI。
 *
 * Http请求工具，阻塞版。不可重入，不可跨线程。
 * 支持get、支持post
 *
 * 简单的HTTP请求。
 */
class QQTSHARED_EXPORT QQtWebLoader : public QObject
{
    Q_OBJECT

public:
    explicit QQtWebLoader ( QObject* parent = 0 );
    virtual ~QQtWebLoader();

    QQtWebAccessManager* manager() {
        return mWebAccessManager;
    }

    //返回的session里面的reply是QQtNetworkReply。
    //get之后，可以修改这一个session的超时？不可以。
    QQtWebAccessSession* get ( const QString& url );

    //manager提供接口修改request，用户可以在session里修改？不可以。
    //这个接口提供给用户，manager没修改request的部分，用户可以改。
    QQtWebAccessSession* get ( const QNetworkRequest& req );

    QQtWebAccessSession* post ( const QString& url, const QByteArray& data );
    QQtWebAccessSession* post ( const QNetworkRequest& req, const QByteArray& data );

    //全局session有效
    void setTimerInterval ( int millsecond = 5000 );
    int timerInterval();

    /*
     * 以下和用户无关。
     */
protected slots:
    void localReplyFinished ( QQtWebAccessSession* session );
    void localReplyTimeout ( QQtWebAccessSession* session );

protected:

private:
    QQtWebAccessManager* mWebAccessManager;
    QQtWebAccessSession session1;
    QQtNetworkReply reply1;
    QQtBlock block1;
};

#endif // QQTWEBLOADER_H

