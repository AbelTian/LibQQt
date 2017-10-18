#include "qqtlanprotocol.h"

QQTLanProtocol::QQTLanProtocol(QObject *parent) :
    QQTProtocol(parent)
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

quint16 QQTLanProtocol::splitter(const QByteArray &s)
{
    return 0;
}

bool QQTLanProtocol::dispatcher(const QByteArray &m)
{
    return 0;
}


QQTServer *QQTSingleServer(QObject *parent)
{
    static QQTServer* s = new QQTServer(parent);
    s->listen(QHostAddress::Any, 8000);
    return s;
}
