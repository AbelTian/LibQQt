#include <qqtnamedpipe.h>
#include <qqtnamedpipeprivate.h>

QQtNamedPipe::QQtNamedPipe ( const QString& key, QObject* parent )
    : QObject ( parent ), mKey ( key )
{
    //创建客户端句柄
    p0 = 0;
    c0 = QQtNamedPipeClientInstance ( p0, this );

    //创建服务器句柄
    pm0 = 0;
    s0 = QQtNamedPipeServerInstance ( pm0, this );

    connect ( c0, SIGNAL ( signalConnectSucc() ),
              this, SLOT ( slotConnectSuccess() ) );
    connect ( c0, SIGNAL ( signalConnectFail() ),
              this, SLOT ( slotConnectFail() ) );

    connect ( c0, SIGNAL ( stateChanged ( QLocalSocket::LocalSocketState ) ),
              this, SLOT ( slotSocketStateChanged ( QLocalSocket::LocalSocketState ) ) );

    hasServer = true;
    bAccepted = false;

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

bool QQtNamedPipe::initializer()
{
    bool ret = create ( );
    ret = attach();
}

void QQtNamedPipe::write ( const QByteArray& bytes )
{
    p0->sendCommand0x0b ( bytes );
    c0->waitForBytesWritten();
    pline();
    //c0->waitForReadyRead();
    pline();
}

QByteArray QQtNamedPipe::read ( int size )
{
    p0->sendCommand0x0a ( size );
    c0->waitForBytesWritten();
    pline();
    //c0->waitForReadyRead();
    pline();
    return p0->bytes();
}

bool QQtNamedPipe::create()
{
    //准备连接到这个服务器
    c0->setServerIPAddress ( "QQtNamedPipeServer" );
    c0->sendConnectToHost();
    c0->waitForConnected();
    return true;

    //这一个server管理所有的pipe了。 第一次返回true，后来返回false，但是可以用。
    bool  ret = false;
    if ( !s0->isListening() )
    {
        s0->listen ( "QQtNamedPipeServer" );
        pline() << "start listen....";
    }
    return ret;
}

bool QQtNamedPipe::attach()
{
    bool ret = 0;
    //c0->sendConnectToHost();
    //c0->waitForConnected();
    p0->sendCommand0x01 ( mKey );
    pline();
    ret = c0->waitForBytesWritten();
    pline();
    //ret = c0->waitForReadyRead();
    pline();
    return ret;
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
            if ( !hasServer )
                return;
            hasServer = false;
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
    pline() << "success";
    //如果有Server，说明这个Server不是我创建的。
    pline() << "hasServer:" << hasServer;
    //Windows下LocalServer用的pipe实现的，然后，必须用\n结束报文吗？！！！！
    if ( !hasServer )
        bAccepted = true;
}

void QQtNamedPipe::slotConnectFail()
{
    pline() << "fail";
#ifdef Q_OS_WIN
    hasServer = false;
    s0->listen ( "QQtNamedPipeServer" );
    c0->sendConnectToHost();
#else
    //refused or notfound
    if ( c0->error() == QLocalSocket::ConnectionRefusedError )
    {
        //这个的错误很严重，被启动的那个App走的时候没有关闭server。在这里关闭。
        QLocalServer::removeServer ( "QQtNamedPipeServer" );
    }
    c0->sendDisConnectFromHost();
#endif
}

