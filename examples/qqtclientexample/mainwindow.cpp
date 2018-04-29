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
    //Tcp OK
    //p = QQtClientConnectionInstance ( this );
    p = QQtClientUdpConnectionInstance ( this );
    connect ( p, SIGNAL ( signalServerSay ( QString ) ),
              this, SLOT ( on_recv_say_hello ( QString ) ),
              Qt::QueuedConnection );

    //QQtClient2Protocol* p0 = QQtClient2ConnectionInstance ( this );
    //p0->sendCommand1();
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
    //这个地方不要加/r/n 程序会死。
    ui->textBrowser->append ( a );
}
