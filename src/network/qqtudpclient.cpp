#include "qqtudpclient.h"

QQtUdpClient::QQtUdpClient ( QObject* parent ) : QUdpSocket ( parent )
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

    m_protocol = NULL;
    mIP = "";
    mPort = 0;
}

void QQtUdpClient::installProtocol ( QQtProtocol* stack )
{
    if ( m_protocol )
        return;
    m_protocol = stack;

    connect ( m_protocol, SIGNAL ( write ( const QByteArray& ) ),
              this, SLOT ( slotWriteData ( const QByteArray& ) ) );
    m_protocol->attach();
    m_protocol->initializer();
}

void QQtUdpClient::uninstallProtocol ( QQtProtocol* stack )
{
    Q_UNUSED ( stack )

    if ( !m_protocol )
        return;

    disconnect ( m_protocol, SIGNAL ( write ( const QByteArray& ) ),
                 this, SLOT ( slotWriteData ( const QByteArray& ) ) );
    m_protocol->detach();
    m_protocol = NULL;
}

QQtProtocol* QQtUdpClient::installedProtocol()
{
    return m_protocol;
}

void QQtUdpClient::domainHostFound()
{
    pline();
}

/**
 * @brief QQtUdpClient::socketStateChanged
 * @param eSocketState
 * 状态函数
 */
void QQtUdpClient::socketStateChanged ( QAbstractSocket::SocketState eSocketState )
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
 * @brief QQtUdpClient::socketErrorOccured
 * @param e
 * 状态函数
 */
void QQtUdpClient::socketErrorOccured ( QAbstractSocket::SocketError e )
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
 * @brief QQtUdpClient::socketConnected
 * 功能接口
 */
void QQtUdpClient::socketConnected()
{
    pline() << peerName() << peerAddress().toString() << peerPort();
    /*
     * 这个步骤，socket重建，资源重新开始
     */
    emit signalConnectSucc();
    if ( !m_protocol )
    {
        pline() << "please install protocol for your udp client.";
    }
}

/**
 * @brief QQtUdpClient::socketDisconnect
 * 功能接口
 */
void QQtUdpClient::socketDisconnect()
{
    pline();
}

void QQtUdpClient::updateProgress ( qint64 bytes )
{
    Q_UNUSED ( bytes )
    //pline() << bytes;
}

void QQtUdpClient::translator ( const QByteArray& bytes )
{
    //pline() << m_protocol;
    m_protocol->dispatcher ( bytes );
}

void QQtUdpClient::recvDatagram ( QByteArray& bytes, QHostAddress& address, quint16& port )
{
#if QT_VERSION > QT_VERSION_DATAGRAM
    /*能够一次收够一条报文？测试的能。*/
    QNetworkDatagram datagram = receiveDatagram();
    /*由于添加了兼容Qt4的代码，以上注释起来。*/
    /*数据无意义 "" -1 在此设置*/
    datagram.setDestination ( this->localAddress(), this->localPort() );
    //pline() << "udp sender:" << datagram.senderAddress() << datagram.senderPort();
    //pline() << "udp receiver:" << datagram.destinationAddress() << datagram.destinationPort();
    bytes = datagram.data();
    address = datagram.senderAddress();
    port = datagram.senderPort();
#else
    qint64 size = pendingDatagramSize();
    //pline() << "udp new msg size:" << size;
    //这里的buf用完, 已经释放。
    char* data = new char[size + 1]();
    qint64 len = readDatagram ( data, size, &address, &port );
    //pline() << len;
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    bytes.resize ( len );
    memcpy ( bytes.data(), data, len );
#elif QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    bytes.resize ( len );
    memcpy ( bytes.data(), data, len );
#else
    //low version
    //Qt5.6 以上 MSVC Linux64 全部都出错，设置进去以后拿到的根本就是乱码。此处决定仅仅Qt4使用。
    bytes.setRawData ( data, size );
#endif
    delete[] data;
#endif
}

void QQtUdpClient::readyReadData()
{
    /*为什么用while?*/ //Qt4 没有那么高级的一次性读取的接口?有
    while ( hasPendingDatagrams() )
    {
        QByteArray bytes;
        QHostAddress address;
        quint16 port;
        recvDatagram ( bytes, address, port );
        translator ( bytes );
    }
}

void QQtUdpClient::slotWriteData ( const QByteArray& bytes )
{
#if QT_VERSION > QT_VERSION_DATAGRAM
    QNetworkDatagram datagram;
    datagram.setData ( bytes );
    datagram.setDestination ( QHostAddress ( mIP ), mPort );
    datagram.setSender ( localAddress(), localPort() );
    writeDatagram ( datagram );
#else
    writeDatagram ( bytes, QHostAddress ( mIP ), mPort );
#endif
}

