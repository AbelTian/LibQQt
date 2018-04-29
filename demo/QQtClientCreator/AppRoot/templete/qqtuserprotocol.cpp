#include "qqtuserprotocol.h"

QDebug& operator << ( QDebug& dbg, const QQtUserMessage& msg )
{
    //这里打印一下，报文里面到底有什么信息，
    //一般到这里的，都是被解析好的message。

    dbg.nospace() << "{" << hex << msg.size() << "}";
    return dbg.space();
}

QQtTcpClient* QQtUserInstance ( QQtUserProtocol*& protocol, QObject* parent )
{
    static QQtUserProtocol* p0 = NULL;
    if ( !p0 )
    {
        p0 = new QQtUserProtocol ( parent );
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

    return s0;
}
