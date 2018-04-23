#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );

    // serialport example
    // tcpsocket example
    // websocket?
    //
    p = QQtClientConnectionInstance ( this );
    connect ( p, SIGNAL ( signalServerSay ( QString ) ),
              this, SLOT ( on_recv_say_hello ( QString ) ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    p->sendA1Command ( ui->lineEdit->text() );
}

void MainWindow::on_recv_say_hello ( QString a )
{
    pline() << a;
    ui->textBrowser->append(a + "\r\n");
}
