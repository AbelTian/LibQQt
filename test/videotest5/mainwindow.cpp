#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );

    manager = new QQtV4L2VideoManager ( this );
    connect ( manager, SIGNAL ( readyRead ( QImage ) ), this, SLOT ( slotCaptured ( QImage ) ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    manager->startCapture();
}

void MainWindow::on_pushButton_2_clicked()
{
    manager->stopCapture();
}

void MainWindow::slotCaptured ( const QImage& img )
{
    ui->widget->setPixmap ( img );
}
