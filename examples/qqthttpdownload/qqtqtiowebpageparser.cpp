#include "qqtqtiowebpageparser.h"
#include <GumboQueryDocument.h>
#include <GumboQuerySelection.h>
#include <GumboQueryNode.h>
#include <QStringList>
#include <QTextCodec>
#include <QDomDocument>
/**
 * @brief QQtQtIOWebPageParser::QQtQtIOWebPageParser
 * bad xml
 * @param parent
 */
QQtQtIOWebPageParser::QQtQtIOWebPageParser ( QObject* parent ) : QQtWebAccessManager ( parent )
{
    m_baseUrl = "http://download.qt.io/official_releases/qt/";
    m_xmlfile = "/Users/abel/Develop/c2-test/cc.xml";
    connect ( this, SIGNAL ( replyFinished (  QQtWebAccessSession* ) ),
              this, SLOT ( replyFinished ( QQtWebAccessSession* ) ) );

    QTimer* timer = new QTimer();
    timer->setSingleShot ( true );
    timer->setInterval ( 10000 );
    connect ( timer, &QTimer::timeout,
              [this]
    {
        QFile file ( m_xmlfile );
        file.open ( QFile::Append );
        QTextStream stream ( &file );
        m_doc.save ( stream, 0 );
        file.close();
        pline() << m_doc.childNodes().at ( 0 ).nodeValue();
        pline() << "save ok";
    } );
    timer->start();
}

void QQtQtIOWebPageParser::sendRequest ( QString url1, QString url2 )
{
    if ( url1 == "" && url2 == "" )
    {
        m_doc.clear();
        m_doc.createElement ( "Qt version list" );
    }

    QString strUrl = QString ( "%1%2%3" ).arg ( m_baseUrl ).arg ( url1 ).arg ( url2 );

    QQtQtIOWebUrlSession* session = new QQtQtIOWebUrlSession ( this );
    session->url1 = url1;
    session->url2 = url2;
    session->setWebAccessUrl ( strUrl );
    session->setWebAccessSessionName ( QUuid::createUuid().toString() );
    getWebAccessSessionManager()->addWebAccessSession ( session );
    sendGetRequest ( session );
}

void QQtQtIOWebPageParser::replyFinished ( QQtWebAccessSession* s0 )
{
    QQtQtIOWebUrlSession* session = ( QQtQtIOWebUrlSession* ) s0;
    QNetworkReply* reply = session->getWebAccessReply();
    //pline() << reply->readAll();
    pline() << reply->url();
    int nHttpCode = reply->attribute ( QNetworkRequest::HttpStatusCodeAttribute ).toInt(); //http返回码

    if ( nHttpCode == 200 ) //成功
    {
        pline() << "success";
    }
    else
    {
        pline() << "fail";
        return;
    }

    QByteArray resultContent = reply->readAll();
    //pline() << QString ( resultContent );
    QString result1 = resultContent;
    //pline() << result1.toLatin1().constData();
    pline() << QTextCodec::codecForHtml ( resultContent )->name();

    /*用页面源文件的编码来进行解码 GB2312 or UTF-8*/
    QTextCodec* pCodec = QTextCodec::codecForName ( "GBK" );
    QString strResult = pCodec->toUnicode ( resultContent );
    //pline() << strResult;

    QTextCodec* pCodec2 = QTextCodec::codecForName ( "UTF-8" );
    QByteArray resultContent2 = pCodec2->fromUnicode ( strResult );
    QString result2 = resultContent2;
    //pline() << result2;

    pline() << QTextCodec::codecForLocale()->name();

    //before </td> + /n
    result2.replace ( "</td>", "\n</td>" );
    result2.replace ( "</a>", "\n</a>" );
    result2.replace ( "</th>", "\n</th>" );

    GumboQueryDocument doc;
    doc.parse ( result2.toLocal8Bit().constData() );
    GumboQuerySelection s = doc.find ( "table" );
    pline() << "node num:" << s.nodeNum();

    GumboQueryNode pNode = s.nodeAt ( 0 );
    QString items = QString::fromStdString ( pNode.text() );
    qDebug() << items;

    QStringList itemList = items.split ( "\n", QString::SkipEmptyParts );

    for ( int i = 0; i < itemList.count(); i++ )
    {
        QString txt = itemList.at ( i );
        qDebug() << txt;
        /*
        txt = txt.trimmed();

        if ( txt.isEmpty() )
        {
            itemList.removeAt ( i );
            i--;
            continue;
        }

        itemList[i] = txt;
        */
    }

    QString url1 = session->url1;
    QString url2 = session->url2;


    for ( int i = 0; i < itemList.count(); i++ )
    {
        /*获取第一列*/
        if ( i % 4 == 0 )
        {
            /*在根目录的时候 第一层目录 qt/*/
            if ( url1 == "" )
            {
                QString item = itemList.at ( i );

                /*是个子目录 5.9*/
                if ( item.endsWith ( '/' ) )
                {
                    QDomNode node;
                    node.setNodeValue ( item );
                    m_doc.appendChild ( node );
                    sendRequest ( item );
                }
            }
            /*进入第二层目录 e.g. 5.9*/
            else if ( url2 == "" )
            {
                QString item = itemList.at ( i );

                /*是个子目录 5.9.1*/
                if ( item.endsWith ( '/' ) )
                {

                    QDomNodeList dl = m_doc.childNodes();
                    int j = 0;

                    for ( j = 0; j < dl.count(); j++ )
                    {
                        if ( dl.at ( j ).nodeValue() == url1 )
                        {
                            break;
                        }
                    }

                    QDomNode node ;
                    node.setNodeValue ( item );
                    dl.at ( j ).appendChild ( node );
                    //url1 url2
                    sendRequest ( url1, item );
                }
            }
            /*最后一层目录*/
            else
            {
                qDebug() << itemList[i];
            }
        }
    }

}
