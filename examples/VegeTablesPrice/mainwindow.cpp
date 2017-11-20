#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <GumboQueryDocument.h>
#include <GumboQuerySelection.h>
#include <GumboQueryNode.h>
#include <QStringList>
#include <QStringListIterator>

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );

    m_client = new QQtWebWorkClient ( this );
    connect ( m_client, SIGNAL ( replyFinished ( QNetworkReply* ) ),
              this, SLOT ( replyFinished ( QNetworkReply* ) ) );

    QStringList vl;
    vl << "西葫芦";
    vl << "土豆";
    vl << "茄子";
    vl << "西红柿";
    vl << "玉米";
    vl << "小麦";
    vl << "棉花";
    vl << "西瓜";
    vl << "白蒜";
    vl << "辣椒";
    vl << "菠菜";
    vl << "胡萝卜";
    vl << "黑木耳";
    vl << "白木耳";
    vl << "蓬蒿";
    vl << "小葱";
    vl << "山药";
    vl << "苹果";
    vl << "香瓜";
    vl << "枣";
    vl << "梨";
    vl << "香蕉";
    vl << "蒜薹";
    vl << "豆角";
    vl << "茴香";
    m_mapVege["西葫芦"] = "xihulu" ;
    m_mapVege["土豆"] = "tudou";
    ui->lw->addItems ( m_mapVege.keys() );


    connect ( ui->lw, SIGNAL ( currentItemChanged ( QListWidgetItem*, QListWidgetItem* ) ),
              this, SLOT ( currentItemChanged ( QListWidgetItem*, QListWidgetItem* ) ) );

    ui->lw->setCurrentRow ( 0 );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::currentItemChanged ( QListWidgetItem* cur, QListWidgetItem* prev )
{
    qDebug() << cur << prev;

    if ( !cur )
        return;

    //QString url = QString ( "http://www.baidu.com/s?wd=%1%2" ).arg ( cur->text() ).arg ( "价格" );
    QString url = QString ( "http://nong.gold600.com/cx?pz=%1&c=shandong" ).arg ( m_mapVege[cur->text()] );
    m_client->sendGetRequest ( url );
}

void MainWindow::replyFinished ( QNetworkReply* reply )
{
    //pline() << reply->readAll();
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
    /*用页面源文件的编码来进行解码 GB2312 or UTF-8*/
    QTextCodec* pCodec = QTextCodec::codecForName ( "GB2312" );
    QString strResult = pCodec->toUnicode ( resultContent );
    //pline() << strResult;
    QTextCodec* pCodec2 = QTextCodec::codecForName ( "GB2312" );
    QByteArray strResult2 = pCodec2->fromUnicode ( strResult );
    QString txt0 = strResult2;
    //pline() << txt0;
    QString cc = resultContent;
    //pline() << cc.toLatin1().constData();

    GumboQueryDocument doc;
    doc.parse ( strResult.toLocal8Bit().constData() );
    GumboQuerySelection s = doc.find ( "table" );

    GumboQueryNode pNode = s.nodeAt ( 0 );
    QString txt = QString::fromStdString ( pNode.text() );

    //pline() << txt;
    QStringList tList = txt.split ( "\n", QString::SkipEmptyParts );


    for ( int i = 0; i < tList.count(); i++ )
    {
        QString txt = tList.at ( i );
        txt = txt.trimmed();

        if ( txt.isEmpty() )
        {
            tList.removeAt ( i );
            i--;
            continue;
        }

        tList[i] = txt;
    }


    /*
    for ( QStringList::Iterator itor = tList.begin();
          itor != tList.end(); itor++ )
    {
        QString txt = ( QString ) * itor;

        if ( "" == txt.trimmed() )
        {
            tList.erase ( itor );
            itor--;
            continue;
        }

        *itor = txt.trimmed();
    }
    */

    ui->tb->clear();
    ui->tb->setColumnCount ( 5 );
    ui->tb->horizontalHeader()->setSectionResizeMode ( QHeaderView::ResizeToContents );


    for ( int i = 0; i < tList.count(); )
    {
        ui->tb->setRowCount ( i / 5 + 1 );

        for ( int j = 0; j < 5; j++ )
        {
            QString cc =  tList.value ( i );
            qDebug() << i / 5 << j << cc;
            QTableWidgetItem* item = new QTableWidgetItem ( cc );
            ui->tb->setItem ( i / 5, j, item );
            i++;
        }
    }
}
