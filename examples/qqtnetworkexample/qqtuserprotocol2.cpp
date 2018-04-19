#include "qqtuserprotocol2.h"

QDebug& operator << ( QDebug& dbg, const QQtUserMessage2& msg )
{
    //这里打印一下，报文里面到底有什么信息，
    //一般到这里的，都是被解析好的message。

    dbg.nospace() << "{" << hex << msg.size() << "}";
    return dbg.space();
}

QQtUserProtocol2* QQtUserConnectionInstance2 ( QObject* parent )
{
    static QQtUserProtocol2* p0 = NULL;
    static QQtSocketTcpClient* s0 = NULL;
    if ( !p0 && !s0 )
    {
        p0 = new QQtUserProtocol2 ( parent );

        s0 = new QQtSocketTcpClient ( parent );
        s0->installProtocol ( p0 );
        s0->connectToHost ( QHostAddress ( "192.168.0.100" ), 8000 );
    }

    return p0;
}
