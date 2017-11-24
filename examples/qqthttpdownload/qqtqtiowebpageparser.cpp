#include "qqtqtiowebpageparser.h"
#include <GumboQueryDocument.h>
#include <GumboQuerySelection.h>
#include <GumboQueryNode.h>
#include <QStringList>
#include <QTextCodec>
/**
 * @brief QQtQtIOWebPageParser::QQtQtIOWebPageParser
 * bad xml
 * @param parent
 */
QQtQtIOWebPageParser::QQtQtIOWebPageParser ( QObject* parent ) : QQtWebAccessManager ( parent )
{
    m_baseUrl = "http://download.qt.io/official_releases/qt/";
    connect ( this, SIGNAL ( replyFinished (  QQtWebAccessSession* ) ),
              this, SLOT ( replyFinished ( QQtWebAccessSession* ) ) );
}

void QQtQtIOWebPageParser::startNewParse ( QString url1, QString url2 )
{
    if ( url1 == "" && url2 == "" )
    {
        sdkGroup.clear();
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
    /*判断返回码 200*/
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
        pline() << "fail" << nHttpCode;
        return;
    }

    /*读取content*/
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

    /*处理一下页面 原页面没有\n，而我需要\n*/
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
    //qDebug() << items;

    QStringList itemList = items.split ( "\n", QString::SkipEmptyParts );

    for ( int i = 0; i < itemList.count(); i++ )
    {
        QString txt = itemList.at ( i );
        //qDebug() << txt;
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

    TSdkGroup group;

    for ( int i = 0; i < itemList.count(); i++ )
    {
        /*获取第一列*/
        if ( i % 4 == 0 )
        {
            /*在根目录的时候 第一层目录 qt/*/
            if ( url1 == "" )
            {
                QString item = itemList.at ( i );

                /*是第二层目录 5.9*/
                if ( item.endsWith ( '/' ) )
                {
                    /*保存下来url1*/
                    startNewParse ( item );
                }
            }
            /*进入第二层目录 e.g. 5.9*/
            else if ( url2 == "" )
            {
                QString item = itemList.at ( i );

                /*是第二层目录 5.9.1*/
                if ( item.endsWith ( '/' ) )
                {
                    /*保存下来url1，url2*/
                    startNewParse ( url1, item );
                }
            }
            /*最后一层目录*/
            else
            {
                QString item = itemList[i];

                /*new sdk node*/
                if ( item.contains ( '.' ) || item.contains ( '-' ) )
                {
                    TSdkNode node;
                    node.name = item;

                    if ( i + 1 < itemList.count() )
                        node.time = itemList[i + 1];

                    if ( i + 2 < itemList.count() )
                        node.size = itemList[i + 2];

                    if ( i + 3 < itemList.count() )
                        node.detail = itemList[i + 3];

                    qDebug() << node.name << node.time << node.size << node.detail;
                    group.list.push_back ( node );
                }
            }
        }
    }

    group.url1 = url1;
    group.url2 = url2;

    if ( url1 != "" && url2 != "" )
    {
        sdkGroup.push_back ( group );
        pline() << sdkGroup.size();
    }
}
