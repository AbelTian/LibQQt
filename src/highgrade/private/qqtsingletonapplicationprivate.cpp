#include <qqtsingletonapplicationprivate.h>

QQtSingleTonNamedPipeClientMessage::QQtSingleTonNamedPipeClientMessage ( QObject* parent )
{
    mSize = 0x03;//报文定长
}

QQtSingleTonNamedPipeClientMessage::~QQtSingleTonNamedPipeClientMessage()
{

}

quint8& QQtSingleTonNamedPipeClientMessage::size() { return mSize; }

const quint8& QQtSingleTonNamedPipeClientMessage::size() const { return mSize; }

quint8& QQtSingleTonNamedPipeClientMessage::cmd() { return mCmd; }

const quint8& QQtSingleTonNamedPipeClientMessage::cmd() const { return mCmd; }

quint8& QQtSingleTonNamedPipeClientMessage::data() { return mData; }

const quint8& QQtSingleTonNamedPipeClientMessage::data() const { return mData; }

void QQtSingleTonNamedPipeClientMessage::parser ( const QByteArray& l )
{
    QByteArray _l = l;
    _l >> mSize;
    _l >> mCmd;
    _l >> mData;
}

void QQtSingleTonNamedPipeClientMessage::packer ( QByteArray& l ) const
{
    l << mSize;
    l << mCmd;
    l << mData;
}

QDebug& operator << ( QDebug& dbg, const QQtSingleTonNamedPipeClientMessage& msg )
{
    //这里打印一下，报文里面到底有什么信息，
    //一般到这里的，都是被解析好的message。

    dbg.nospace() << "{" << hex << msg.size() << "}";
    return dbg.space();
}

QQtSingleTonNamedPipeClientProtocol::QQtSingleTonNamedPipeClientProtocol ( QObject* parent )
{

}

QQtSingleTonNamedPipeClientProtocol::~QQtSingleTonNamedPipeClientProtocol()
{

}

void QQtSingleTonNamedPipeClientProtocol::recvCommand1 ( const QQtSingleTonNamedPipeClientMessage& msg )
{
    //what do you want to do?
    pline() << "client receive accept:" << msg.cmd();
    emit signalAccept();
}

void QQtSingleTonNamedPipeClientProtocol::recvCommand2 ( const QQtSingleTonNamedPipeClientMessage& msg )
{
    //what do you want to do?
    pline() << "client receive reject:" << msg.cmd();
    emit signalReject();
}

void QQtSingleTonNamedPipeClientProtocol::sendCommand1()
{
    //what do you want to do?
    QQtSingleTonNamedPipeClientMessage msg;
    msg.cmd() = 0x0a;
    QByteArray l;
    msg.packer ( l );
    write ( l );
}

void QQtSingleTonNamedPipeClientProtocol::sendCommand2()
{
    //what do you want to do?
    QQtSingleTonNamedPipeClientMessage msg;
    msg.cmd() = 0x0b;
    QByteArray l;
    msg.packer ( l );
    write ( l );
}

quint16 QQtSingleTonNamedPipeClientProtocol::minlength()
{
    return 0x03;
}

quint16 QQtSingleTonNamedPipeClientProtocol::maxlength()
{
    return 0x07FF;
}

quint16 QQtSingleTonNamedPipeClientProtocol::splitter ( const QByteArray& l ) //stream
{
    QByteArray s0 = l.left ( 1 );
    quint8 size = 0;
    s0 >> size;
    return size;
}

bool QQtSingleTonNamedPipeClientProtocol::dispatcher ( const QByteArray& m ) //message
{
    bool ret = true;

    QQtSingleTonNamedPipeClientMessage qMsg;
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


QQtNamedPipeClient* QQtSingleTonNamedPipeClientInstance ( QQtSingleTonNamedPipeClientProtocol*& protocol, QObject* parent )
{
    static QQtSingleTonNamedPipeClientProtocol* p0 = NULL;
    if ( !p0 )
    {
        p0 = new QQtSingleTonNamedPipeClientProtocol ( parent );
    }
    protocol = p0;

    static QQtNamedPipeClient* s0 = NULL;
    if ( !s0 )
    {
        s0 = new QQtNamedPipeClient ( parent );
        s0->installProtocol ( p0 );
        //现在不设置。
        //s0->setServerIPAddress ( qqtApp->applicationName() );
        //现在不连接。
        //s0->sendConnectToHost();
    }

    return s0;
}


QQtSingleTonNamedPipeServerMessage::QQtSingleTonNamedPipeServerMessage ( QObject* parent )
{
    mSize = 0x03;//报文定长
}

QQtSingleTonNamedPipeServerMessage::~QQtSingleTonNamedPipeServerMessage()
{

}

quint8& QQtSingleTonNamedPipeServerMessage::size() { return mSize; }

const quint8& QQtSingleTonNamedPipeServerMessage::size() const { return mSize; }

quint8& QQtSingleTonNamedPipeServerMessage::cmd() { return mCmd; }

const quint8& QQtSingleTonNamedPipeServerMessage::cmd() const { return mCmd; }

quint8& QQtSingleTonNamedPipeServerMessage::data() { return mData; }

const quint8& QQtSingleTonNamedPipeServerMessage::data() const { return mData; }

void QQtSingleTonNamedPipeServerMessage::parser ( const QByteArray& l )
{
    QByteArray _l = l;
    _l >> mSize;
    _l >> mCmd;
    _l >> mData;
}

void QQtSingleTonNamedPipeServerMessage::packer ( QByteArray& l ) const
{
    l << mSize;
    l << mCmd;
    l << mData;
}


QDebug& operator << ( QDebug& dbg, const QQtSingleTonNamedPipeServerMessage& msg )
{
    //这里打印一下，报文里面到底有什么信息，
    //一般到这里的，都是被解析好的message。

    dbg.nospace() << "{" << hex << msg.size() << "}";
    return dbg.space();
}


QQtSingleTonNamedPipeServerProtocol::QQtSingleTonNamedPipeServerProtocol ( QObject* parent )
{

}

QQtSingleTonNamedPipeServerProtocol::~QQtSingleTonNamedPipeServerProtocol()
{

}

void QQtSingleTonNamedPipeServerProtocol::recvCommand1 ( const QQtSingleTonNamedPipeServerMessage& msg )
{
    //what do you want to do?
    sendCommand1();
}

void QQtSingleTonNamedPipeServerProtocol::recvCommand2 ( const QQtSingleTonNamedPipeServerMessage& msg )
{
    //what do you want to do?
    sendCommand2();
}

void QQtSingleTonNamedPipeServerProtocol::sendCommand1()
{
    //what do you want to do?
    QQtSingleTonNamedPipeServerMessage msg;
    msg.cmd() = 0x0a;
    QByteArray l;
    msg.packer ( l );
    write ( l );
    pline() << "server send accept:" << msg.cmd();
}

void QQtSingleTonNamedPipeServerProtocol::sendCommand2()
{
    //what do you want to do?
    QQtSingleTonNamedPipeServerMessage msg;
    msg.cmd() = 0x0b;
    QByteArray l;
    msg.packer ( l );
    write ( l );
    pline() << "server send reject:" << msg.cmd();
}

quint16 QQtSingleTonNamedPipeServerProtocol::minlength()
{
    return 0x03;
}

quint16 QQtSingleTonNamedPipeServerProtocol::maxlength()
{
    return 0x07FF;
}

quint16 QQtSingleTonNamedPipeServerProtocol::splitter ( const QByteArray& l ) //stream
{
    QByteArray s0 = l.left ( 1 );
    quint8 size = 0;
    s0 >> size;
    return size;
}

bool QQtSingleTonNamedPipeServerProtocol::dispatcher ( const QByteArray& m ) //message
{
    bool ret = true;

    QQtSingleTonNamedPipeServerMessage qMsg;
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

QQtNamedPipeServer* QQtSingleTonNamedPipeServerInstance ( QQtProtocolManager*& protocolManager, QObject* parent )
{
    static QQtProtocolManager* pm0 = 0;
    if ( !pm0 )
    {
        pm0 = new QQtProtocolManager ( parent );
        pm0->registerProtocol<QQtSingleTonNamedPipeServerProtocol>();
    }
    protocolManager = pm0;

    static QQtNamedPipeServer* s0 = NULL;
    if ( !s0 )
    {
        s0 = new QQtNamedPipeServer ( parent );
        s0->installProtocolManager ( pm0 ) ;
        //现在不监听。
        //s0->listen("QQtSingleTon");
    }

    return s0;
}
