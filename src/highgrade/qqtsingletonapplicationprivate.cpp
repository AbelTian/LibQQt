#include <qqtsingletonapplicationprivate.h>

QQtSingleTonLocalClientMessage::QQtSingleTonLocalClientMessage ( QObject* parent )
{
    mSize = 0x03;//报文定长
}

QQtSingleTonLocalClientMessage::~QQtSingleTonLocalClientMessage()
{

}

quint8& QQtSingleTonLocalClientMessage::size() { return mSize; }

const quint8& QQtSingleTonLocalClientMessage::size() const { return mSize; }

quint8& QQtSingleTonLocalClientMessage::cmd() { return mCmd; }

const quint8& QQtSingleTonLocalClientMessage::cmd() const { return mCmd; }

quint8& QQtSingleTonLocalClientMessage::data() { return mData; }

const quint8& QQtSingleTonLocalClientMessage::data() const { return mData; }

void QQtSingleTonLocalClientMessage::parser ( const QByteArray& l )
{
    QByteArray _l = l;
    _l >> mSize;
    _l >> mCmd;
    _l >> mData;
}

void QQtSingleTonLocalClientMessage::packer ( QByteArray& l ) const
{
    l << mSize;
    l << mCmd;
    l << mData;
}

QDebug& operator << ( QDebug& dbg, const QQtSingleTonLocalClientMessage& msg )
{
    //这里打印一下，报文里面到底有什么信息，
    //一般到这里的，都是被解析好的message。

    dbg.nospace() << "{" << hex << msg.size() << "}";
    return dbg.space();
}

QQtSingleTonLocalClientProtocol::QQtSingleTonLocalClientProtocol ( QObject* parent )
{

}

QQtSingleTonLocalClientProtocol::~QQtSingleTonLocalClientProtocol()
{

}

void QQtSingleTonLocalClientProtocol::recvCommand1 ( const QQtSingleTonLocalClientMessage& msg )
{
    //what do you want to do?
    pline() << "client receive accept:" << msg.cmd();
    emit signalAccept();
}

void QQtSingleTonLocalClientProtocol::recvCommand2 ( const QQtSingleTonLocalClientMessage& msg )
{
    //what do you want to do?
    pline() << "client receive reject:" << msg.cmd();
    emit signalReject();
}

void QQtSingleTonLocalClientProtocol::sendCommand1()
{
    //what do you want to do?
    QQtSingleTonLocalClientMessage msg;
    msg.cmd() = 0x0a;
    QByteArray l;
    msg.packer ( l );
    write ( l );
}

void QQtSingleTonLocalClientProtocol::sendCommand2()
{
    //what do you want to do?
    QQtSingleTonLocalClientMessage msg;
    msg.cmd() = 0x0b;
    QByteArray l;
    msg.packer ( l );
    write ( l );
}

quint16 QQtSingleTonLocalClientProtocol::minlength()
{
    return 0x03;
}

quint16 QQtSingleTonLocalClientProtocol::maxlength()
{
    return 0x07FF;
}

quint16 QQtSingleTonLocalClientProtocol::splitter ( const QByteArray& l ) //stream
{
    QByteArray s0 = l.left ( 1 );
    quint8 size = 0;
    s0 >> size;
    return size;
}

bool QQtSingleTonLocalClientProtocol::dispatcher ( const QByteArray& m ) //message
{
    bool ret = true;

    QQtSingleTonLocalClientMessage qMsg;
    qMsg.parser ( m );
    pline() << qMsg;

    //0x0a.
    switch ( qMsg.cmd() )
    {
        case 0x0a://protocol command 1
            recvCommand1 ( qMsg );
            break;

        case 0x0b://protocol command 2
            recvCommand2 ( qMsg );
            break;

        default:
            ret = false;
            pline() << "receive unknown command:" << hex << qMsg.cmd();
            break;
    }

    return ret;
}


QQtLocalClient* QQtSingleTonLocalClientInstance ( QQtSingleTonLocalClientProtocol*& protocol, QObject* parent )
{
    static QQtSingleTonLocalClientProtocol* p0 = NULL;
    if ( !p0 )
    {
        p0 = new QQtSingleTonLocalClientProtocol ( parent );
    }
    protocol = p0;

    static QQtLocalClient* s0 = NULL;
    if ( !s0 )
    {
        s0 = new QQtLocalClient ( parent );
        s0->installProtocol ( p0 );
        //现在不设置。
        //s0->setServerIPAddress ( qqtApp->applicationName() );
        //现在不连接。
        //s0->sendConnectToHost();
    }

    return s0;
}


QQtSingleTonLocalServerMessage::QQtSingleTonLocalServerMessage ( QObject* parent )
{
    mSize = 0x03;//报文定长
}

QQtSingleTonLocalServerMessage::~QQtSingleTonLocalServerMessage()
{

}

quint8& QQtSingleTonLocalServerMessage::size() { return mSize; }

const quint8& QQtSingleTonLocalServerMessage::size() const { return mSize; }

quint8& QQtSingleTonLocalServerMessage::cmd() { return mCmd; }

const quint8& QQtSingleTonLocalServerMessage::cmd() const { return mCmd; }

quint8& QQtSingleTonLocalServerMessage::data() { return mData; }

const quint8& QQtSingleTonLocalServerMessage::data() const { return mData; }

void QQtSingleTonLocalServerMessage::parser ( const QByteArray& l )
{
    QByteArray _l = l;
    _l >> mSize;
    _l >> mCmd;
    _l >> mData;
}

void QQtSingleTonLocalServerMessage::packer ( QByteArray& l ) const
{
    l << mSize;
    l << mCmd;
    l << mData;
}


QDebug& operator << ( QDebug& dbg, const QQtSingleTonLocalServerMessage& msg )
{
    //这里打印一下，报文里面到底有什么信息，
    //一般到这里的，都是被解析好的message。

    dbg.nospace() << "{" << hex << msg.size() << "}";
    return dbg.space();
}


QQtSingleTonLocalServerProtocol::QQtSingleTonLocalServerProtocol ( QObject* parent )
{

}

QQtSingleTonLocalServerProtocol::~QQtSingleTonLocalServerProtocol()
{

}

void QQtSingleTonLocalServerProtocol::recvCommand1 ( const QQtSingleTonLocalServerMessage& msg )
{
    //what do you want to do?
    sendCommand1();
}

void QQtSingleTonLocalServerProtocol::recvCommand2 ( const QQtSingleTonLocalServerMessage& msg )
{
    //what do you want to do?
    sendCommand2();
}

void QQtSingleTonLocalServerProtocol::sendCommand1()
{
    //what do you want to do?
    QQtSingleTonLocalServerMessage msg;
    msg.cmd() = 0x0a;
    QByteArray l;
    msg.packer ( l );
    write ( l );
    pline() << "server send accept:" << msg.cmd();
}

void QQtSingleTonLocalServerProtocol::sendCommand2()
{
    //what do you want to do?
    QQtSingleTonLocalServerMessage msg;
    msg.cmd() = 0x0b;
    QByteArray l;
    msg.packer ( l );
    write ( l );
    pline() << "server send reject:" << msg.cmd();
}

quint16 QQtSingleTonLocalServerProtocol::minlength()
{
    return 0x03;
}

quint16 QQtSingleTonLocalServerProtocol::maxlength()
{
    return 0x07FF;
}

quint16 QQtSingleTonLocalServerProtocol::splitter ( const QByteArray& l ) //stream
{
    QByteArray s0 = l.left ( 1 );
    quint8 size = 0;
    s0 >> size;
    return size;
}

bool QQtSingleTonLocalServerProtocol::dispatcher ( const QByteArray& m ) //message
{
    bool ret = true;

    QQtSingleTonLocalServerMessage qMsg;
    qMsg.parser ( m );
    pline() << qMsg;

    switch ( qMsg.cmd() )
    {
        case 0x0a://protocol command 1
            recvCommand1 ( qMsg );
            break;

        case 0x0b://protocol command 2
            recvCommand2 ( qMsg );
            break;

        default:
            ret = false;
            pline() << "receive unknown command:" << hex << qMsg.cmd();
            break;
    }

    return ret;
}

QQtLocalServer* QQtSingleTonLocalServerInstance ( QQtProtocolManager*& protocolManager, QObject* parent )
{
    static QQtProtocolManager* pm0 = 0;
    if ( !pm0 )
    {
        pm0 = new QQtProtocolManager ( parent );
        pm0->registerProtocol<QQtSingleTonLocalServerProtocol>();
    }
    protocolManager = pm0;

    static QQtLocalServer* s0 = NULL;
    if ( !s0 )
    {
        s0 = new QQtLocalServer ( parent );
        s0->installProtocolManager ( pm0 ) ;
        //现在不监听。
        //s0->listen("QQtSingleTon");
    }

    return s0;
}
