#include "qqtserver2protocolmanager.h"

QDebug& operator << ( QDebug& dbg, const QQtClient2Message& msg )
{
    //这里打印一下，报文里面到底有什么信息，
    //一般到这里的，都是被解析好的message。

    dbg.nospace() << "{" << hex << msg.size() << "}";
    return dbg.space();
}

QQtProtocolManager* QQtServer2ConnectionInstance ( QObject* parent )
{
    static QQtProtocolManager* m0 = NULL;
    if ( !m0 )
    {
        //创建Protocol管理者
        m0 = new QQtProtocolManager ( parent );
        //注册我实现的Protocol
        m0->registerProtocol<QQtServer2Protocol> ( "QQtServer2Protocol" );
        //初始化Protocol管理者完成。
    }

    static QQtTcpServer* s0 = NULL;
    if ( !s0 )
    {
        //新建服务器
        s0 = new QQtTcpServer ( parent );
        //安装协议管理者
        s0->installProtocolManager ( m0 );
        //开始监听
        s0->listen ( QHostAddress::Any, 8500 );
        //服务器初始化完成。
    }

    //等待客户端发消息过来，Protocol就处理了，去业务层看看。
    return m0;
}
