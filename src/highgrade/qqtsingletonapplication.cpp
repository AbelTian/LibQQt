#include <qqtsingletonapplication.h>
#include <qqtsingletonapplicationprivate.h>

QQtSingleTonApplication::QQtSingleTonApplication ( int& argc, char** argv ) : QQtApplication ( argc, argv )
{
    QQtApplication::setOrganizationName ( "QQtSingleTon" );
    QQtApplication::setOrganizationDomain ( "www.qqt.singleton.com" ); //
    //无论如何都要设置。
    QQtApplication::setApplicationName ( "QQtSingleTon" );

    hasServer = true;
    bAccepted = false;

    //创建客户端句柄
    p0 = 0;
    c0 = QQtSingleTonNamedPipeClientInstance ( p0 );

    //创建服务器句柄
    pm0 = 0;
    s0 = QQtSingleTonNamedPipeServerInstance ( pm0 );

    connect ( p0, SIGNAL ( signalAccept() ),
              this, SLOT ( slotAccept() ) );
    connect ( p0, SIGNAL ( signalReject() ),
              this, SLOT ( slotReject() ) );

    connect ( c0, SIGNAL ( signalConnectSucc() ),
              this, SLOT ( slotConnectSuccess() ) );
    connect ( c0, SIGNAL ( signalConnectFail() ),
              this, SLOT ( slotConnectFail() ) );

    connect ( c0, SIGNAL ( stateChanged ( QLocalSocket::LocalSocketState ) ),
              this, SLOT ( slotSocketStateChanged ( QLocalSocket::LocalSocketState ) ) );
}

QQtSingleTonApplication::~QQtSingleTonApplication()
{
#ifdef Q_OS_WIN
#else
    //linux下，如果被接受的app不删除这个server，那么无法启动了吆。
    if ( bAccepted )
        QLocalServer::removeServer ( qqtApp->applicationName() );
#endif
}

void QQtSingleTonApplication::startSingleTonInstance()
{
    c0->setServerIPAddress ( qqtApp->applicationName() );
    c0->sendConnectToHost();
    c0->waitForConnected();
}

void QQtSingleTonApplication::slotSocketStateChanged ( QLocalSocket::LocalSocketState eSocketState )
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
            s0->listen ( qqtApp->applicationName() );
            c0->sendConnectToHost();
#endif
            break;
        }
        default:
            break;
    }
}

void QQtSingleTonApplication::slotConnectSuccess()
{
    pline() << "success";
    //如果有Server，说明这个Server不是我创建的。
    pline() << "hasServer:" << hasServer;
    //Windows下LocalServer用的pipe实现的，然后，必须用\n结束报文吗？！！！！
    if ( !hasServer )
        bAccepted = true;

#ifdef Q_OS_WIN
    if ( !hasServer )
        return;
    QQtMsgBox::warning ( 0, tr ( "Has an app instance, exit." ) );
    //quit()和exit(0)都无法退出。
    ::exit ( 0 );
#else
    if ( !hasServer )
        return;
    QQtMsgBox::warning ( 0, tr ( "Has an app instance, exit." ) );
    //quit()和exit(0)都无法退出。linux也一样。
    ::exit ( 0 );
#if 0
    //太慢了，主窗口都显示出来了。
    if ( !hasServer )
        p0->sendCommand1();
    else
        p0->sendCommand2();
#endif
#endif
}

void QQtSingleTonApplication::slotConnectFail()
{
    pline() << "fail";
#ifdef Q_OS_WIN
    hasServer = false;
    s0->listen ( qqtApp->applicationName() );
    c0->sendConnectToHost();
#else
    //refused or notfound
    if ( c0->error() == QLocalSocket::ConnectionRefusedError )
    {
        //这个的错误很严重，被启动的那个App走的时候没有关闭server。在这里关闭。
        QLocalServer::removeServer ( qqtApp->applicationName() );
    }
    c0->sendDisConnectFromHost();
    //waitfordisconnnect也可以，在这里监听和开始连接。
#endif
}

void QQtSingleTonApplication::slotAccept()
{
    //通过了。
    pline() << "can start.";
}

void QQtSingleTonApplication::slotReject()
{
    //根据现在的设计，这个函数来不了，来的时候主窗口出来了，所以这个步骤删除了。
    pline() << "can't start, stop now.";
    QQtMsgBox::warning ( 0, tr ( "Has a app instance, exit." ) );
    quit();
}
