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
    //p = QQtClientUdpConnectionInstance ( this );
    p = new QQtClientProtocol ( parent );

    QQtTcpClient* s0 = NULL;
    if(!s0){
        s0 = new QQtTcpClient ( parent );
        s0->installProtocol ( p );
        QStringList ip;
        ip << "192.168.0.100";
        s0->setServerIPAddress ( ip );
        s0->setServerPort ( 8001 );
        s0->sendConnectToHost();
    }

    QQtUdpClient* s1 = NULL;
    if ( !s1 )
    {
        s1 = new QQtUdpClient ( parent );
        s1->installProtocol ( p );
        QStringList ip;
        ip << "192.168.0.100";
        s1->setServer ( ip[0], 8200 );
        //我接收服务器消息，所以需要绑定本地端口
        s1->bind ( QHostAddress::Any, 8210 );
    }

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
