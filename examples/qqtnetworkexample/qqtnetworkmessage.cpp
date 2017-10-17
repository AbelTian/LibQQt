#include "qqtnetworkmessage.h"
#include "qqtcore.h"
#include "qqtnetwork.h"

QQTNetworkMessage::QQTNetworkMessage(QObject *parent) : QQTMessage(parent)
{
    m_Head = _TCPCMD_TAGHEAD;
    m_Size = m_Cmd = m_Uid = m_Sum = 0;
    m_Data.clear();;
    m_Tail = _TCPCMD_TAGTAIL;
}

const quint16 &QQTNetworkMessage::head() const { return m_Head; }

void QQTNetworkMessage::setHead(quint16 head) { m_Head = head; }

const quint16 &QQTNetworkMessage::size() const { return m_Size; }

void QQTNetworkMessage::setSize(quint16 size) { m_Size = size; }

const quint16 &QQTNetworkMessage::cmd() const { return m_Cmd; }

void QQTNetworkMessage::setCmd(quint16 cmd) { m_Cmd = cmd; }

const quint32 &QQTNetworkMessage::uid() const { return m_Uid; }

void QQTNetworkMessage::setUid(quint32 uid) { m_Uid = uid; }

const QByteArray &QQTNetworkMessage::data() const { return m_Data; }

void QQTNetworkMessage::setData(QByteArray &data) { m_Data = data; }

const quint16 &QQTNetworkMessage::sum() const { return m_Sum; }

void QQTNetworkMessage::setSum(quint16 sum) { m_Sum = sum; }

const quint32 &QQTNetworkMessage::tail() const { return m_Tail; }

void QQTNetworkMessage::setTail(quint32 tail) { m_Tail = tail; }

void QQTNetworkMessage::translate()
{
    m_Size = m_Data.length() + 0x10;
    QByteArray qbaVerify;
    qbaVerify << m_Size << m_Cmd << m_Uid << m_Data;
    m_Sum = 0;
    /*
     * 校验码等错误 会导致服务器不回复消息
     * 如果不添加quint8 0x0112+0x0088=0x009a 单字节到二字节进位的位置看不懂
     * 带进位的8位偶校验。
     */
    for(int i = 0; i < qbaVerify.length(); i++)
        m_Sum += quint8(qbaVerify.at(i));
    //real verify
    //m_Sum = qChecksum(qbaVerify.data(), qbaVerify.length());
}

void QQTNetworkMessage::parser(const QByteArray &block)
{
    QByteArray l = block;
    quint16 b0 = 0, b1 = 0, b2 = 0, b5 = 0;
    quint32 b3 = 0, b6 = 0;
    QByteArray b4;
    l >> b0 >> b1 >> b2 >> b3;
    b4.resize(b1-0x10);
    l >> b4 >> b5 >> b6;
    setHead(b0);
    setSize(b1);
    setCmd(b2);
    setUid(b3);
    setData(b4);
    setSum(b5);
    setTail(b6);
}

void QQTNetworkMessage::packer(QByteArray &stream)
{
    stream << head();
    stream << size();
    stream << cmd();
    stream << uid();
    stream << data();
    stream << sum();
    stream << tail();
}

QDebug operator<<(QDebug dbg, const QQTNetworkMessage &c)
{
    dbg.nospace() << "{" << hex << c.head() << "|" <<
                     hex << c.size() << "=" << dec << c.size() << "|" <<
                     hex << c.cmd() << "|" <<
                     hex << c.uid() << "|" <<
                     c.data().data() << "@" << dec << c.data().size() << "|" <<
                     hex << c.sum() << "|" <<
                     hex << c.tail() << "}";
    return dbg.space();
}

