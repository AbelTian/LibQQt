#include <qqtnamedpipeprivate.h>


QQtNamedPipeMessage::QQtNamedPipeMessage ( QObject* parent )
{
    mSize = 0x0000;//报文定长
    mCmd = 0x00;
    mData.clear();
}

QQtNamedPipeMessage::~QQtNamedPipeMessage()
{

}

quint16& QQtNamedPipeMessage::size() { return mSize; }

const quint16& QQtNamedPipeMessage::size() const { return mSize; }

quint8& QQtNamedPipeMessage::cmd() { return mCmd; }

const quint8& QQtNamedPipeMessage::cmd() const { return mCmd; }

QByteArray& QQtNamedPipeMessage::data() { return mData; }

const QByteArray& QQtNamedPipeMessage::data() const { return mData; }

void QQtNamedPipeMessage::translate()
{
    mSize = mData.size() + 1 + 2;
}

void QQtNamedPipeMessage::parser ( const QByteArray& l )
{
    QByteArray _l = l;
    _l >> mSize;
    _l >> mCmd;
    quint16 s0 = mSize - 2 - 1;
    mData.resize ( s0 );
    _l >> mData;
}

void QQtNamedPipeMessage::packer ( QByteArray& l ) const
{
    l << mSize;
    l << mCmd;
    l << mData;
}

QDebug& operator << ( QDebug& dbg, const QQtNamedPipeMessage& msg )
{
    //这里打印一下，报文里面到底有什么信息，
    //一般到这里的，都是被解析好的message。

    dbg.nospace() << "{" << msg.size() << "|" << hex << msg.cmd() << "}";
    return dbg.space();
}

QQtNamedPipeClientProtocol::QQtNamedPipeClientProtocol ( QObject* parent )
{

}

QQtNamedPipeClientProtocol::~QQtNamedPipeClientProtocol()
{

}

void QQtNamedPipeClientProtocol::recvCommand0x01 ( const QQtNamedPipeMessage& msg )
{
    pline() << "client receive set key ack:" << msg.cmd();
}

void QQtNamedPipeClientProtocol::recvCommand0x0a ( const QQtNamedPipeMessage& msg )
{
    //what do you want to do?
    pline() << "client receive read data ack:" << msg.cmd();
    mBytes = msg.data();
}

void QQtNamedPipeClientProtocol::recvCommand0x0b ( const QQtNamedPipeMessage& msg )
{
    //what do you want to do?
    pline() << "client receive write data ack:" << msg.cmd();
    //不处理。
}

void QQtNamedPipeClientProtocol::sendCommand0x01 ( QString key )
{
    QQtNamedPipeMessage msg;
    msg.cmd() = 0x01;
    msg.data() << key.toLocal8Bit();
    msg.translate();
    QByteArray l;
    msg.packer ( l );
    write ( l );
}

//send read command
void QQtNamedPipeClientProtocol::sendCommand0x0a ( quint16 size )
{
    //what do you want to do?
    QQtNamedPipeMessage msg;
    msg.cmd() = 0x0a;
    msg.data() << size;
    msg.translate();
    QByteArray l;
    msg.packer ( l );
    write ( l );
}

//send write command
void QQtNamedPipeClientProtocol::sendCommand0x0b ( const QByteArray& data )
{
    //what do you want to do?
    QQtNamedPipeMessage msg;
    msg.cmd() = 0x0b;
    msg.data() = data;
    msg.translate();
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
    return 0xFFFF;
}

quint16 QQtNamedPipeClientProtocol::splitter ( const QByteArray& l ) //stream
{
    QByteArray s0 = l.left ( 2 );
    quint16 size = 0;
    s0 >> size;
    return size;
}

bool QQtNamedPipeClientProtocol::dispatcher ( const QByteArray& m ) //message
{
    bool ret = true;

    QQtNamedPipeMessage qMsg;
    qMsg.parser ( m );
    pline() << qMsg;

    switch ( qMsg.cmd() )
    {
        case 0x01://protocol command 1
            recvCommand0x01 ( qMsg );
            break;

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
        //现在不设置。
        //s0->setServerIPAddress ( "QQtSingleTon" );
        //现在不连接。
        //s0->sendConnectToHost();
    }

    return s0;
}

QQtNamedPipeServerProtocol::QQtNamedPipeServerProtocol ( QObject* parent )
{

}

QQtNamedPipeServerProtocol::~QQtNamedPipeServerProtocol()
{

}

void QQtNamedPipeServerProtocol::recvCommand0x01 ( const QQtNamedPipeMessage& msg )
{
    mKey = msg.data();
    sendCommand0x01();
}

void QQtNamedPipeServerProtocol::recvCommand0x0a ( const QQtNamedPipeMessage& msg )
{
    //what do you want to do?
    //把bytes里的数据发回去。
    //但是，不是在这里，而是在上层。
    emit notifyToProtocolManager ( this, &msg );
}

void QQtNamedPipeServerProtocol::recvCommand0x0b ( const QQtNamedPipeMessage& msg )
{
    //what do you want to do?
    //为bytes追加数据。
    //但是，不是在这里，而是在上层。
    emit notifyToProtocolManager ( this, &msg );
}

void QQtNamedPipeServerProtocol::sendCommand0x01()
{
    QQtNamedPipeMessage msg;
    msg.cmd() = 0x01;
    msg.translate();;
    QByteArray l;
    msg.packer ( l );
    write ( l );
    pline() << "server send set key ack command:" << msg.cmd();
}

void QQtNamedPipeServerProtocol::sendCommand0x0a ( const QByteArray& data )
{
    //what do you want to do?
    QQtNamedPipeMessage msg;
    msg.cmd() = 0x0a;
    msg.data() = data;
    msg.translate();;
    QByteArray l;
    msg.packer ( l );
    write ( l );
    pline() << "server send read data ack:" << msg.cmd();
}

void QQtNamedPipeServerProtocol::sendCommand0x0b()
{
    //what do you want to do?
    QQtNamedPipeMessage msg;
    msg.cmd() = 0x0b;
    msg.translate();;
    QByteArray l;
    msg.packer ( l );
    write ( l );
    pline() << "server send write ack command:" << msg.cmd();
}

quint16 QQtNamedPipeServerProtocol::minlength()
{
    return 0x03;
}

quint16 QQtNamedPipeServerProtocol::maxlength()
{
    return 0xFFFF;
}

quint16 QQtNamedPipeServerProtocol::splitter ( const QByteArray& l ) //stream
{
    QByteArray s0 = l.left ( 2 );
    quint16 size = 0;
    s0 >> size;
    return size;
}

bool QQtNamedPipeServerProtocol::dispatcher ( const QByteArray& m ) //message
{
    bool ret = true;

    QQtNamedPipeMessage qMsg;
    qMsg.parser ( m );
    pline() << qMsg;

    switch ( qMsg.cmd() )
    {
        case 0x01://protocol command 1
            recvCommand0x01 ( qMsg );
            break;

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

QQtLocalServer* QQtNamedPipeServerInstance ( QQtNamedPipeServerProtocolManager*& protocolManager, QObject* parent )
{
    static QQtNamedPipeServerProtocolManager* pm0 = 0;
    if ( !pm0 )
    {
        pm0 = new QQtNamedPipeServerProtocolManager ( parent );
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


QQtNamedPipeServerProtocolManager::QQtNamedPipeServerProtocolManager ( QObject* parent ) : QQtProtocolManager (
        parent )
{
    connect ( this, SIGNAL ( notifyToBusinessLevel ( const QQtProtocol*, const QQtMessage* ) ),
              this, SLOT ( slotAcceptNotify ( const QQtProtocol*, const QQtMessage* ) ) );
}

QQtNamedPipeServerProtocolManager::~QQtNamedPipeServerProtocolManager() {}

void QQtNamedPipeServerProtocolManager::slotAcceptNotify ( const QQtProtocol* protocol, const QQtMessage* message )
{
    QQtNamedPipeMessage* msg = ( QQtNamedPipeMessage* ) message;
    QQtNamedPipeServerProtocol* p0  = ( QQtNamedPipeServerProtocol* ) protocol;
    switch ( msg->cmd() )
    {
        case 0x0a:
        {
            quint16 size = 0;
            QByteArray data = msg->data();
            data >> size;
            QByteArray bytes;
            size = qMin<int> ( mBytesMap[p0->key()].size(), size );
            bytes.resize ( size );
            mBytesMap[p0->key()] >> bytes;
            p0->sendCommand0x0a ( bytes );
        }
        break;
        case 0x0b:
        {
            QByteArray data = msg->data();
            mBytesMap[p0->key()] << data;
            p0->sendCommand0x0b();
        }
        break;
        default:
            break;
    }
}
