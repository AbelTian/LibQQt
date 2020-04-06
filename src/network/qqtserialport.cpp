#include "qqtserialport.h"
#include "qqtcore.h"

QQtSerialPort::QQtSerialPort ( QObject* parent ) : QSerialPort ( parent )
{
    //connect(this, SIGNAL(bytesWritten(qint64)), this, SLOT(updateProgress(qint64)) );
    connect ( this, SIGNAL ( readyRead() ), this, SLOT ( readyReadData() ) );
    //connect(this, SIGNAL(aboutToClose()), this, SLOT(aboutToClose()));
    //connect(this, SIGNAL(readChannelFinished()), this, SLOT(readChannelFinished()));
    m_protocol = NULL;
}

QQtSerialPort::~QQtSerialPort()
{
    if ( isOpen() )
        close();
}

void QQtSerialPort::installProtocol ( QQtProtocol* stack )
{
    if ( m_protocol )
        return;
    m_protocol = stack;

    connect ( m_protocol, SIGNAL ( write ( const QByteArray& ) ),
              this, SLOT ( slotWriteData ( const QByteArray& ) ) );
    m_protocol->setClientHandler ( this );
    m_protocol->attach();
    m_protocol->initializer();
}

void QQtSerialPort::uninstallProtocol ( QQtProtocol* stack )
{
    Q_UNUSED ( stack )

    if ( !m_protocol )
        return;

    disconnect ( m_protocol, SIGNAL ( write ( const QByteArray& ) ),
                 this, SLOT ( slotWriteData ( const QByteArray& ) ) );
    m_protocol->detach();
    m_protocol = NULL;
}

QQtProtocol* QQtSerialPort::installedProtocol()
{
    return m_protocol;
}

void QQtSerialPort::readyReadData()
{
    QByteArray bytes;
    bytes = readAll();
    translator ( bytes );
}

void QQtSerialPort::slotWriteData ( const QByteArray& bytes )
{
    write ( bytes );
}

void QQtSerialPort::translator ( const QByteArray& bytes )
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
