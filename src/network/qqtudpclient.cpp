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
}

void QQtUdpClient::installProtocol ( QQtUdpProtocol* stack )
{
    if ( m_protocol )
        return;

    m_protocol = stack;
    connect ( m_protocol, SIGNAL ( writeDatagram ( QByteArray, QHostAddress, quint16 ) ),
              this, SLOT ( slotWriteDatagram ( QByteArray, QHostAddress, quint16 ) ) );
}

void QQtUdpClient::uninstallProtocol ( QQtUdpProtocol* stack )
{
    Q_UNUSED ( stack )

    if ( !m_protocol )
        return;

    disconnect ( m_protocol, SIGNAL ( writeDatagram ( QByteArray, QHostAddress, quint16 ) ),
                 this, SLOT ( slotWriteDatagram ( QByteArray, QHostAddress, quint16 ) ) );
    m_protocol = NULL;
}

QQtUdpProtocol* QQtUdpClient::installedProtocol()
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

qint64 QQtUdpClient::slotWriteDatagram ( const QByteArray& datagram, const QHostAddress& host, quint16 port )
{
    return writeDatagram ( datagram, host, port );
}

void QQtUdpClient::readyReadData()
{
    /*为什么用while?*/ //Qt4 没有那么高级的一次性读取的接口?有
    while ( hasPendingDatagrams() )
    {
        QByteArray bytes;
        qint64 maxlen = 0;
        QHostAddress host;
        quint16 port;

#if QT_VERSION > QT_VERSION_DATAGRAM
        /*能够一次收够一条报文？测试的能。*/
        QNetworkDatagram datagram = receiveDatagram();
        /*由于添加了兼容Qt4的代码，以上注释起来。*/

        /*数据无意义 "" -1 在此设置*/
        datagram.setDestination ( this->localAddress(), this->localPort() );
        //pline() << "udp sender:" << datagram.senderAddress() << datagram.senderPort();
        //pline() << "udp receiver:" << datagram.destinationAddress() << datagram.destinationPort();
        m_protocol->translator ( datagram );

        bytes = datagram.data();
        host = datagram.senderAddress();
        port = datagram.senderPort();
        m_protocol->translator ( bytes, host, port );
#else
        qint64 size = pendingDatagramSize();
        //pline() << "udp new msg size:" << size;
        //这里的buf用完, 已经释放。
        char* data = new char[size + 1]();
        qint64 len = readDatagram ( data, size, &host, &port );
        pline() << len;
        bytes.setRawData ( data, size );
        delete[] data;

        m_protocol->translator ( bytes, host, port );
#endif

    }
}

