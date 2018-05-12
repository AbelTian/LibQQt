#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <GumboQueryDocument.h>
#include <GumboQuerySelection.h>
#include <GumboQueryNode.h>
#include <QStringList>
#include <QTextCodec>

//#include "qqtcore.h"

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );

    //ui->b0->setFixedHeight ( 50 );
    //ui->b1->setFixedHeight ( 50 );
    m_webmanager = new QQtWebAccessManager ( this );
    connect ( m_webmanager, SIGNAL ( replyFinished ( QQtWebAccessSession* ) ),
              this, SLOT ( replyFinished ( QQtWebAccessSession* ) ) );


    m_mapVege["西葫芦"] = "xihulu" ;
    m_mapVege["土豆"] = "tudou";
    m_mapVege["大蒜"] = "dasuan";
    m_mapVege["白萝卜"] = "bailuobo";
    m_mapVege["菠菜"] = "bocai";
    m_mapVege["胡萝卜"] = "huluobo";
    m_mapVege["茄子"] = "qiezi";
    m_mapVege["葱头"] = "congtou";
    m_mapVege["豆角"] = "doujiao";
    m_mapVege["菜花"] = "caihua";
    m_mapVege["菜油"] = "caiyou";
    m_mapVege["菜苔"] = "caitai";
    m_mapVege["大白菜"] = "dabaicai";
    m_mapVege["大葱"] = "dacong";
    m_mapVege["金针菇"] = "jinzhengu";
    m_mapVege["韭菜"] = "jiucai";
    m_mapVege["苦瓜"] = "kugua";
    m_mapVege["莲藕"] = "lianou";
    m_mapVege["绿尖椒"] = "lvjianjiao";
    m_mapVege["平菇"] = "pinggu";
    m_mapVege["芹菜"] = "qincai";
    m_mapVege["青椒"] = "qingjiao";
    m_mapVege["生菜"] = "shengcai";
    m_mapVege["生姜"] = "shengjiang";
    m_mapVege["蒜薹"] = "suantai";
    m_mapVege["莴笋"] = "wosun";
    m_mapVege["西兰花"] = "xilanhua";
    m_mapVege["香菜"] = "xiangcai";
    m_mapVege["小白菜"] = "xiaobaicai";
    m_mapVege["洋白菜"] = "yangbaicai";
    m_mapVege["油菜"] = "youcai";
    m_mapVege["芸豆"] = "yundou";


    ui->lw->addItems ( m_mapVege.keys() );
#ifdef __ANDROID__
    ui->lw->setFixedWidth ( 260 );
#endif

    for ( int i = 0; i < ui->lw->count(); i++ )
    {
        QSize siz = ui->lw->item ( i )->sizeHint();
        //siz.setHeight ( 70 );
        //siz.setWidth ( 70 );
        //ui->lw->item ( i )->setSizeHint ( siz );

    }


    connect ( ui->lw, SIGNAL ( currentItemChanged ( QListWidgetItem*, QListWidgetItem* ) ),
              this, SLOT ( currentItemChanged ( QListWidgetItem*, QListWidgetItem* ) ) );

    ui->lw->setCurrentRow ( 0 );

    m_barSet0 = new QBarSet ( "德州黑马" );
    m_barSet1 = new QBarSet ( "临邑临南蔬菜" );
    m_barSet2 = new QBarSet ( "七里堡" );
    m_barSet3 = new QBarSet ( "山东章丘" );
    m_barSet4 = new QBarSet ( "山东寿光" );

    QBarSeries* series = new QBarSeries();
    series->append ( m_barSet0 );
    series->append ( m_barSet1 );
    series->append ( m_barSet2 );
    series->append ( m_barSet3 );
    series->append ( m_barSet4 );
    series->setLabelsVisible ( true );
    series->setLabelsPosition ( QAbstractBarSeries::LabelsOutsideEnd );
    series->setBarWidth ( 0.7 );
    series->setLabelsAngle ( -30 );

    QChart* chart = new QChart();
    chart->addSeries ( series );
    chart->setTitle ( "蔬菜价格报表" );
    chart->setAnimationOptions ( QChart::SeriesAnimations );
    chart->setTheme ( QChart::ChartThemeDark );
    chart->setTitleBrush ( QBrush ( QRgb ( 0xd6d6d6 ) ) );

    QStringList categories;
    categories << "今天" << "昨天" << "前天";
    QBarCategoryAxis* axis = new QBarCategoryAxis();
    axis->append ( categories );
    chart->createDefaultAxes();
    chart->setAxisX ( axis, series );
    chart->setBackgroundBrush ( QBrush ( QColor ( 38, 40, 48 ) ) );
    chart->setContentsMargins ( 0, 0, 0, 0 );
    chart->setPlotAreaBackgroundBrush ( QBrush ( QColor ( 60, 100, 30 ) ) );

    chart->axisY()->setMin ( 0 );
    chart->axisY()->setMax ( 10 );
    chart->axisY()->setLabelsColor ( Qt::white );
    chart->axisX()->setLabelsColor ( Qt::white );

    chart->legend()->setVisible ( true );
    chart->legend()->setAlignment ( Qt::AlignBottom );
    chart->legend()->setLabelColor ( Qt::white );

    ui->w0->setChart ( chart );
    ui->w0->setRenderHint ( QPainter::Antialiasing );
    ui->w0->setContentsMargins ( 0, 0, 0, 0 );

    QPalette pal = ui->w0->palette();
    pal.setColor ( QPalette::Window, QRgb ( 0xffab03 ) );
    pal.setColor ( QPalette::WindowText, QRgb ( 0x181818 ) );
    //ui->w0->setPalette ( pal );

    connect ( ui->a0, SIGNAL ( triggered ( bool )  ),
              this, SLOT ( seeplot() ) );
    connect ( ui->a1, SIGNAL ( triggered ( bool )  ),
              this, SLOT ( seereport() ) );
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
    m_webmanager->sendGetRequest ( url );
}

void MainWindow::replyFinished ( QQtWebAccessSession* session )
{
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

    GumboQueryDocument doc;
    doc.parse ( result2.toLocal8Bit().constData() );
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
    ui->tb->setSelectionMode ( QAbstractItemView::MultiSelection );
    ui->tb->horizontalHeader()->setSectionResizeMode ( QHeaderView::ResizeToContents );

    for ( int j = 0; j < 5; j++ )
    {
        QString cc =  tList.value ( j );
        //qDebug() << "header" << j << cc;
        QTableWidgetItem* item = new QTableWidgetItem ( cc );
        ui->tb->setHorizontalHeaderItem ( j, item );
    }

    QBarSet* c[5];
    c[0] = m_barSet0;
    c[1] = m_barSet1;
    c[2] = m_barSet2;
    c[3] = m_barSet3;
    c[4] = m_barSet4;

    //pline() << c[0]->count() << c[0]->sum();

    for ( int i = 0; i < 5; i++ )
    {
        for ( int j = 0; j < c[i]->count(); )
        {
            c[i]->remove ( 0 );
        }
    }

    //pline() << c[0]->count() << c[0]->sum();

    for ( int i = 5; i < tList.count(); )
    {
        ui->tb->setRowCount ( i / 5 );

        for ( int j = 0; j < 5; j++ )
        {
            QString cc =  tList.value ( i );
            //qDebug() << i / 5 - 1 << j << cc;
            QTableWidgetItem* item = new QTableWidgetItem ( cc );
            ui->tb->setItem ( i / 5 - 1, j, item );

            if ( j == 3 )
            {
                if ( cc.contains ( "德州黑马" ) )
                {
                    QString txt = tList.value ( i - 2 );
                    qreal price = txt.toFloat();
                    *m_barSet0 << price;
                    qDebug() << i / 5 - 1 << j << price;
                }
                else if ( cc.contains ( "临邑临南蔬菜" ) )
                {
                    QString txt = tList.value ( i - 2 );
                    qreal price = txt.toFloat();
                    *m_barSet1 << price;
                }
                else if ( cc.contains ( "七里堡" ) )
                {
                    QString txt = tList.value ( i - 2 );
                    qreal price = txt.toFloat();
                    *m_barSet2 << price;
                }
                else if ( cc.contains ( "山东章丘" ) )
                {
                    QString txt = tList.value ( i - 2 );
                    qreal price = txt.toFloat();
                    *m_barSet3 << price;
                }
                else if ( cc.contains ( "山东寿光" ) )
                {
                    QString txt = tList.value ( i - 2 );
                    qreal price = txt.toFloat();
                    *m_barSet4 << price;
                }
            }

            i++;
        }
    }
}

void MainWindow::seeplot()
{
    ui->sw0->setCurrentIndex ( 1 );
}

void MainWindow::seereport()
{
    ui->sw0->setCurrentIndex ( 0 );
}
