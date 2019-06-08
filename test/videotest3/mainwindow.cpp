#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );

    manager = new QQtVideoManager ( this );

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

    //建立照相机图像控制关系
    pline() << manager->expose()->supportedIsoSensitivities();
    form = new CameraControllerForm();
    form->show();
    connect ( form, SIGNAL ( isovalue ( int ) ), manager->expose(), SLOT ( setManualIsoSensitivity ( int ) ) );
    connect ( form, SIGNAL ( isomodel ( bool ) ), this, SLOT ( slotISOModelChanged ( bool ) ) );

    //输入由页面控制，这里开启输出
    manager->startOutput();
    output1->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotISOModelChanged ( bool iso )
{
    pline() << iso;
    if ( iso )
    {
        manager->expose()->setAutoIsoSensitivity();
    }
    else
    {

    }
}

void MainWindow::moveEvent ( QMoveEvent* event )
{
    form->setGeometry ( geometry().left() - 140, geometry().top(), 120, geometry().height() );
}

void MainWindow::resizeEvent ( QResizeEvent* event )
{
    QSize size = event->size();
    form->setFixedHeight ( size.height() );
}


void MainWindow::closeEvent ( QCloseEvent* event )
{
    form->close();
}

void MainWindow::showEvent ( QShowEvent* event )
{
    form->setGeometry ( geometry().left() - 140, geometry().top(), 120, geometry().height() );
}

void MainWindow::hideEvent ( QHideEvent* event )
{
    form->hide();
}
