#include <qqtnamedpipe.h>
#include <qqtnamedpipeprivate.h>

//仅仅linux可用。
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

    connect ( c0, SIGNAL ( stateChanged ( QLocalSocket::LocalSocketState ) ),
              this, SLOT ( slotSocketStateChanged ( QLocalSocket::LocalSocketState ) ) );


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
    eLoop->exec();
    //c0->waitForReadyRead();
    pline();
}

QByteArray QQtNamedPipe::read ( int size )
{
    p0->sendCommand0x0a ( size );
    c0->waitForBytesWritten();
    pline();
    eLoop->exec();
    //c0->waitForReadyRead();
    pline();
    return p0->bytes();
}

bool QQtNamedPipe::initializer()
{
    //如果一切工作正常，应该打印的地方都是true。
    bool ret = false;
    //检测 或许创建Server
    ret = hasServer();
    if ( !ret )
        ret = create();
    pline() << "create pipe server:" << ret;
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
    c0->waitForConnected();
    return mHasServer;
}

bool QQtNamedPipe::create()
{
    bool  ret = false;

    //这个是有原因的，linux下unconnect来的特别慢。
    //c0->sendDisConnectFromHost();

    ret = s0->listen ( "QQtNamedPipeServer" );
#ifdef Q_OS_WIN
    //给windows缓冲10ms
    QQtSleep ( 10 );
#endif
    return ret;

    //准备连接到这个服务器
    c0->setServerIPAddress ( "QQtNamedPipeServer" );
    c0->sendConnectToHost();
    pline();
    ret = c0->waitForConnected();
    pline();
    return ret;

    //这一个server管理所有的pipe了。 第一次返回true，后来返回false，但是可以用。
    if ( !s0->isListening() )
    {
        s0->listen ( "QQtNamedPipeServer" );
        pline() << "start listen....";
    }
    return ret;
}

bool QQtNamedPipe::attach()
{
    bool ret = false;
    c0->sendConnectToHost();
    //这里应该成功返回，如果失败返回，mHasServer=false,那么，呵呵....
    ret = c0->waitForConnected();
    return ret;

    pline();
#ifdef Q_OS_WIN
    //需要睡一会儿，Windows在socket连接的时机会堵塞一下。
    //c0->waitForConnected();
    pline();
    p0->sendCommand0x01 ( mKey );
    //不知道为什么，Windows刚刚连接成功，打印都来了，这个地方堵死。后来打印又来了。别的世界的打印提前打到这边来了？
    pline();
    //ret = c0->waitForBytesWritten();
    pline();
    //eLoop->exec();
#else
    p0->sendCommand0x01 ( mKey );
    pline();
    ret = c0->waitForBytesWritten();
    pline();
    eLoop->exec();
#endif
    //无论如何不应该在这里等待。
    //ret = c0->waitForReadyRead();
    pline();
    return ret;
}

bool QQtNamedPipe::setKey()
{
    bool ret = false;
    p0->sendCommand0x01 ( mKey );
    QQtBlockSignal b1;
    b1.addsignal ( p0, SIGNAL ( signalSuccessCommand() ) );
    b1.lock ( 10000 );
    return true;
}


void QQtNamedPipe::slotSocketStateChanged ( QLocalSocket::LocalSocketState eSocketState )
{
    switch ( eSocketState )
    {
        case QLocalSocket::ConnectingState:
            break;

        case QLocalSocket::ConnectedState:
            break;

        case QLocalSocket::ClosingState:
            break;

        case QLocalSocket::UnconnectedState:
        {
#ifdef Q_OS_WIN
#else
            pline() << "unconnected";
            break;
            //???
            if ( !mHasServer )
                return;
            mHasServer = false;
            s0->listen ( "QQtNamedPipeServer" );
            c0->sendConnectToHost();
#endif
            break;
        }
        default:
            break;
    }
}

void QQtNamedPipe::slotConnectSuccess()
{
    pline() << "connect pipe server success, has server";
    mHasServer = true;
    emit signalConnectComeBack();
    return;

    //如果有Server，说明这个Server不是我创建的。
    pline() << "hasServer:" << mHasServer;
    //Windows下LocalServer用的pipe实现的，然后，必须用\n结束报文吗？！！！！
    if ( !mHasServer )
        bAccepted = true;
}

void QQtNamedPipe::slotConnectFail()
{
    pline() << "connect pipe server fail, has no server";
    mHasServer = false;
    emit signalConnectComeBack();
    //到这里说明，这个server肯定是我创建的。
    bAccepted = true;
    return;

#ifdef Q_OS_WIN
    c0->sendDisConnectFromHost();
    s0->listen ( "QQtNamedPipeServer" );
    c0->sendConnectToHost();
#else
    mHasServer = true;//??
    //refused or notfound
    if ( c0->error() == QLocalSocket::ConnectionRefusedError )
    {
        //这个的错误很严重，被启动的那个App走的时候没有关闭server。在这里关闭。
        QLocalServer::removeServer ( "QQtNamedPipeServer" );
    }
    c0->sendDisConnectFromHost();
#endif
}

