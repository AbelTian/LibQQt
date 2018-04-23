#include "qqtclient2protocol.h"

QDebug& operator << ( QDebug& dbg, const QQtClient2Message& msg )
{
    //这里打印一下，报文里面到底有什么信息，
    //一般到这里的，都是被解析好的message。

    dbg.nospace() << "{" << hex << msg.size() << "}";
    return dbg.space();
}

QQtClient2Protocol* QQtClient2ConnectionInstance ( QObject* parent )
{
    static QQtClient2Protocol* p0 = NULL;
    if ( !p0 )
    {
        p0 = new QQtClient2Protocol ( parent );
    }

    static QQtTcpClient* s0 = NULL;
    if ( !s0 )
    {
        s0 = new QQtTcpClient ( parent );
        s0->installProtocol ( p0 );

        QStringList ip;
        ip << "192.168.0.100";
        s0->SetServerIPAddress ( ip );
        s0->SetServerPort ( 8500 );

        s0->SendConnectMessage();
    }

    return p0;
}
