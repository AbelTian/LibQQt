#include "qqttcpclient.h"

#include <QTcpSocket>
#include <QHostInfo>

QQtTcpClient::QQtTcpClient ( QObject* parent ) :
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
    m_protocol = NULL;
}

QQtTcpClient::~QQtTcpClient()
{
}

void QQtTcpClient::installProtocol ( QQtProtocol* stack )
{
    if ( m_protocol )
        return;
    m_protocol = stack;

    connect ( m_protocol, SIGNAL ( write ( const QByteArray& ) ),
              this, SLOT ( slotWriteData ( const QByteArray& ) ) );
    m_protocol->attach();
}

void QQtTcpClient::uninstallProtocol ( QQtProtocol* stack )
{
    Q_UNUSED ( stack )

    if ( !m_protocol )
        return;

    disconnect ( m_protocol, SIGNAL ( write ( const QByteArray& ) ),
                 this, SLOT ( slotWriteData ( const QByteArray& ) ) );
    m_protocol->detach();
    m_protocol = NULL;
}

QQtProtocol* QQtTcpClient::installedProtocol()
{
    return m_protocol;
}

void QQtTcpClient::sendConnectToHost()
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


int QQtTcpClient::sendDisConnectFromHost()
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

void QQtTcpClient::domainHostFound()
{
    pline();
}

/**
 * @brief QQtTcpClient::socketStateChanged
 * @param eSocketState
 * 状态函数
 */
void QQtTcpClient::socketStateChanged ( QAbstractSocket::SocketState eSocketState )
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
        {
            break;
        }
        default:
            break;
    }
}

/**
 * @brief QQtTcpClient::socketErrorOccured
 * @param e
 * 状态函数
 */
void QQtTcpClient::socketErrorOccured ( QAbstractSocket::SocketError e )
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
        {
            QSettings set;
            int contype = set.value ( "Network/eConType", 0 ).toInt();
            contype++;
            contype = contype % m_serverIP.size();
            set.setValue ( "Network/eConType", contype );
            set.sync();

            eConType = contype;

            emit signalConnectFail();
        }
        break;
    }
}

/**
 * @brief QQtTcpClient::socketConnected
 * 功能接口
 */
void QQtTcpClient::socketConnected()
{
    pline() << peerName() << peerAddress().toString() << peerPort();
    /*
     * 这个步骤，socket重建，资源重新开始
     */
    emit signalConnectSucc();
    if ( !m_protocol )
    {
        pline() << "please install protocol for your tcp client.";
    }
}

/**
 * @brief QQtTcpClient::socketDisconnect
 * 功能接口
 */
void QQtTcpClient::socketDisconnect()
{
    pline();
}

void QQtTcpClient::updateProgress ( qint64 bytes )
{
    Q_UNUSED ( bytes )
    //pline() << bytes;
}

void QQtTcpClient::connectToSingelHost()
{
    //int contype = eConType % m_serverIP.size();

    QSettings set;
    int contype = set.value ( "Network/eConType", 0 ).toInt();
    contype = contype % m_serverIP.size();

    QString ip = m_serverIP.at ( contype );
    connectToHost ( QHostAddress ( ip ), m_PORT );

    pline() << peerName() << m_PORT;
}


void QQtTcpClient::readyReadData()
{
    //self, protocol, message
    QByteArray bytes;
    bytes = readAll();
    translator ( bytes );
}

void QQtTcpClient::slotWriteData ( const QByteArray& data )
{
    write ( data );
}

void QQtTcpClient::translator ( const QByteArray& bytes )
{
    // queued conn and queued package;
    // direct conn and direct package;
    /**
     * 这个地方的实现，还是有一些复杂，
     * 但是只有流式传输才需要，
     * 而且，每种通讯接口的流式传输都是一样的，
     * 过去，写在protocol里是为了增添传输工具客户端类型方便
     * 现在，这块比较稳定，所以挪动回来。
     *
     * 只能安装一个协议。
     * 如果安装多个，这个地方的static，需要给协议们分配独立的buffer。
     * 一个客户端，和服务器通信，一条流，可以由多个协议进行解析吗？
     */
    static QByteArray sqbaBlockOnNet;
    sqbaBlockOnNet += bytes;
    //qint64 aaa = bytesAvailable();
    //pline() << aaa;

    do
    {
        quint16 nBlockLen = m_protocol->splitter ( sqbaBlockOnNet );

        pmeta ( this ) << sqbaBlockOnNet.size() << "..." << nBlockLen;

        if ( sqbaBlockOnNet.length() < nBlockLen || nBlockLen < m_protocol->minlength() )
        {
            /*
             * 收到数据不足或者解析包长小于最小包长
             */
            return;
        }
        else if ( nBlockLen > m_protocol->maxlength() )
        {
            /*
             * 数据包长超过了最大长度
             */
            sqbaBlockOnNet.clear();
            pmeta ( this ) << "forbidden package" << sqbaBlockOnNet.length() << nBlockLen;
            return;
        }
        else if ( sqbaBlockOnNet.length() > nBlockLen )
        {
            /*
             * 粘包
             * 还没有处理完毕，数据已经接收到，异步信号处理出现这种异常
             * 疑问:如果异步调用这个函数绘出现什么问题？正常情况，同步获取数据，异步处理；检测异步获取并且处理会有什么状况
             */
            pmeta ( this ) << "stick package" << sqbaBlockOnNet.length() << nBlockLen;
            QByteArray netData;
            netData.resize ( nBlockLen );
            sqbaBlockOnNet >> netData;
            m_protocol->dispatcher ( netData );
            continue;
        }

        /*
         * 正常分发
         */
        m_protocol->dispatcher ( sqbaBlockOnNet );
        break;
    } while ( 1 );

    sqbaBlockOnNet.clear();
}
