#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qqtslideeffecttabbar.h>
#include <qqtpictureeffecttabwidget.h>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*
    ui->w60->setFixedHeight(30);
    QQtSlideEffectTabBar* bar = new QQtSlideEffectTabBar(ui->tab_6);
    QQtSlideEffectTabBar* bar2 = new QQtSlideEffectTabBar(ui->tab_6);
    bar->addTab("xxx");
    bar->addTab("ccc");
    bar2->setShape(QQtSlideEffectTabBar::RoundedEast);
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
    QQtSlideEffectTabBar* bar2 = new QQtSlideEffectTabBar(ui->tab_6);
    ui->tb1->setTabBar(bar2);
    */
    //QQtSlideEffectTabBar* bar = new QQtSlideEffectTabBar(ui->tb0);
    //ui->tb0->setTabBar(bar);
    //ui->tb0->setObjectName("tb0");

    ui->w77->addTab("ddd");
    ui->w77->addTab("xxxx");
    ui->w77->setFixedHeight(28);


    ui->tw0->setStyleSheet("QTabWidget#tw0 QTabBar::tab { width:90px; height:30px; }");
    QQtPictureEffectTabBar* tab = (QQtPictureEffectTabBar*) ui->tw0->localTabBar();
    tab->setIconStyle(QQtPictureEffectTabBar::IconStyle_Left_And_RightText);
    tab->setTabPixmap(0, "./skin/default/bt_setting.png", "./skin/default/bt_setting_press.png");
    tab->setTabPixmap(1, "./skin/default/bt_user.png", "./skin/default/bt_user_press.png");

    ui->tw1->setStyleSheet("QTabWidget#tw1 QTabBar::tab { width:90px; height:30px; }");
    QQtPictureEffectTabBar* tab1 = (QQtPictureEffectTabBar*) ui->tw1->localTabBar();
    tab1->setIconStyle(QQtPictureEffectTabBar::IconStyle_Left_And_RightText);
    tab1->setTabPixmap(0, "./skin/default/bt_setting.png", "./skin/default/bt_setting_press.png");
    tab1->setTabPixmap(1, "./skin/default/bt_user.png", "./skin/default/bt_user_press.png");

    ui->tb0->setStyleSheet("QTabWidget#tb0 QTabBar::tab { width:90px; height:30px; }");
}

MainWindow::~MainWindow()
{
    delete ui;
}
