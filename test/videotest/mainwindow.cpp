#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );

    input = new QQtVideoInput ( this );
    pline() << input->defaultCamera();
    pline() << input ->availableCameras();

    pline() << input->viewFinderSettings().pixelFormat();
    pline() << input->camera()->supportedViewfinderPixelFormats();

    connect ( input, SIGNAL ( readyRead ( QImage ) ), this, SLOT ( slotImageComing ( QImage ) ) );
    connect ( input, SIGNAL ( readyReadCapture ( QImage ) ), this, SLOT ( slotCapture ( QImage ) ) );

    input2 = new QQtVideoInput ( this );
    connect ( input2, SIGNAL ( readyRead ( QImage ) ), this, SLOT ( slotImageComing2 ( QImage ) ) );

    QThread* thread = new QThread();
    input2->moveToThread ( thread );
    thread->start();

    connect ( ui->pushButton_3, SIGNAL ( released() ), input, SLOT ( capture() ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotImageComing ( QImage img )
{
    ui->qqtwidget->setPixmap ( img );
}

void MainWindow::slotImageComing2 ( QImage img )
{
    ui->qqtwidget_2->setPixmap ( img );
    ui->qqtwidget_2->update();
}

void MainWindow::slotCapture ( QImage image )
{
    ui->qqtwidget_3->setPixmap ( image );
}

void MainWindow::on_pushButton_clicked()
{
    input->start();
    input2->start();
}

void MainWindow::on_pushButton_2_clicked()
{
    input->stop();
    input2->stop();
}
