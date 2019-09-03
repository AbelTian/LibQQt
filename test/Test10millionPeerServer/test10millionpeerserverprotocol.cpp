#include "test10millionpeerserverprotocol.h"

quint32 gnum = 0;
QMutex mutex ( QMutex::NonRecursive );

QDebug& operator << ( QDebug& dbg, const Test10millionPeerServerMessage& msg )
{
    //这里打印一下，报文里面到底有什么信息，
    //一般到这里的，都是被解析好的message。

    dbg.nospace() << "{" << hex << msg.size() << "}";
    return dbg.space();
}

QQtTcpServer* Test10millionPeerServerInstance ( QQtProtocolManager*& protocolManager, QObject* parent )
{
    static QQtProtocolManager* m0 = 0;
    if ( !m0 )
    {
        //创建Protocol管理者
        m0 = new QQtProtocolManager ( parent );
        //注册我实现的Protocol 默认1024个 如果不够用，m0有个协议句柄个数变化信号，进行动态增加。
        m0->registerProtocol<Test10millionPeerServerProtocol> ( 110000 );
        //初始化Protocol管理者完成。
    }
    protocolManager = m0;

    static QQtTcpServer* s0 = 0;
    if ( !s0 )
    {
        //新建服务器
        s0 = new QQtTcpServer ( parent );
        //安装协议管理者
        s0->installProtocolManager ( m0 );
        //开始监听
        s0->listen ( QHostAddress::Any, 8001 );
        //服务器初始化完成。
    }

    //等待客户端发消息过来，Protocol就处理了，去业务层看看。
    return s0;
}

Test10millionPeerServerProtocol::Test10millionPeerServerProtocol ( QObject* parent )
{

}

Test10millionPeerServerProtocol::~Test10millionPeerServerProtocol()
{

}

void Test10millionPeerServerProtocol::recvCommand1 ( const Test10millionPeerServerMessage& msg )
{
    //what do you want to do?
    sendCommand1();
}

void Test10millionPeerServerProtocol::recvCommand2 ( const Test10millionPeerServerMessage& msg )
{
    //what do you want to do?
    mutex.lock();
    gnum ++;
    mutex.unlock();
    pline() << "protocol " << gnum << "complete.";
}

void Test10millionPeerServerProtocol::sendCommand1()
{
    //what do you want to do?
    Test10millionPeerServerMessage msg;
    msg.cmd() = 0x0a;
    msg.data() = 0x0aaa;
    QByteArray l;
    msg.packer ( l );
    write ( l );
    pline() << msg;
}

quint16 Test10millionPeerServerProtocol::minlength()
{
    return 0x01;
}

quint16 Test10millionPeerServerProtocol::maxlength()
{
    return 0x05;
}

quint16 Test10millionPeerServerProtocol::splitter ( const QByteArray& l ) //stream
{
    QByteArray s0 = l.left ( 1 );
    quint8 size = 0;
    s0 >> size;
    return size;
}

bool Test10millionPeerServerProtocol::dispatcher ( const QByteArray& m ) //message
{
    bool ret = true;

    Test10millionPeerServerMessage qMsg;
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
