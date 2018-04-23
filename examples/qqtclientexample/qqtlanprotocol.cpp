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


QQtTcpServer* QQTSingleServer ( QObject* parent )
{
    static QQtTcpServer* s = new QQtTcpServer ( parent );
    s->listen ( QHostAddress::Any, 8000 );
    return s;
}

QQTLanProtocol* QQtLanServer ( QObject* parent )
{
    static QQTLanProtocol* p0 = NULL;
    static QQtTcpServer* s0 = NULL;
    if ( !p0 && !s0 )
    {
        p0 = new QQTLanProtocol ( parent );

        s0 = new QQtTcpServer ( parent );
        s0->listen ( QHostAddress::Any, 8000 );
        s0->installProtocol ( p0 );

    }

    return p0;
}
