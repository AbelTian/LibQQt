#include "qqtlanprotocol.h"

QQTLanProtocol::QQTLanProtocol ( QObject* parent ) :
    QQtProtocol ( parent )
{

}


quint16 QQTLanProtocol::minlength()
{
    return 0;
}

quint16 QQTLanProtocol::maxlength()
{
    return 0;
}

quint16 QQTLanProtocol::splitter ( const QByteArray& s )
{
    return 0;
}

bool QQTLanProtocol::dispatcher ( const QByteArray& m )
{
    return 0;
}


QQtSocketTcpServer* QQTSingleServer ( QObject* parent )
{
    static QQtSocketTcpServer* s = new QQtSocketTcpServer ( parent );
    s->listen ( QHostAddress::Any, 8000 );
    return s;
}

QQTLanProtocol* QQtLanServer ( QObject* parent )
{
    static QQTLanProtocol* p0 = NULL;
    static QQtSocketTcpServer* s0 = NULL;
    if ( !p0 && !s0 )
    {
        p0 = new QQTLanProtocol ( parent );

        s0 = new QQtSocketTcpServer ( parent );
        s0->listen ( QHostAddress::Any, 8000 );
        s0->installProtocol ( p0 );

    }

    return p0;
}
