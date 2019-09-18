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

    ui->pushButton->iconTable().initNormal ( conf_root ( "close_0.png" ), conf_root ( "close_01.png" ) );
    ui->pushButton->iconTable().initCheck ( conf_root ( "close_0.png" ), conf_root ( "close_01.png" ) );
    ui->pushButton->iconTable().initOther ( conf_root ( "close_01.png" ), conf_root ( "close_01.png" ) );
    connect ( ui->pushButton, SIGNAL ( clicked ( bool ) ), this, SLOT ( clicked2() ) );

    ui->widget_22->setPixmap ( conf_root ( "second_0.png" ) );
    ui->widget_22->setImageStyle ( QQtWidget::QQTZOOM );
    ui->widget_22->installEventFilter ( clicker );
    ui->widget_23->setPixmap ( conf_root ( "third_0.png" ) );
    ui->widget_23->setImageStyle ( QQtWidget::QQTZOOM );
    ui->widget_23->installEventFilter ( clicker );
    ui->widget_24->setPixmap ( conf_root ( "four_0.png" ) );
    ui->widget_24->setImageStyle ( QQtWidget::QQTZOOM );
    ui->widget_24->installEventFilter ( clicker );

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
