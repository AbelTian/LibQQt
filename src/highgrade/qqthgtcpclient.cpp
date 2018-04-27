#include "qqthgtcpclient.h"

#include <QTcpSocket>
#include <QHostInfo>

#include "qqtcore.h"

QQtHgTcpClient::QQtHgTcpClient ( QObject* parent ) :
    QTcpSocket ( parent )
{
    connect ( this, SIGNAL ( stateChanged ( QAbstractSocket::SocketState ) ), this,
              SLOT ( socketStateChanged ( QAbstractSocket::SocketState ) ) );
    // connected
    connect ( this, SIGNAL ( connected() ), this, SLOT ( socketConnected() ) );
    // disconnected
    connect ( this, SIGNAL ( disconnected() ), this, SLOT ( socketDisconnect() ) );
    // domain
    connect ( this, SIGNAL ( hostFound() ), this, SLOT ( domainHostFound() ) );
    // error
    connect ( this, SIGNAL ( error ( QAbstractSocket::SocketError ) ), this,
              SLOT ( socketErrorOccured ( QAbstractSocket::SocketError ) ) );

    connect ( this, SIGNAL ( readyRead() ), this, SLOT ( readyReadData() ) );

    connect ( this, SIGNAL ( bytesWritten ( qint64 ) ), this, SLOT ( updateProgress ( qint64 ) ) );

    connect ( this, SIGNAL ( bytesWritten ( qint64 ) ), this, SIGNAL ( signalUpdateProgress ( qint64 ) ) );

    /*
     * 心情很好，但是给自己带来麻烦顾虑，也不能给系统节约多少什么资源, Qt::QueuedConnection);
     */

    setSocketOption ( QAbstractSocket::LowDelayOption, 0 );
    setSocketOption ( QAbstractSocket::KeepAliveOption, 0 );
    setReadBufferSize ( _TCP_RECVBUFF_SIZE );

    m_PORT = 0;
    /*
     * 启动连接
     */
    eConType = 0;
    m_protocolManager = NULL;
}

QQtHgTcpClient::~QQtHgTcpClient()
{
}

void QQtHgTcpClient::installProtocolManager ( QQtHgProtocolManager* stackGroup )
{
    if ( m_protocolManager )
        return;

    m_protocolManager = stackGroup;

    QListIterator<QQtHgProtocol*> itor ( m_protocolManager->installedProtocol() );
    while ( itor.hasNext() )
    {
        //安装一个一个的句柄
        QQtHgProtocol* stack = itor.next();
        connect ( stack, SIGNAL ( write ( const QByteArray& ) ),
                  this, SLOT ( writeData ( const QByteArray& ) ) );
        stack->createClientBuffer ( this );
    }

}

void QQtHgTcpClient::uninstallProtocolManager ( QQtHgProtocolManager* stackGroup )
{
    Q_UNUSED ( stackGroup )

    if ( !m_protocolManager )
        return;

    QListIterator<QQtHgProtocol*> itor ( m_protocolManager->installedProtocol() );
    while ( itor.hasNext() )
    {
        //安装一个一个的句柄
        QQtHgProtocol* stack = itor.next();
        disconnect ( stack, SIGNAL ( write ( const QByteArray& ) ),
                     this, SLOT ( writeData ( const QByteArray& ) ) );
        stack->deleteClientBuffer ( this );
    }

    m_protocolManager = NULL;
}

QQtHgProtocolManager* QQtHgTcpClient::installedProtocolManager()
{
    return m_protocolManager;
}

void QQtHgTcpClient::SendConnectMessage()
{
    pline() << isValid() << isOpen() << state();

    if ( !isValid() && !isOpen() )
    {
        connectToSingelHost();
        return;
    }

    if ( state() == HostLookupState ||
         state() == ConnectingState )
    {
        emit signalConnecting();
        return;
    }

    if ( state() == ConnectedState )
        emit signalConnectSucc();

    return;
}


int QQtHgTcpClient::SendDisConnectFromHost()
{
    pline() << isValid() << isOpen() << state();

    if ( isValid() || isOpen() )
    {
#if defined(__WIN32__) || defined (__WIN64__)
        ;
#else
        shutdown ( this->socketDescriptor(), SHUT_RDWR );
#endif
        disconnectFromHost();
        waitForDisconnected();
        close();
        emit signalDisConnectSucc();
    }

    return true;
}

void QQtHgTcpClient::domainHostFound()
{
    pline();
}

/**
 * @brief QQtHgTcpClient::socketStateChanged
 * @param eSocketState
 * 状态函数
 */
void QQtHgTcpClient::socketStateChanged ( QAbstractSocket::SocketState eSocketState )
{
    pline() << eSocketState;

    switch ( eSocketState )
    {
        case QAbstractSocket::HostLookupState:
        case QAbstractSocket::ConnectingState:
            break;

        case QAbstractSocket::ConnectedState:
            break;

        case QAbstractSocket::ClosingState:
            break;

        case QAbstractSocket::UnconnectedState:
            eConType++;
            break;

        default:
            break;
    }
}

/**
 * @brief QQtHgTcpClient::socketErrorOccured
 * @param e
 * 状态函数
 */
void QQtHgTcpClient::socketErrorOccured ( QAbstractSocket::SocketError e )
{
    /*
     * 在错误状态下重新连接其他热点，直到确定连接类型，写入配置文件
     */
    pline() << e;

    switch ( e )
    {
        case QAbstractSocket::RemoteHostClosedError:
            break;

        case QAbstractSocket::HostNotFoundError:
        default:
            emit signalConnectFail();
            break;
    }
}

/**
 * @brief QQtHgTcpClient::socketConnected
 * 功能接口
 */
void QQtHgTcpClient::socketConnected()
{
    pline() << peerName() << peerAddress().toString() << peerPort();
    /*
     * 这个步骤，socket重建，资源重新开始
     */
    emit signalConnectSucc();
}

/**
 * @brief QQtHgTcpClient::socketDisconnect
 * 功能接口
 */
void QQtHgTcpClient::socketDisconnect()
{
    pline();
}

void QQtHgTcpClient::updateProgress ( qint64 bytes )
{
    Q_UNUSED ( bytes )
    //pline() << bytes;
}

void QQtHgTcpClient::connectToSingelHost()
{
    int contype = eConType % m_serverIP.size();
    QString ip = m_serverIP.at ( contype );
    connectToHost ( QHostAddress ( ip ), m_PORT );

    pline() << peerName() << m_PORT;
}


void QQtHgTcpClient::readyReadData()
{
    //self, protocol, message
    if ( !m_protocolManager )
    {
        pline() << "please install protocol manager for your client.";
        deleteLater();
        return;
    }

    QByteArray bytes;
    bytes = readAll();

    QByteArray tmpBytes = bytes;
    QListIterator<QQtHgProtocol*> itor ( m_protocolManager->installedProtocol() );
    while ( itor.hasNext() )
    {
        QQtHgProtocol* protocol = itor.next();
        protocol->translator ( this, tmpBytes );
    }
}

void QQtHgTcpClient::writeData ( const QByteArray& data )
{
    write ( data );
}
