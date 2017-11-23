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

    void sendRequest ( QString url1 = "", QString url2  = "" );

signals:

public slots:
private slots:
    void replyFinished ( QQtWebAccessSession* session );
private:
    QString m_baseUrl;
    QString m_xmlfile;
    QDomDocument m_doc;
};

#endif // QQTQTIOWEBPROTOCOL_H
