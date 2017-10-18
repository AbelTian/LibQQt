#ifndef QQTLANPROTOCOL_H
#define QQTLANPROTOCOL_H

#include "qqtprotocol.h"
#include "qqtserver.h"

class QQTLanProtocol : public QQTProtocol
{
public:
    explicit QQTLanProtocol(QObject *parent = 0);

    // QQTProtocol interface
public:
    quint16 minlength() override;
    quint16 maxlength() override;
    quint16 splitter(const QByteArray &s) override;
    bool dispatcher(const QByteArray &m) override;
};

QQTServer *QQTSingleServer(QObject* parent);

#endif // QQTLANPROTOCOL_H
