#ifndef QQTLANPROTOCOL_H
#define QQTLANPROTOCOL_H

#include "qqtprotocol.h"
#include "qqtmessage.h"
#include "qqttcpserver.h"

class QQtLanMessage : public QQtMessage
{
    Q_OBJECT
public:
    explicit QQtLanMessage ( QObject* parent = 0 ) {
        mSize = 0x03;//3个字节 定长
    }
    ~QQtLanMessage() {

    }

    quint8& size() { return mSize; }
    const quint8& size() const { return mSize; }


private:
    //一条报文格式
    //|quint8 size| quint8 cmd|quint8 data|
    quint8 mSize;
    quint8 mCmd;
    quint8 mData;

    // QQtMessage interface
public:
    virtual void parser ( const QByteArray& l ) override {
        QByteArray _l = l;
        _l >> mSize;
        _l >> mCmd;
        _l >> mData;
    }
    virtual void packer ( QByteArray& l ) const override {
        l << mSize;
        l << mCmd;
        l << mData;
    }
};

class QQTLanProtocol : public QQtProtocol
{
    Q_OBJECT
public:
    explicit QQTLanProtocol ( QObject* parent = 0 );

    //void recvUserACommand ( const& data );

    // QQtProtocol interface
public:
    quint16 minlength() override;
    quint16 maxlength() override;
    quint16 splitter ( const QByteArray& s ) override;
    bool dispatcher ( const QByteArray& m ) override;
};

QQtTcpServer* QQTSingleServer ( QObject* parent );
//new
QQTLanProtocol* QQtLanServer ( QObject* parent = 0 );
#endif // QQTLANPROTOCOL_H
