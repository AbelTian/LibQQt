#include "qqtlanprotocol.h"

QQTLanProtocol::QQTLanProtocol(QObject *parent) :
    QQtProtocol(parent)
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


QQtServer *QQTSingleServer(QObject *parent)
{
    static QQtServer* s = new QQtServer(parent);
    s->listen(QHostAddress::Any, 8000);
    return s;
}
