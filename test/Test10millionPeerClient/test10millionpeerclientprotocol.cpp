#include "test10millionpeerclientprotocol.h"
#include <qqtapplication.h>
quint32 gnum = 0;
QMutex mutex ( QMutex::NonRecursive );

QDebug& operator << ( QDebug& dbg, const Test10millionPeerClientMessage& msg )
{
    //这里打印一下，报文里面到底有什么信息，
    //一般到这里的，都是被解析好的message。

    dbg.nospace() << "{" << hex << msg.size() << "}";
    return dbg.space();
}

QQtTcpClient* Test10millionPeerClientInstance ( Test10millionPeerClientProtocol*& protocol, QObject* parent )
{
    static Test10millionPeerClientProtocol* p0 = NULL;
    if ( !p0 )
    {
        p0 = new Test10millionPeerClientProtocol ( parent );
    }
    protocol = p0;

    static QQtTcpClient* s0 = NULL;
    if ( !s0 )
    {
        s0 = new QQtTcpClient ( parent );
        s0->installProtocol ( p0 );
        //s0->setServer
        //s0->sendConnectToHost();
    }

    for ( int i = 0; i < 100000; i++ )
    {
        Test10millionPeerClientProtocol* p1 = new Test10millionPeerClientProtocol ( parent );
        QQtTcpClient* s1 = new QQtTcpClient ( parent );
        s1->installProtocol ( p1 );
        s1->setServerIPAddress ( "192.168.3.103" );
        s1->sendConnectToHost();
        s1->waitForConnected();
        p1->sendCommand1();
        QQtApplication::processEvents();
    }

    return s0;
}

Test10millionPeerClientProtocol::Test10millionPeerClientProtocol ( QObject* parent )
{

}

Test10millionPeerClientProtocol::~Test10millionPeerClientProtocol()
{

}

void Test10millionPeerClientProtocol::recvCommand1 ( const Test10millionPeerClientMessage& msg )
{
    //what do you want to do?
    pline() << this << msg.data();
    sendCommand2();
    mutex.lock();
    gnum ++;
    mutex.unlock();
    pline() << "protocol " << gnum << "complete.";
}

void Test10millionPeerClientProtocol::recvCommand2 ( const Test10millionPeerClientMessage& msg )
{
    //what do you want to do?
}

void Test10millionPeerClientProtocol::sendCommand1()
{
    //what do you want to do?
    Test10millionPeerClientMessage msg;
    msg.cmd() = 0x0a;
    msg.data() = 0x00;
    QByteArray l;
    msg.packer ( l );
    write ( l );
}

void Test10millionPeerClientProtocol::sendCommand2()
{
    Test10millionPeerClientMessage msg;
    msg.cmd() = 0x0b;
    msg.data() = 0x01;
    QByteArray l;
    msg.packer ( l );
    write ( l );
}

quint16 Test10millionPeerClientProtocol::minlength()
{
    return 0x0a;
}

quint16 Test10millionPeerClientProtocol::maxlength()
{
    return 0x07FF;
}

quint16 Test10millionPeerClientProtocol::splitter ( const QByteArray& l ) //stream
{
    QByteArray s0 = l.left ( 1 );
    quint8 size = 0;
    s0 >> size;
    return size;
}

bool Test10millionPeerClientProtocol::dispatcher ( const QByteArray& m ) //message
{
    bool ret = true;

    Test10millionPeerClientMessage qMsg;
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
