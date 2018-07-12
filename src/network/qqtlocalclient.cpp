#include "qqtlocalclient.h"

#include <QLocalSocket>
#include <QHostInfo>
#include <QUuid>

QQtLocalClient::QQtLocalClient ( QObject* parent ) :
    QLocalSocket ( parent )
{
    connect ( this, SIGNAL ( stateChanged ( QLocalSocket::LocalSocketState ) ), this,
              SLOT ( socketStateChanged ( QLocalSocket::LocalSocketState ) ) );
    // connected
    connect ( this, SIGNAL ( connected() ), this, SLOT ( socketConnected() ) );
    // disconnected
    connect ( this, SIGNAL ( disconnected() ), this, SLOT ( socketDisconnect() ) );

    // error
    connect ( this, SIGNAL ( error ( QLocalSocket::LocalSocketError ) ), this,
              SLOT ( socketErrorOccured ( QLocalSocket::LocalSocketError ) ) );

    connect ( this, SIGNAL ( readyRead() ), this, SLOT ( readyReadData() ) );

    connect ( this, SIGNAL ( bytesWritten ( qint64 ) ), this, SLOT ( updateProgress ( qint64 ) ) );

    connect ( this, SIGNAL ( bytesWritten ( qint64 ) ), this, SIGNAL ( signalUpdateProgress ( qint64 ) ) );

    /*
     * 心情很好，但是给自己带来麻烦顾虑，也不能给系统节约多少什么资源, Qt::QueuedConnection);
     */

    setReadBufferSize ( 0x800 );

    /*
     * 启动连接
     */
    eConType = 0;
    m_protocol = NULL;

    QUuid uuid = QUuid::createUuid();
    mPeerName = uuid.toString();
}

QQtLocalClient::~QQtLocalClient()
{
}

void QQtLocalClient::installProtocol ( QQtProtocol* stack )
{
    if ( m_protocol )
        return;
    m_protocol = stack;

    connect ( m_protocol, SIGNAL ( write ( const QByteArray& ) ),
              this, SLOT ( slotWriteData ( const QByteArray& ) ) );
    m_protocol->attach();
    m_protocol->initializer();
}

void QQtLocalClient::uninstallProtocol ( QQtProtocol* stack )
{
    Q_UNUSED ( stack )

    if ( !m_protocol )
        return;

    disconnect ( m_protocol, SIGNAL ( write ( const QByteArray& ) ),
                 this, SLOT ( slotWriteData ( const QByteArray& ) ) );
    m_protocol->detach();
    m_protocol = NULL;
}

QQtProtocol* QQtLocalClient::installedProtocol()
{
    return m_protocol;
}

void QQtLocalClient::sendConnectToHost()
{
    pline() << isValid() << isOpen() << state();

    if ( !isValid() && !isOpen() )
    {
        connectToSingelHost();
        return;
    }

    if ( state() == ConnectingState )
    {
        emit signalConnecting();
        return;
    }

    if ( state() == ConnectedState )
        emit signalConnectSucc();

    return;
}


int QQtLocalClient::sendDisConnectFromHost()
{
    pline() << isValid() << isOpen() << state();

    if ( isValid() || isOpen() )
    {
#if defined(__WIN__)
        ;
#else
        shutdown ( this->socketDescriptor(), SHUT_RDWR );
#endif
        disconnectFromServer();
        if ( state() != UnconnectedState )
            waitForDisconnected();
        close();
        emit signalDisConnectSucc();
    }

    return true;
}

/**
 * @brief QQtLocalClient::socketStateChanged
 * @param eSocketState
 * 状态函数
 */
void QQtLocalClient::socketStateChanged ( QLocalSocket::LocalSocketState eSocketState )
{
    pline() << eSocketState;

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
            break;
        }
        default:
            break;
    }
}

/**
 * @brief QQtLocalClient::socketErrorOccured
 * @param e
 * 状态函数
 */
void QQtLocalClient::socketErrorOccured ( LocalSocketError e )
{
    /*
     * 在错误状态下重新连接其他热点，直到确定连接类型，写入配置文件
     */
    pline() << e;

    switch ( e )
    {
        case QLocalSocket::PeerClosedError:
        case QLocalSocket::OperationError:
            break;

        case QLocalSocket::ServerNotFoundError:
        default:
        {
            QSettings set;
            int contype = set.value ( "Network/eLocalConnType", 0 ).toInt();
            contype++;
            contype = contype % m_serverIP.size();
            set.setValue ( "Network/eLocalConnType", contype );
            set.sync();

            eConType = contype;

            emit signalConnectFail();
        }
        break;
    }
}

/**
 * @brief QQtLocalClient::socketConnected
 * 功能接口
 */
void QQtLocalClient::socketConnected()
{
    pline() << peerName();
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
 * @brief QQtLocalClient::socketDisconnect
 * 功能接口
 */
void QQtLocalClient::socketDisconnect()
{
    pline();
}

void QQtLocalClient::updateProgress ( qint64 bytes )
{
    Q_UNUSED ( bytes )
    //pline() << bytes;
}

void QQtLocalClient::connectToSingelHost()
{
    //int contype = eConType % m_serverIP.size();

    QSettings set;
    int contype = set.value ( "Network/eLocalConnType", 0 ).toInt();
    contype = contype % m_serverIP.size();

    QString ip = m_serverIP.at ( contype );
    connectToServer ( ip );
    pline() << peerName() << serverName() << fullServerName();
}


void QQtLocalClient::readyReadData()
{
    //self, protocol, message
    QByteArray bytes;
    bytes = readAll();
    translator ( bytes );
}

void QQtLocalClient::slotWriteData ( const QByteArray& data )
{
    write ( data );
}

void QQtLocalClient::translator ( const QByteArray& bytes )
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
