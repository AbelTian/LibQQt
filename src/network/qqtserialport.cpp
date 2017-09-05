#include "qqtserialport.h"

QQTSerialPort::QQTSerialPort(QObject *parent) :
    QSerialPort(parent)
{
    //connect(this, SIGNAL(bytesWritten(qint64)), this, SLOT(updateProgress(qint64)) );
    connect(this, SIGNAL(readyRead()), this, SLOT(readyReadData()) );
    //connect(this, SIGNAL(aboutToClose()), this, SLOT(aboutToClose()));
    //connect(this, SIGNAL(readChannelFinished()), this, SLOT(readChannelFinished()));
}

QQTSerialPort::~QQTSerialPort()
{
    close();
}

void QQTSerialPort::installProtocol(QQTProtocol *stack)
{
    if(m_protocol)
        return;

    m_protocol = stack;
    connect(m_protocol, SIGNAL(write(const QByteArray&)), this, SLOT(write(const QByteArray&)));
}

void QQTSerialPort::uninstallProtocol(QQTProtocol *stack)
{
    if(!m_protocol)
        return;

    disconnect(m_protocol, SIGNAL(write(const QByteArray&)), this, SLOT(write(const QByteArray&)));
    m_protocol = NULL;
}

QQTProtocol *QQTSerialPort::installedProtocol()
{
    return m_protocol;
}

void QQTSerialPort::readyReadData()
{
    // queued conn and queued package;
    // direct conn and direct package;

    static QByteArray m_blockOnNet;
    m_blockOnNet += readAll();
    //qint64 aaa = bytesAvailable();
    //pline() << aaa;

    do{
        quint16 nBlockLen = m_protocol->splitter(m_blockOnNet);

        pline() << m_blockOnNet.size() << "..." << nBlockLen;

        if(m_blockOnNet.length() < nBlockLen || nBlockLen < m_protocol->minlength())
        {
            /*
             * 收到数据不足或者解析包长小于最小包长
             */
            return;
        }
        else if(nBlockLen > m_protocol->maxlength())
        {
            /*
             * 数据包长超过了最大长度
             */
            m_blockOnNet.clear();
            pline() << "forbidden package" << m_blockOnNet.length() << nBlockLen;
            return;
        }
        else if(m_blockOnNet.length() > nBlockLen)
        {
            /*
             * 粘包
             * 还没有处理完毕，数据已经接收到，异步信号处理出现这种异常
             * 疑问:如果异步调用这个函数绘出现什么问题？正常情况，同步获取数据，异步处理；检测异步获取并且处理会有什么状况
             */
            pline() << "stick package" << m_blockOnNet.length() << nBlockLen;
            QByteArray netData;
            netData.resize(nBlockLen);
            m_blockOnNet >> netData;
            m_protocol->dispatcher(netData);
            continue;
        }
        /*
         * 正常分发
         */
        m_protocol->dispatcher(m_blockOnNet);
        break;
    }while(1);

    m_blockOnNet.clear();
}
