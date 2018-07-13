#include <qqtnamedpipe.h>

QQtNamedPipeClientMessage::QQtNamedPipeClientMessage ( QObject* parent )
{
    mSize = 0x03;//报文定长
}

QQtNamedPipeClientMessage::~QQtNamedPipeClientMessage()
{

}

quint8& QQtNamedPipeClientMessage::size() { return mSize; }

const quint8& QQtNamedPipeClientMessage::size() const { return mSize; }

quint8& QQtNamedPipeClientMessage::cmd() { return mCmd; }

const quint8& QQtNamedPipeClientMessage::cmd() const { return mCmd; }

quint8& QQtNamedPipeClientMessage::data() { return mData; }

const quint8& QQtNamedPipeClientMessage::data() const { return mData; }

void QQtNamedPipeClientMessage::parser ( const QByteArray& l )
{
    QByteArray _l = l;
    _l >> mSize;
    _l >> mCmd;
    _l >> mData;
}

void QQtNamedPipeClientMessage::packer ( QByteArray& l ) const
{
    l << mSize;
    l << mCmd;
    l << mData;
}

QDebug& operator << ( QDebug& dbg, const QQtNamedPipeClientMessage& msg )
{
    //这里打印一下，报文里面到底有什么信息，
    //一般到这里的，都是被解析好的message。

    dbg.nospace() << "{" << hex << msg.size() << "}";
    return dbg.space();
}

QQtNamedPipeClientProtocol::QQtNamedPipeClientProtocol ( QObject* parent )
{

}

QQtNamedPipeClientProtocol::~QQtNamedPipeClientProtocol()
{

}

void QQtNamedPipeClientProtocol::recvCommand0x0a ( const QQtNamedPipeClientMessage& msg )
{
    //what do you want to do?
    pline() << "client receive accept:" << msg.cmd();
}

void QQtNamedPipeClientProtocol::recvCommand0x0b ( const QQtNamedPipeClientMessage& msg )
{
    //what do you want to do?
    pline() << "client receive reject:" << msg.cmd();
}

void QQtNamedPipeClientProtocol::sendCommand0x0a()
{
    //what do you want to do?
    QQtNamedPipeClientMessage msg;
    msg.cmd() = 0x0a;
    QByteArray l;
    msg.packer ( l );
    write ( l );
}

void QQtNamedPipeClientProtocol::sendCommand0x0b()
{
    //what do you want to do?
    QQtNamedPipeClientMessage msg;
    msg.cmd() = 0x0b;
    QByteArray l;
    msg.packer ( l );
    write ( l );
}

quint16 QQtNamedPipeClientProtocol::minlength()
{
    return 0x03;
}

quint16 QQtNamedPipeClientProtocol::maxlength()
{
    return 0x07FF;
}

quint16 QQtNamedPipeClientProtocol::splitter ( const QByteArray& l ) //stream
{
    QByteArray s0 = l.left ( 1 );
    quint8 size = 0;
    s0 >> size;
    return size;
}

bool QQtNamedPipeClientProtocol::dispatcher ( const QByteArray& m ) //message
{
    bool ret = true;

    QQtNamedPipeClientMessage qMsg;
    qMsg.parser ( m );
    pline() << qMsg;

    //0x0a.
    switch ( qMsg.cmd() )
    {
        case 0x0a://protocol command 1
            recvCommand0x0a ( qMsg );
            break;

        case 0x0b://protocol command 2
            recvCommand0x0b ( qMsg );
            break;

        default:
            ret = false;
            pline() << "receive unknown command:" << hex << qMsg.cmd();
            break;
    }

    return ret;
}


QQtLocalClient* QQtNamedPipeClientInstance ( QQtNamedPipeClientProtocol*& protocol, QObject* parent )
{
    static QQtNamedPipeClientProtocol* p0 = NULL;
    if ( !p0 )
    {
        p0 = new QQtNamedPipeClientProtocol ( parent );
    }
    protocol = p0;

    static QQtLocalClient* s0 = NULL;
    if ( !s0 )
    {
        s0 = new QQtLocalClient ( parent );
        s0->installProtocol ( p0 );
        s0->setServerIPAddress ( "QQtSingleTon" );
        //现在不连接。
        //s0->sendConnectToHost();
    }

    return s0;
}


QQtNamedPipeServerMessage::QQtNamedPipeServerMessage ( QObject* parent )
{
    mSize = 0x03;//报文定长
}

QQtNamedPipeServerMessage::~QQtNamedPipeServerMessage()
{

}

quint8& QQtNamedPipeServerMessage::size() { return mSize; }

const quint8& QQtNamedPipeServerMessage::size() const { return mSize; }

quint8& QQtNamedPipeServerMessage::cmd() { return mCmd; }

const quint8& QQtNamedPipeServerMessage::cmd() const { return mCmd; }

quint8& QQtNamedPipeServerMessage::data() { return mData; }

const quint8& QQtNamedPipeServerMessage::data() const { return mData; }

void QQtNamedPipeServerMessage::parser ( const QByteArray& l )
{
    QByteArray _l = l;
    _l >> mSize;
    _l >> mCmd;
    _l >> mData;
}

void QQtNamedPipeServerMessage::packer ( QByteArray& l ) const
{
    l << mSize;
    l << mCmd;
    l << mData;
}


QDebug& operator << ( QDebug& dbg, const QQtNamedPipeServerMessage& msg )
{
    //这里打印一下，报文里面到底有什么信息，
    //一般到这里的，都是被解析好的message。

    dbg.nospace() << "{" << hex << msg.size() << "}";
    return dbg.space();
}


QQtNamedPipeServerProtocol::QQtNamedPipeServerProtocol ( QObject* parent )
{

}

QQtNamedPipeServerProtocol::~QQtNamedPipeServerProtocol()
{

}

void QQtNamedPipeServerProtocol::recvCommand0x0a ( const QQtNamedPipeServerMessage& msg )
{
    //what do you want to do?
    sendCommand0x0a();
}

void QQtNamedPipeServerProtocol::recvCommand0x0b ( const QQtNamedPipeServerMessage& msg )
{
    //what do you want to do?
    sendCommand0x0b();
}

void QQtNamedPipeServerProtocol::sendCommand0x0a()
{
    //what do you want to do?
    QQtNamedPipeServerMessage msg;
    msg.cmd() = 0x0a;
    QByteArray l;
    msg.packer ( l );
    write ( l );
    pline() << "server send accept:" << msg.cmd();
}

void QQtNamedPipeServerProtocol::sendCommand0x0b()
{
    //what do you want to do?
    QQtNamedPipeServerMessage msg;
    msg.cmd() = 0x0b;
    QByteArray l;
    msg.packer ( l );
    write ( l );
    pline() << "server send reject:" << msg.cmd();
}

quint16 QQtNamedPipeServerProtocol::minlength()
{
    return 0x03;
}

quint16 QQtNamedPipeServerProtocol::maxlength()
{
    return 0x07FF;
}

quint16 QQtNamedPipeServerProtocol::splitter ( const QByteArray& l ) //stream
{
    QByteArray s0 = l.left ( 1 );
    quint8 size = 0;
    s0 >> size;
    return size;
}

bool QQtNamedPipeServerProtocol::dispatcher ( const QByteArray& m ) //message
{
    bool ret = true;

    QQtNamedPipeServerMessage qMsg;
    qMsg.parser ( m );
    pline() << qMsg;

    switch ( qMsg.cmd() )
    {
        case 0x0a://protocol command 1
            recvCommand0x0a ( qMsg );
            break;

        case 0x0b://protocol command 2
            recvCommand0x0b ( qMsg );
            break;

        default:
            ret = false;
            pline() << "receive unknown command:" << hex << qMsg.cmd();
            break;
    }

    return ret;
}

QQtLocalServer* QQtNamedPipeServerInstance ( QQtProtocolManager*& protocolManager, QObject* parent )
{
    static QQtProtocolManager* pm0 = 0;
    if ( !pm0 )
    {
        pm0 = new QQtProtocolManager ( parent );
        pm0->registerProtocol<QQtNamedPipeServerProtocol>();
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

