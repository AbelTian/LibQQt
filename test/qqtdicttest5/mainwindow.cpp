#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qqtdictionary.h>
#include <qqtwebaccessmanager.h>

#include <QDebug>

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );

    manager = new QQtWebAccessManager ( this );
    connect ( manager, SIGNAL ( replyFinished ( QQtWebAccessSession* ) ),
              this, SLOT ( replyFinished ( QQtWebAccessSession* ) ) );
    manager->sendGetRequest ( "http://t.weather.sojson.com/api/weather/city/101030100" );

    manager2 = new QQtWebAccessManager ( this );
    connect ( manager2, SIGNAL ( replyFinished ( QQtWebAccessSession* ) ),
              this, SLOT ( replyFinished2 ( QQtWebAccessSession* ) ) );
    manager2->sendGetRequest ( "http://flash.weather.com.cn/wmaps/xml/sichuan.xml" );

    manager3 = new QQtWebAccessManager ( this );
    connect ( manager3, SIGNAL ( replyFinished ( QQtWebAccessSession* ) ),
              this, SLOT ( replyFinished3 ( QQtWebAccessSession* ) ) );
    manager3->sendGetRequest ( "http://api.map.baidu.com/location/ip?ak=9zNKGguAbdNC6xwD7syftt533eIf7cSn&callback=showLocation" );


    manager4 = new QQtWebAccessManager ( this );
    connect ( manager4, SIGNAL ( replyFinished ( QQtWebAccessSession* ) ),
              this, SLOT ( replyFinished4 ( QQtWebAccessSession* ) ) );
    manager4->sendGetRequest ( "https://ss0.baidu.com/6KAZsjip0QIZ8tyhnq/text2audio?tex=111111&cuid=dict&lan=zh&ctp=1&pdt=30&vol=100&spd=3" );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::replyFinished ( QQtWebAccessSession* session )
{
    QNetworkReply* reply = session->getWebAccessReply();
    int httpCode = reply->attribute ( QNetworkRequest::HttpStatusCodeAttribute ).toInt();
    if ( httpCode != 200 )
    {

        qDebug() << "http code error:" << httpCode;
        return;
    }

    qDebug() << "===========================================================================";
    QByteArray htmlContent = reply->readAll();
    QQtDictionary dict;
    dict.fromJson ( htmlContent );
    QByteArray result = dict.toJson ( QJsonDocument::Indented );
    qDebug() << qPrintable ( QString ( result ) );
    ui->textBrowser->append ( QString ( result ) );
}

void MainWindow::replyFinished2 ( QQtWebAccessSession* session )
{
    QNetworkReply* reply = session->getWebAccessReply();
    int httpCode = reply->attribute ( QNetworkRequest::HttpStatusCodeAttribute ).toInt();
    if ( httpCode != 200 )
    {

        qDebug() << "http code error:" << httpCode;
        return;
    }

    qDebug() << "===========================================================================";
    QByteArray htmlContent = reply->readAll();
    QQtDictionary dict;
    dict.fromXML ( htmlContent );
    QByteArray result = dict.toXML ( 4 );
    qDebug() << qPrintable ( QString ( result ) );
    ui->textBrowser_2->append ( QString ( result ) );

    QByteArray result2 = dict.toJson ( QJsonDocument::Indented );
    ui->textBrowser_21->append ( QString ( result2 ) );
}

void MainWindow::replyFinished3 ( QQtWebAccessSession* session )
{
    QNetworkReply* reply = session->getWebAccessReply();
    int httpCode = reply->attribute ( QNetworkRequest::HttpStatusCodeAttribute ).toInt();
    if ( httpCode != 200 )
    {

        qDebug() << "http code error:" << httpCode;
        return;
    }

    qDebug() << "===========================================================================";
    QByteArray htmlContent = reply->readAll();
    htmlContent.replace ( QByteArray ( "showLocation && showLocation(" ), "" );
    htmlContent.replace ( ")", "" );
    QQtDictionary dict;
    dict.fromJson ( htmlContent );
    QByteArray result = dict.toJson ( QJsonDocument::Indented );
    qDebug() << qPrintable ( QString ( result ) );
    ui->textBrowser_3->append ( QString ( result ) );
}

void MainWindow::replyFinished4 ( QQtWebAccessSession* session )
{
    QNetworkReply* reply = session->getWebAccessReply();
    int httpCode = reply->attribute ( QNetworkRequest::HttpStatusCodeAttribute ).toInt();
    if ( httpCode != 200 )
    {

        qDebug() << "http code error:" << httpCode;
        return;
    }

    qDebug() << "===========================================================================";
    QByteArray htmlContent = reply->readAll();
    qDebug() << htmlContent;
}
