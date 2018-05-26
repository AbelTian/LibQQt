#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qqtslidetabbar.h>
#include <qqtpicturetabwidget.h>

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );
    /*
    ui->w60->setFixedHeight(30);
    QQtSlideTabBar* bar = new QQtSlideTabBar(ui->tab_6);
    QQtSlideTabBar* bar2 = new QQtSlideTabBar(ui->tab_6);
    bar->addTab("xxx");
    bar->addTab("ccc");
    bar2->setShape(QQtSlideTabBar::RoundedEast);
    bar2->addTab("yyy");
    bar2->addTab("ddd");

    QSpacerItem* space = new QSpacerItem(800, 30, QSizePolicy::Maximum);
    QGridLayout* lay = new QGridLayout(ui->tab_6);
    lay->addWidget(ui->w60, 1, 1, 1, 2);
    lay->addWidget(bar, 2, 1, 1, 2);
    lay->addWidget(bar2, 3, 1, 1, 1);
    lay->addItem(space, 3, 2, 1, 1);

    ui->tab_6->setLayout(lay);
    */
    /*
    QQtSlideTabBar* bar2 = new QQtSlideTabBar(ui->tab_6);
    ui->tb1->setTabBar(bar2);
    */
    //QQtSlideTabBar* bar = new QQtSlideTabBar(ui->tb0);
    //ui->tb0->setTabBar(bar);
    //ui->tb0->setObjectName("tb0");

    ui->w77->addTab ( "ddd" );
    ui->w77->addTab ( "xxxx" );
    ui->w77->setFixedHeight ( 28 );


    ui->tw0->setStyleSheet ( "QTabWidget#tw0 QTabBar::tab { width:72px; height:90px; }" );
    QQtPictureTabBar* tab = ( QQtPictureTabBar* ) ui->tw0->localTabBar();
    tab->setIconStyle ( QQtPictureTabBar::IconStyle_Top_And_BottomText );
    tab->setTabPixmap ( 0, "./skin/default/bt_setting.png", "./skin/default/bt_setting_press.png" );
    tab->setTabPixmap ( 1, "./skin/default/bt_dispel.png", "./skin/default/bt_dispel_press.png" );
    tab->setContentsMargins ( 2, 2, 2, 2 );

    ui->tw1->setStyleSheet ( "QTabWidget#tw1 QTabBar::tab { width:90px; height:30px; }" );
    QQtPictureTabBar* tab1 = ( QQtPictureTabBar* ) ui->tw1->localTabBar();
    tab1->setIconStyle ( QQtPictureTabBar::IconStyle_Left_And_RightText );
    tab1->setTabPixmap ( 0, "./skin/default/bt_bt_hover.png", "./skin/default/bt_bt_press.png" );
    tab1->setTabIcon ( 0, "./skin/default/bk_user_normal.png", "./skin/default/bk_user_press.png" );
    tab1->setTabPixmap ( 1, "./skin/default/bt_bt_hover.png", "./skin/default/bt_bt_press.png" );
    pline() << tab1->contentsMargins();
    tab1->setContentsMargins ( 2, 2, 8, 2 );
    pline() << tab1->contentsMargins();

    ui->tb0->setStyleSheet ( "QTabWidget#tb0 QTabBar::tab { width:90px; height:30px; }" );
}

MainWindow::~MainWindow()
{
    delete ui;
}
