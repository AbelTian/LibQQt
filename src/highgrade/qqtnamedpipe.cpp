#include <qqtnamedpipe.h>
#include <qqtnamedpipeprivate.h>

//仅仅linux可用？
//这个还需要修改，修改好移动到core.cpp
void QQtSleepSignal2 ( int millsecond, const QObject* obj, const char* signal )
{
    //initilizer
    QEventLoop eventloop;
    QObject::connect ( obj, signal, &eventloop, SLOT ( quit() ) );

    QTimer timer;
    timer.setSingleShot ( true );
    timer.setInterval ( millsecond );
    QObject::connect ( &timer, SIGNAL ( timeout() ), &eventloop, SLOT ( quit() ) );

    //process
    eventloop.exec();

    //clear
    if ( timer.isActive() )
        timer.stop();

}



QQtNamedPipe::QQtNamedPipe ( const QString& key, QObject* parent )
    : QObject ( parent ), mKey ( key )
{
    //创建客户端句柄
    p0 = 0;
    c0 = QQtNamedPipeClientInstance ( p0, this );

    //创建服务器句柄
    pm0 = 0;
    s0 = QQtNamedPipeServerInstance ( pm0, this );

    //用于检测是否存在服务器。
    connect ( c0, SIGNAL ( signalConnectSucc() ),
              this, SLOT ( slotConnectSuccess() ) );
    connect ( c0, SIGNAL ( signalConnectFail() ),
              this, SLOT ( slotConnectFail() ) );

    mHasServer = false;
    bAccepted = false;

    eLoop = new QEventLoop ( this );
    connect ( p0, SIGNAL ( signalSuccessCommand() ), eLoop, SLOT ( quit() ) );
}

QQtNamedPipe::~QQtNamedPipe()
{
#ifdef Q_OS_WIN
#else
    //linux下，如果被接受的app不删除这个server，那么无法启动了吆。
    if ( bAccepted )
        QLocalServer::removeServer ( "QQtNamedPipeServer" );
#endif
}

void QQtNamedPipe::write ( const QByteArray& bytes )
{
    p0->sendCommand0x0b ( bytes );
    c0->waitForBytesWritten();
    pline();
    QQtBlockSignal b1;
    b1.addsignal ( p0, SIGNAL ( signalSuccessCommand() ) );
    b1.lock ( 2000 );
    //c0->waitForReadyRead();
    pline();
}

QByteArray QQtNamedPipe::read ( int size )
{
    p0->sendCommand0x0a ( size );
    c0->waitForBytesWritten();
    pline();
    QQtBlockSignal b1;
    b1.addsignal ( p0, SIGNAL ( signalSuccessCommand() ) );
    b1.lock ( 2000 );
    //c0->waitForReadyRead();
    pline();
    return p0->bytes();
}

bool QQtNamedPipe::initializer()
{
    bool ret = false;
    //检测 或许创建Server
    ret = hasServer();
    pline() << "has server:" << ret;
    if ( !ret )
    {
        ret = create();
        pline() << "create pipe server:" << ret;
    }
    //连接
    ret = attach();
    pline() << "connect to pipe server:" << ret;
    //设置key
    ret = setKey();
    pline() << "send key to pipe server:" << ret;
    return ret;
}

bool QQtNamedPipe::hasServer()
{
    //c0 conn fail +c0 refused error
    c0->setServerIPAddress ( "QQtNamedPipeServer" );
    c0->sendConnectToHost();
    bool ret = c0->waitForConnected();
    //很忠诚的返回值。
    //pline() << "check server, wait for connected:" << ret;
    return ret;
}

bool QQtNamedPipe::create()
{
    bool  ret = false;
    ret = s0->listen ( "QQtNamedPipeServer" );
    return ret;
}

bool QQtNamedPipe::attach()
{
    bool ret = false;
    c0->sendConnectToHost();
    //这里应该成功返回，如果失败返回，mHasServer=false,那么，呵呵....
    ret = c0->waitForConnected();
    return ret;
}

bool QQtNamedPipe::setKey()
{
    bool ret = false;
    p0->sendCommand0x01 ( mKey );
    QQtBlockSignal b1;
    b1.addsignal ( p0, SIGNAL ( signalSuccessCommand() ) );
    b1.lock ( 2000 );
    return true;
}


void QQtNamedPipe::slotConnectSuccess()
{
    mHasServer = true;
    emit signalConnectComeBack();
    return;
}

void QQtNamedPipe::slotConnectFail()
{
    if ( c0->error() == QLocalSocket::ConnectionRefusedError )
    {
        //这个的错误很严重，被启动的那个App走的时候没有关闭server。在这里关闭。
        QLocalServer::removeServer ( "QQtNamedPipeServer" );
    }
    mHasServer = false;
    emit signalConnectComeBack();
    //到这里说明，这个server肯定是我创建的。
    bAccepted = true;
    return;
}

