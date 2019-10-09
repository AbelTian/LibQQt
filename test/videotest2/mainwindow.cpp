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

    //建立输入、输出关系
    connect ( manager, SIGNAL ( readyRead ( QImage ) ), manager, SLOT ( outputImage ( QImage ) ) );

    //输入由页面控制，这里开启输出
    manager->startOutput();

    //设置截图输出
    //使用Wrapper建立信号和槽关系......
    QQtVideoOutput* output1 =  new QQtVideoOutput ( this );
    output1->viewFinder() = ui->qqtwidget_2;
    connect ( manager, SIGNAL ( readyReadCapture ( QImage ) ), output1, SLOT ( setPixmap ( QImage ) ) );
    output1->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_4_clicked()
{
    QCameraViewfinderSettings s0 = manager->camera()->viewfinderSettings();
    pline() << s0.pixelFormat();
    pline() << s0.minimumFrameRate() << s0.maximumFrameRate();
    pline() << s0.pixelAspectRatio();
    pline() << s0.resolution();


    return;

    //不管用
    QCameraViewfinderSettings set = manager->camera()->viewfinderSettings();
    set.setPixelFormat ( QVideoFrame::Format_RGB24 );
    manager->camera()->setViewfinderSettings ( set );

    return;

    //会崩溃
    for ( int i = 0; i < manager->camera()->supportedViewfinderSettings().size(); i++ )
    {
        QCameraViewfinderSettings& set = manager->camera()->supportedViewfinderSettings() [i];
        //pline() << manager->camera()->supportedViewfinderFrameRateRanges();
        pline() << manager->camera()->supportedViewfinderResolutions ( set );
        pline() << manager->camera()->supportedViewfinderPixelFormats ( set );
    }

}

void MainWindow::on_pushButton_5_clicked()
{
    manager->inputManager()->setViewMirror ( true, false );
}

void MainWindow::on_pushButton_6_clicked()
{
    manager->inputManager()->setViewMirror ( false, false );
}

void MainWindow::on_pushButton_7_clicked()
{
    manager->inputManager()->setViewMirror ( true, true );
}

void MainWindow::on_pushButton_8_clicked()
{
    manager->inputManager()->setViewMirror ( false, true );
}

void MainWindow::on_pushButton_9_clicked()
{
    if ( manager->inputManager()->mirrorEnabled() )
        manager->inputManager()->setMirrorEnable ( false );
    else
        manager->inputManager()->setMirrorEnable ( true );
}
