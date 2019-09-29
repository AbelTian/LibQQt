#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qqtirregularwidget.h>
#include <qqtclickhelper.h>
#include <qqtframe.h>
#include <qqtbodymover.h>
#include <qqtbodyresizer.h>
#include <qqtirregularpushbutton.h>

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );

    //用户设置图片就可以了，图像就已经裁切好了，已经变形了，透明部分已经不能点击了。
    //而且当图片跟随窗口大小改变，mask的部分也跟随变化，跟QQtWidget的imageStyle有关系。
    ui->widget->setPixmap ( conf_root ( "a1.png" ) );

    QQtClickHelper* clicker = new QQtClickHelper ( this );
    connect ( clicker, SIGNAL ( clickWithPoint ( QPoint ) ), this, SLOT ( clicked1 ( QPoint ) ) );
    ui->widget->installEventFilter ( clicker );

    //加个信号
    QQtBodyMover* mover = new QQtBodyMover ( this );
    //ui->widget_8->installEventFilter ( mover );
    //加个信号
    QQtBodyResizer* resizer = new QQtBodyResizer ( this );
    //ui->widget_8->installEventFilter ( resizer );

    //center normal
    ui->widget_12->setPixmap ( conf_root ( "a1.png" ) );

    //zoom
    ui->widget_2->setPixmap ( conf_root ( "a1.png" ) );
    ui->widget_2->setImageStyle ( QQtWidget::QQTZOOM );
    ui->widget_2->installEventFilter ( clicker );

    //zoom keep aspect ratio
    ui->widget_21->setPixmap ( conf_root ( "a1.png" ) );
    ui->widget_21->setImageStyle ( QQtWidget::QQTZOOM_KEEPASPECTRATIO );
    ui->widget_21->installEventFilter ( clicker );

    //tiled
    ui->widget_7->setPixmap ( conf_root ( "a1.png" ) );
    ui->widget_7->setImageStyle ( QQtWidget::QQTTILED );
    ui->widget_7->installEventFilter ( clicker );


    //other
    //ui->widget_30->setParent ( 0 );
    //ui->widget_30->show();

    ui->widget_15->setPixmap ( conf_root ( "a1.png" ) );
    ui->widget_15->setImageStyle ( QQtWidget::QQTZOOMWIDTH );
    ui->widget_15->installEventFilter ( clicker );

    ui->widget_16->setPixmap ( conf_root ( "a1.png" ) );
    ui->widget_16->setImageStyle ( QQtWidget::QQTZOOMHEIGHT );
    ui->widget_16->installEventFilter ( clicker );

    ui->widget_17->setPixmap ( conf_root ( "a1.png" ) );
    ui->widget_17->setImageStyle ( QQtWidget::QQTZOOMWIDTH_KEEPASPECTRATIO );
    ui->widget_17->installEventFilter ( clicker );

    ui->widget_18->setPixmap ( conf_root ( "a1.png" ) );
    ui->widget_18->setImageStyle ( QQtWidget::QQTZOOMHEIGHT_KEEPASPECTRATIO );
    ui->widget_18->installEventFilter ( clicker );

    ui->widget_19->setPixmap ( conf_root ( "a1.png" ) );
    ui->widget_19->setImageStyle ( QQtWidget::QQTTILEDWIDTH );
    ui->widget_19->installEventFilter ( clicker );

    ui->widget_20->setPixmap ( conf_root ( "a1.png" ) );
    ui->widget_20->setImageStyle ( QQtWidget::QQTTILEDHEIGHT );
    ui->widget_20->installEventFilter ( clicker );

    //ui->widget_26->setParent ( 0 );
    //ui->widget_26->show();

    ui->pushButton->iconTable().initNormal ( conf_root ( "close_0.png" ), conf_root ( "close_01.png" ) );
    ui->pushButton->iconTable().initCheck ( conf_root ( "close_0.png" ), conf_root ( "close_01.png" ) );
    ui->pushButton->iconTable().initOther ( conf_root ( "close_01.png" ), conf_root ( "close_01.png" ) );
    connect ( ui->pushButton, SIGNAL ( clicked ( bool ) ), this, SLOT ( clicked2() ) );
    ui->pushButton->installEventFilter ( this );

    ui->widget_22->setPixmap ( conf_root ( "second_0.png" ) );
    ui->widget_22->setImageStyle ( QQtWidget::QQTZOOM );
    ui->widget_22->installEventFilter ( clicker );
    ui->widget_23->setPixmap ( conf_root ( "third_0.png" ) );
    ui->widget_23->setImageStyle ( QQtWidget::QQTZOOM );
    ui->widget_23->installEventFilter ( clicker );
    ui->widget_24->setPixmap ( conf_root ( "four_0.png" ) );
    ui->widget_24->setImageStyle ( QQtWidget::QQTZOOM );
    ui->widget_24->installEventFilter ( clicker );


    ui->widget_25->setParent ( 0 );
    ui->widget_25->show();

    ui->label_6->setPixmap ( QPixmap ( conf_root ( "a1.png" ) ) );
    ui->label->setPixmap ( QPixmap ( conf_root ( "a1.png" ) ) );
    ui->label->installEventFilter ( clicker );

    ui->label_4->setPixmap ( QPixmap ( conf_root ( "a1.png" ) ) );
    ui->label_4->setAlignment ( Qt::AlignRight );
    ui->label_5->setPixmap ( QPixmap ( conf_root ( "a1.png" ) ) );
    ui->label_5->setAlignment ( Qt::AlignRight );
    ui->label_5->installEventFilter ( clicker );

    ui->label_2->setPixmap ( QPixmap ( conf_root ( "a1.png" ) ) );
    ui->label_2->setAlignment ( Qt::AlignLeft );
    ui->label_3->setPixmap ( QPixmap ( conf_root ( "a1.png" ) ) );
    ui->label_3->setAlignment ( Qt::AlignLeft );
    ui->label_3->installEventFilter ( clicker );

    ui->label_8->setPixmap ( QPixmap ( conf_root ( "a1.png" ) ) );
    //ui->label_8->setScaledContents ( true );
    //ui->label_8->setAutoFillBackground ( true );
    ui->label_7->setPixmap ( QPixmap ( conf_root ( "a1.png" ) ) );
    ui->label_7->installEventFilter ( clicker );
    ui->label_7->installEventFilter ( this );
    //ui->label_7->setScaledContents ( true );

    QStringList items;
    items << "Qt::AlignLeft"
          << "Qt::AlignRight"
          << "Qt::AlignHCenter"
          << "Qt::AlignJustify"
          << "Qt::AlignAbsolute"
          << "Qt::AlignHorizontal_Mask"
          << "Qt::AlignTop"
          << "Qt::AlignBottom"
          << "Qt::AlignVCenter"
          << "Qt::AlignBaseline"
          << "Qt::AlignVertical_Mask"
          << "Qt::AlignCenter"
          << "Qt::AlignRight|Qt::AlignTop"
          << "Qt::AlignRight|Qt::AlignBottom"
          << "Qt::AlignRight|Qt::AlignVCenter"
          << "Qt::AlignRight|Qt::AlignBaseline"
          << "Qt::AlignRight|Qt::AlignVertical_Mask"
          << "Qt::AlignHCenter|Qt::AlignTop"
          << "Qt::AlignHCenter|Qt::AlignBottom"
          << "Qt::AlignHCenter|Qt::AlignVCenter"
          << "Qt::AlignHCenter|Qt::AlignBaseline"
          << "Qt::AlignHCenter|Qt::AlignVertical_Mask"
          << "Qt::AlignJustify|Qt::AlignTop"
          << "Qt::AlignJustify|Qt::AlignBottom"
          << "Qt::AlignJustify|Qt::AlignVCenter"
          << "Qt::AlignJustify|Qt::AlignBaseline"
          << "Qt::AlignJustify|Qt::AlignVertical_Mask"
          << "Qt::AlignAbsolute|Qt::AlignTop"
          << "Qt::AlignAbsolute|Qt::AlignBottom"
          << "Qt::AlignAbsolute|Qt::AlignVCenter"
          << "Qt::AlignAbsolute|Qt::AlignBaseline"
          << "Qt::AlignAbsolute|Qt::AlignVertical_Mask"
          << "Qt::AlignHorizontal_Mask|Qt::AlignTop"
          << "Qt::AlignHorizontal_Mask|Qt::AlignBottom"
          << "Qt::AlignHorizontal_Mask|Qt::AlignVCenter"
          << "Qt::AlignHorizontal_Mask|Qt::AlignBaseline"
          << "Qt::AlignHorizontal_Mask|Qt::AlignVertical_Mask"
          ;

    ui->listWidget->addItems ( items );
    connect ( ui->listWidget, SIGNAL ( currentItemChanged ( QListWidgetItem*, QListWidgetItem* ) ),
              this, SLOT ( currentItemChanged ( QListWidgetItem*, QListWidgetItem* ) ) );

    //ui->label_9->setAlignment ( Qt::AlignCenter );
    ui->label_9->setPixmap ( QPixmap ( conf_root ( "a1.png" ) ) );
    ui->label_9->installEventFilter ( clicker );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clicked1 ( QPoint point )
{
    pline() << point;
}

void MainWindow::clicked2()
{
    pline();
}

void MainWindow::currentItemChanged ( QListWidgetItem* current, QListWidgetItem* previous )
{
    if ( !current )
        return;
    Qt::Alignment flag;
    if ( current->text() == "Qt::AlignLeft" )
    {
        flag = Qt::AlignLeft;
    }
    else if ( current->text() == "Qt::AlignRight" )
    {
        flag = Qt::AlignRight;
    }
    else if ( current->text() == "Qt::AlignHCenter" )
    {
        flag = Qt::AlignHCenter;
    }
    else if ( current->text() == "Qt::AlignJustify" )
    {
        flag = Qt::AlignJustify;
    }
    else if ( current->text() == "Qt::AlignAbsolute" )
    {
        flag = Qt::AlignAbsolute;
    }
    else if ( current->text() == "Qt::AlignHorizontal_Mask" )
    {
        flag = Qt::AlignHorizontal_Mask;
    }
    else if ( current->text() == "Qt::AlignTop" )
    {
        flag = Qt::AlignTop;
    }
    else if ( current->text() == "Qt::AlignBottom" )
    {
        flag = Qt::AlignBottom;
    }
    else if ( current->text() == "Qt::AlignVCenter" )
    {
        flag = Qt::AlignVCenter;
    }
    else if ( current->text() == "Qt::AlignBaseline" )
    {
        flag = Qt::AlignBaseline;
    }
    else if ( current->text() == "Qt::AlignVertical_Mask" )
    {
        flag = Qt::AlignVertical_Mask;
    }
    else if ( current->text() == "Qt::AlignCenter" )
    {
        flag = Qt::AlignCenter;
    }
    else if ( current->text() == "Qt::AlignRight" )
    {
        flag = Qt::AlignRight;
    }
    else if ( current->text() == "Qt::AlignRight|Qt::AlignTop" )
    {
        flag = Qt::AlignRight | Qt::AlignTop;
    }
    else if ( current->text() == "Qt::AlignRight|Qt::AlignBottom" )
    {
        flag = Qt::AlignRight | Qt::AlignBottom;
    }
    else if ( current->text() == "Qt::AlignRight|Qt::AlignVCenter" )
    {
        flag = Qt::AlignRight | Qt::AlignVCenter;
    }
    else if ( current->text() == "Qt::AlignRight|Qt::AlignBaseline" )
    {
        flag = Qt::AlignRight | Qt::AlignBaseline;
    }
    else if ( current->text() == "Qt::AlignRight|Qt::AlignVertical_Mask" )
    {
        flag = Qt::AlignRight | Qt::AlignVertical_Mask;
    }
    else if ( current->text() == "Qt::AlignHCenter|Qt::AlignTop" )
    {
        flag = Qt::AlignHCenter | Qt::AlignTop;
    }
    else if ( current->text() == "Qt::AlignHCenter|Qt::AlignBottom" )
    {
        flag = Qt::AlignHCenter | Qt::AlignBottom;
    }
    else if ( current->text() == "Qt::AlignHCenter|Qt::AlignVCenter" )
    {
        flag = Qt::AlignHCenter | Qt::AlignVCenter;
    }
    else if ( current->text() == "Qt::AlignHCenter|Qt::AlignBaseline" )
    {
        flag = Qt::AlignHCenter | Qt::AlignBaseline;
    }
    else if ( current->text() == "Qt::AlignHCenter|Qt::AlignVertical_Mask" )
    {
        flag = Qt::AlignHCenter | Qt::AlignVertical_Mask;
    }
    else if ( current->text() == "Qt::AlignJustify|Qt::AlignTop" )
    {
        flag = Qt::AlignJustify | Qt::AlignTop;
    }
    else if ( current->text() == "Qt::AlignJustify|Qt::AlignBottom" )
    {
        flag = Qt::AlignJustify | Qt::AlignBottom;
    }
    else if ( current->text() == "Qt::AlignJustify|Qt::AlignVCenter" )
    {
        flag = Qt::AlignJustify | Qt::AlignVCenter;
    }
    else if ( current->text() == "Qt::AlignJustify|Qt::AlignBaseline" )
    {
        flag = Qt::AlignJustify | Qt::AlignBaseline;
    }
    else if ( current->text() == "Qt::AlignJustify|Qt::AlignVertical_Mask" )
    {
        flag = Qt::AlignJustify | Qt::AlignVertical_Mask;
    }
    else if ( current->text() == "Qt::AlignAbsolute|Qt::AlignTop" )
    {
        flag = Qt::AlignAbsolute | Qt::AlignTop;
    }
    else if ( current->text() == "Qt::AlignAbsolute|Qt::AlignBottom" )
    {
        flag = Qt::AlignAbsolute | Qt::AlignBottom;
    }
    else if ( current->text() == "Qt::AlignAbsolute|Qt::AlignVCenter" )
    {
        flag = Qt::AlignAbsolute | Qt::AlignVCenter;
    }
    else if ( current->text() == "Qt::AlignAbsolute|Qt::AlignBaseline" )
    {
        flag = Qt::AlignAbsolute | Qt::AlignBaseline;
    }
    else if ( current->text() == "Qt::AlignAbsolute|Qt::AlignVertical_Mask" )
    {
        flag = Qt::AlignAbsolute | Qt::AlignVertical_Mask;
    }
    else if ( current->text() == "Qt::AlignHorizontal_Mask|Qt::AlignTop" )
    {
        flag = Qt::AlignHorizontal_Mask | Qt::AlignTop;
    }
    else if ( current->text() == "Qt::AlignHorizontal_Mask|Qt::AlignBottom" )
    {
        flag = Qt::AlignHorizontal_Mask | Qt::AlignBottom;
    }
    else if ( current->text() == "Qt::AlignHorizontal_Mask|Qt::AlignVCenter" )
    {
        flag = Qt::AlignHorizontal_Mask | Qt::AlignVCenter;
    }
    else if ( current->text() == "Qt::AlignHorizontal_Mask|Qt::AlignBaseline" )
    {
        flag = Qt::AlignHorizontal_Mask | Qt::AlignBaseline;
    }
    else if ( current->text() == "Qt::AlignHorizontal_Mask|Qt::AlignVertical_Mask" )
    {
        flag = Qt::AlignHorizontal_Mask | Qt::AlignVertical_Mask;
    }
    ui->label_7->setAlignment ( flag );
    ui->label_8->setAlignment ( flag );
}


bool MainWindow::eventFilter ( QObject* watched, QEvent* event )
{
    if ( event->type() == QEvent::Paint )
        return QMainWindow::eventFilter ( watched, event );
    pline() << watched << event->type();
    //不管用
    if ( event->type() == QEvent::Enter )
        ui->pushButton->updateGeometry();
    return QMainWindow::eventFilter ( watched, event );
}
