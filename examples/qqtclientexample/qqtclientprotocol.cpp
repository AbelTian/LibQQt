#include "qqtclientprotocol.h"

QDebug& operator << ( QDebug& dbg, const QQtClientMessage& msg )
{
    //这里打印一下，报文里面到底有什么信息，
    //一般到这里的，都是被解析好的message。

    dbg.nospace() << "{" << hex << msg.getBSize() << "}";
    return dbg.space();
}

QQtClientProtocol* QQtClientConnectionInstance ( QObject* parent )
{
    static QQtClientProtocol* p0 = NULL;
    static QQtTcpClient* s0 = NULL;
    if ( !p0 && !s0 )
    {
        p0 = new QQtClientProtocol ( parent );

        s0 = new QQtTcpClient ( parent );
        s0->installProtocol ( p0 );
        QStringList ip;
        ip << "192.168.0.100";
        s0->SetServerIPAddress ( ip );
        s0->SetServerPort ( 8001 );

        s0->SendConnectMessage();

    }

    return p0;
}
