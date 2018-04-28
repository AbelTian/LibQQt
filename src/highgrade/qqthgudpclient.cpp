#include "qqthgudpclient.h"

QQtHgUdpClient::QQtHgUdpClient ( QObject* parent ) : QUdpSocket ( parent )
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

    m_protocolManager = NULL;
}

void QQtHgUdpClient::installProtocolManager ( QQtHgProtocolManager* stackGroup )
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

void QQtHgUdpClient::uninstallProtocolManager ( QQtHgProtocolManager* stackGroup )
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

QQtHgProtocolManager* QQtHgUdpClient::installedProtocolManager()
{
    return m_protocolManager;
}

void QQtHgUdpClient::domainHostFound()
{
    pline();
}

/**
 * @brief QQtHgUdpClient::socketStateChanged
 * @param eSocketState
 * 状态函数
 */
void QQtHgUdpClient::socketStateChanged ( QAbstractSocket::SocketState eSocketState )
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
 * @brief QQtHgUdpClient::socketErrorOccured
 * @param e
 * 状态函数
 */
void QQtHgUdpClient::socketErrorOccured ( QAbstractSocket::SocketError e )
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
 * @brief QQtHgUdpClient::socketConnected
 * 功能接口
 */
void QQtHgUdpClient::socketConnected()
{
    pline() << peerName() << peerAddress().toString() << peerPort();
    /*
     * 这个步骤，socket重建，资源重新开始
     */
    emit signalConnectSucc();
}

/**
 * @brief QQtHgUdpClient::socketDisconnect
 * 功能接口
 */
void QQtHgUdpClient::socketDisconnect()
{
    pline();
}

void QQtHgUdpClient::updateProgress ( qint64 bytes )
{
    Q_UNUSED ( bytes )
    //pline() << bytes;
}

qint64 QQtHgUdpClient::slotWriteDatagram ( const QByteArray& datagram, const QHostAddress& host, quint16 port )
{
    return writeDatagram ( datagram, host, port );
}

void QQtHgUdpClient::readyReadData()
{
    if ( !m_protocolManager )
    {
        pline() << "please install protocol manager for your client.";
        deleteLater();
        return;
    }

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

        QListIterator<QQtHgProtocol*> itor ( m_protocolManager->installedProtocol() );
        while ( itor.hasNext() )
        {
            QQtHgProtocol* protocol = itor.next();
            protocol->translator ( this, bytes );
        }

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

