#ifndef QQTQTIOWEBPROTOCOL_H
#define QQTQTIOWEBPROTOCOL_H

#include <QObject>
#include <qqtwebaccessmanager.h>
#include <qqtdictionary.h>
#include <QTimer>
#include <QTime>

class QQtQtIOWebUrlSession: public QQtWebAccessSession
{
    Q_OBJECT
public:
    explicit QQtQtIOWebUrlSession ( QObject* parent = 0 ) :
        QQtWebAccessSession ( parent ) {
        url1 = "";
        url2 = "";
    }
    virtual ~QQtQtIOWebUrlSession() {}

    QString url1;
    QString url2;
};

class QQtQtIOWebPageParser : public QQtWebAccessManager
{
    Q_OBJECT
public:
    explicit QQtQtIOWebPageParser ( QObject* parent = nullptr );

    void startNewParse ( QString url1 = "", QString url2  = "" );

    typedef struct tagSdkNode
    {
        QString name;
        QString time;
        QString size;
        QString detail;
    } TSdkNode;

    typedef struct tagSdkGroup
    {
        QString url1;
        QString url2;
        QList<TSdkNode> list;
    } TSdkGroup;

    QString getBaseUrl() { return m_baseUrl; }
    QList<TSdkGroup>& getSdkGroup() { return sdkGroup; }
signals:
    void fetchFinish();
    //timeout
    void fetchTimeout();
public slots:
private slots:
    void replyFinished ( QQtWebAccessSession* session );
    void detecteTimeout();
private:
    QString m_baseUrl;
    /*过去有用这种自定义的，有用xml的，有用json的，留作纪念*/
    QList<TSdkGroup> sdkGroup;
    /*现在用QQtDict*/
    QQtDictionary m_sdkGroup;
    /*格式：["5.7"]["5.7.3"][0-3]*/
    QTimer* m_timer;
    QTime m_time;
};

#endif // QQTQTIOWEBPROTOCOL_H
