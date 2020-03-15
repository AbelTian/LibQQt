#include <qqtfindservermanager.h>


#include <qqtframe.h>

QQtBeServerManager::QQtBeServerManager ( QObject* parent ) : QObject ( parent )
{

    s0 = new QQtUdpServer ( this );
    s0->bind ( 4408, QQtUdpServer::ShareAddress );
    p3line() << s0->peerAddress() << s0->peerPort();
    m0 = new QQtBeServerProtocolManager ( this );
    //m0->setLocalIpPort ( s0->localAddress().toString(), 4409 );
    m0->setLocalIpPort ( QHostAddress ( QHostAddress::AnyIPv4 ).toString(), 4409 );
    m0->registerProtocol<QQtBeServerProtocol>();
    s0->installProtocolManager ( m0 );

}

QQtBeServerManager::~QQtBeServerManager() {}

QQtBeServerProtocolManager::QQtBeServerProtocolManager ( QObject* parent ) : QQtProtocolManager ( parent ) {}

QQtBeServerProtocolManager::~QQtBeServerProtocolManager() {}

void QQtBeServerProtocolManager::setLocalIpPort ( QString ip, int port )
{
    mIP = ip;
    mPort = port;
}

QQtProtocol* QQtBeServerProtocolManager::createProtocol()
{
    QQtBeServerProtocol* p = ( QQtBeServerProtocol* ) QQtProtocolManager::createProtocol();
    p->setLocalIpPort ( mIP, mPort );
    return p;
}

QQtBeServerProtocol::QQtBeServerProtocol ( QObject* parent )
    : QQtStandardProtocol ( parent ) {}

QQtBeServerProtocol::~QQtBeServerProtocol()
{

}

void QQtBeServerProtocol::setLocalIpPort ( QString ip, int port )
{
    mIP = ip;
    mPort = port;
}

void QQtBeServerProtocol::sendBeServerMessage()
{
    QQtDataSerialization data;
    data[CMD_TYPE] = "server_ack";
    data[CMD_CONTENT]["ip"] = mIP;
    data[CMD_CONTENT]["port"] = mPort;
    data.serialize();
    p3line() << data[CMD_TYPE].getValue().toString() << mIP << mPort;
    sendMessage ( data );
}

void QQtBeServerProtocol::recvMessage ( const QQtDataSerialization& data )
{
    QQtDataSerialization ds0 = data;
    QString cmd_type = ds0[CMD_TYPE].getValue().toString();
    p3line() << cmd_type;
    if ( cmd_type == "find_server" )
    {
        sendBeServerMessage();
    }
}

QQtFindServerProtocol::QQtFindServerProtocol ( QObject* parent )
    : QQtStandardProtocol ( parent ) {}

QQtFindServerProtocol::~QQtFindServerProtocol()
{

}

void QQtFindServerProtocol::sendFindServerRequest()
{
    QQtDataSerialization data;
    data[CMD_TYPE] = "find_server";
    data.serialize();
    p3line() << data[CMD_TYPE].getValue().toString();
    sendMessage ( data );
}

void QQtFindServerProtocol::recvMessage ( const QQtDataSerialization& data )
{
    QQtDataSerialization ds0 = data;
    QString cmd_type = ds0[CMD_TYPE].getValue().toString();
    p3line() << cmd_type;
    if ( cmd_type == "server_ack" )
    {
        QQtDictionary& ct0 = ds0[CMD_CONTENT];
        mIP = ct0["ip"].getValue().toString();
        mPort = ct0["port"].getValue().toInt();
        p3line() << mIP << mPort;
        emit signalFindServer ( mIP, mPort );
    }
}
