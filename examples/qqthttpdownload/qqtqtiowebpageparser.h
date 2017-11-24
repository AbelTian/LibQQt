#ifndef QQTQTIOWEBPROTOCOL_H
#define QQTQTIOWEBPROTOCOL_H

#include <QObject>
#include <qqtwebaccessmanager.h>
#include <QDomDocument>

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

public slots:
private slots:
    void replyFinished ( QQtWebAccessSession* session );
private:
    QString m_baseUrl;
    QList<TSdkGroup> sdkGroup;
};

#endif // QQTQTIOWEBPROTOCOL_H
