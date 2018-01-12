#include "qqtsocketudpserver.h"
#include "qqtnetwork.h"
#include <QNetworkDatagram>
#include <QNetworkInterface>

QQtSocketUdpServer::QQtSocketUdpServer ( QObject* parent ) : QUdpSocket ( parent )
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

    connect ( this, SIGNAL ( bytesWritten ( qint64 ) ), this, SLOT ( updateProgress ( qint64 ) ) );

    connect ( this, SIGNAL ( bytesWritten ( qint64 ) ), this, SIGNAL ( signalUpdateProgress ( qint64 ) ) );

    connect ( this, SIGNAL ( signalRunListening() ),
              this, SLOT ( slotRunListening() ) );

    m_protocol = NULL;
    m_thread = new QThread ( this );
    moveToThread ( m_thread );

    startListening();
}

QQtSocketUdpServer::~QQtSocketUdpServer()
{
    stopListening();
}

void QQtSocketUdpServer::installProtocol ( QQtUdpProtocol* stack )
{
    if ( m_protocol )
        return;

    m_protocol = stack;
    connect ( m_protocol, SIGNAL ( writeDatagram ( const QNetworkDatagram& ) ),
              this, SLOT ( slotWriteDatagram ( const QNetworkDatagram& ) ) );
}

void QQtSocketUdpServer::uninstallProtocol ( QQtUdpProtocol* stack )
{
    Q_UNUSED ( stack )

    if ( !m_protocol )
        return;

    disconnect ( m_protocol, SIGNAL ( writeDatagram ( const QNetworkDatagram& ) ),
                 this, SLOT ( slotWriteDatagram ( const QNetworkDatagram& ) ) );
    m_protocol = NULL;
}

QQtUdpProtocol* QQtSocketUdpServer::installedProtocol()
{
    return m_protocol;
}

void QQtSocketUdpServer::domainHostFound()
{
    pline();
}

/**
 * @brief QQtSocketUdpServer::socketStateChanged
 * @param eSocketState
 * 状态函数
 */
void QQtSocketUdpServer::socketStateChanged ( QAbstractSocket::SocketState eSocketState )
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
        break;

    default:
        break;
    }
}

/**
 * @brief QQtSocketUdpServer::socketErrorOccured
 * @param e
 * 状态函数
 */
void QQtSocketUdpServer::socketErrorOccured ( QAbstractSocket::SocketError e )
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
 * @brief QQtSocketUdpServer::socketConnected
 * 功能接口
 */
void QQtSocketUdpServer::socketConnected()
{
    pline() << peerName() << peerAddress().toString() << peerPort();
    /*
     * 这个步骤，socket重建，资源重新开始
     */
    emit signalConnectSucc();
}

/**
 * @brief QQtSocketUdpServer::socketDisconnect
 * 功能接口
 */
void QQtSocketUdpServer::socketDisconnect()
{
    pline();
}

qint64 QQtSocketUdpServer::slotWriteDatagram ( const QNetworkDatagram& datagram )
{
    return writeDatagram ( datagram );
}

void QQtSocketUdpServer::updateProgress ( qint64 bytes )
{
    Q_UNUSED ( bytes )
    //pline() << bytes;
}

void QQtSocketUdpServer::startListening()
{
    m_thread->start();
    pline() << "QQt udp server is starting...";
    emit signalRunListening();
}

void QQtSocketUdpServer::stopListening()
{
    pline() << "QQt udp server is quiting...";
    m_thread->quit();
    m_thread->wait();
}

void QQtSocketUdpServer::slotRunListening()
{
    pline() << "QQt udp server is started";

    while ( 1 )
    {
        /*这个实现思路，其实是对QUpdSocket不太了解导致的，QUdpSocket接口没有会堵塞的*/
        QQtSleep ( 100 );

        bool hasNew = hasPendingDatagrams();

        if ( !hasNew )
            continue;

        qint64 size = pendingDatagramSize();

        QNetworkDatagram da = receiveDatagram();

        pline() << "udp sender:" << da.senderAddress() << da.senderPort();
        pline() << "udp receiver:" << da.destinationAddress() << da.destinationPort();
        pline() << "udp new msg size:" << size;

        QByteArray bytes = da.data();
        m_protocol->translator ( bytes );
    }

    pline() << "QQt udp server is quited";
}
