#include "cedianudpprotocol.h"

CedianUdpProtocol::CedianUdpProtocol ( QObject* parent ) : QQtProtocol ( parent )
{

}

bool CedianUdpProtocol::dispatcher ( const QByteArray& dg )
{
    QByteArray data = dg;
    mMsg.parser ( data );
    emit msgIncoming();
}

/*依赖已经初始化好的端口*/
CedianUdpProtocol* cedianUdpServer ( QObject* parent )
{
    static CedianUdpServer* s0[9] = {NULL};
    static CedianUdpProtocol* p0 = NULL;
    if ( !s0[0] && !p0 )
    {
        p0 = new CedianUdpProtocol ( parent );
        for ( int i = 0; i < 9; i++ )
        {
            int port = cedianUdpPort ( i + 1 );
            pline() << i + 1 << port;

            s0[i] = new CedianUdpServer ( parent );
            /*通讯端口：绑定本地端口*/
            s0[i]->bind ( port );
            /*通讯端口：给测点协议*/
            //s0[i]->installProtocol ( p0 );
        }
    }
    return p0;
}

/*
 * 这里最好添加一个针对测点的本地监听Port列表设置函数，给mainwindow调用。
 * 初始化第一次调用，需要把port列表传进去。
 * 以后只需要获取即可，这个端口列表，重启生效。
 * 不要少于9个，不要越界。
 * 1-9
*/
qint32 cedianUdpPort ( int siteID, qint32* portList )
{
    if ( siteID < 1 || siteID > 9 )
        return 0;

    static qint32 sPort[9] = {0};
    if ( portList )
    {
        for ( int i = 0; i < 9; i++ )
        {
            sPort[i] = portList[i];
        }
    }
    return sPort[siteID - 1];
}
