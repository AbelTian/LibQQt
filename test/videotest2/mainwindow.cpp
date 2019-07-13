#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );

    manager = new QQtVideoManager ( this );
    pline() << manager->availableCameras();

    //设置输入
    connect ( ui->pushButton, SIGNAL ( clicked ( bool ) ), manager, SLOT ( startInput() ) );
    connect ( ui->pushButton_2, SIGNAL ( clicked ( bool ) ), manager, SLOT ( stopInput() ) );
    connect ( ui->pushButton_3, SIGNAL ( clicked ( bool ) ), manager, SLOT ( capture() ) );

    //设置输出
    manager->viewFinder() = ui->qqtwidget;

    //设置截图输出
    //使用Wrapper建立信号和槽关系......
    QQtVideoOutput* output1 =  new QQtVideoOutput ( this );
    output1->viewFinder() = ui->qqtwidget_2;

    //建立输入、输出关系
    connect ( manager, SIGNAL ( readyRead ( QImage ) ), manager, SLOT ( outputImage ( QImage ) ) );
    connect ( manager, SIGNAL ( readyReadCapture ( QImage ) ), output1, SLOT ( setPixmap ( QImage ) ) );

    //输入由页面控制，这里开启输出
    manager->startOutput();
    output1->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}
