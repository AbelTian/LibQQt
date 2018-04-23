#ifndef QQTSERVERPROTOCOLMANAGER_H
#define QQTSERVERPROTOCOLMANAGER_H

#include <QObject>
#include <qqtmessage.h>
#include <qqtprotocol.h>
#include <qqtprotocolmanager.h>
#include <qqtcore.h>
#include <qqttcpserver.h>

/**
 * @brief The QQtServerMessage class
 * 这是协议使用的报文，报文的接收和发送格式不一样。
 */
class QQtServerMessage : public QQtMessage
{
    Q_OBJECT
public:
    explicit QQtServerMessage ( QObject* parent = 0 ) {
        bstart = 0x00;
        bend = 0x01;
    }

    quint16& getASize() {
        return asize;
    }
    const quint16& getASize() const {
        return asize;
    }

    quint8& getACmd() {
        return acmd;
    }
    const quint8& getACmd() const {
        return acmd;
    }
    QByteArray& getAData() {
        return adata;
    }
    const QByteArray& getAData() const {
        return adata;
    }

    quint16& getBSize() {
        return bsize;
    }
    const quint16& getBSize() const {
        return bsize;
    }

    quint8& getBCmd() {
        return bcmd;
    }
    const quint8& getBCmd() const {
        return bcmd;
    }
    QByteArray& getBData() {
        return bdata;
    }
    const QByteArray& getBData() const {
        return bdata;
    }

    void translate() {
        bsize = 1 + 2 + 1 + bdata.length() + 1;
    }


    // QQtMessage interface
public:
    virtual void parser ( const QByteArray& l0 ) override {
        QByteArray l = l0;
        l >> asize;
        l >> acmd;
        adata.resize ( asize - 2 - 1 );
        l >> adata;
    }
    virtual void packer ( QByteArray& l ) const override {
        l << bstart;
        l << bsize;
        l << bcmd;
        l << bdata;
        l << bend;
    }

private:
    //客户端发过来的。
    quint16 asize;
    quint8 acmd;
    QByteArray adata;

    //服务器发回去的
    quint8 bstart;
    quint16 bsize;
    quint8 bcmd;
    QByteArray bdata;
    quint8 bend;
};

/**
 * @brief The QQtServerProtocol class
 * 这是我定义的服务器和客户端的协议
 * 在这里我实现服务器要干的事情。
 * 具体的：这是我按照服务器和客户端的通信协议，实现的服务器端通信功能。
 */
class QQtServerProtocol : public QQtProtocol
{
    Q_OBJECT
public:
    explicit QQtServerProtocol ( QObject* parent = nullptr ) : QQtProtocol ( parent ) {

    }

    void recvA1Command ( const QQtServerMessage& msg ) {
        pline() << msg.getAData();
        emit notifyToProtocolManager ( this, &msg );
    }

    void sendB1Command() {
        QQtServerMessage msg;
        msg.getBCmd() = 0x01;
        msg.getBData() = "Recived, Also hello to you.";
        msg.translate();

        //pline() << msg.getBCmd() << msg.getBData();

        QByteArray l;
        msg.packer ( l );
        write ( l );
    }

    void sendB10Command() {
        QQtServerMessage msg;
        msg.getBCmd() = 0x0A;
        msg.getBData() = "Please, say hello to me.";
        msg.translate();

        //pline() << msg.getBCmd() << msg.getBData();

        QByteArray l;
        msg.packer ( l );
        write ( l );
    }

    // QQtProtocol interface
protected:
    virtual quint16 minlength() override {
        return 0x02;
    }
    virtual quint16 maxlength() override {
        return 0x07FF;
    }
    virtual quint16 splitter ( const QByteArray& l0 ) override {
        //过来的数据流，按照报文格式，取出size字段。
        QByteArray l = l0.left ( 2 );
        quint16 size;
        l >> size;
        return size;
    }
    virtual bool dispatcher ( const QByteArray& l0 ) override {
        QQtServerMessage msg;
        msg.parser ( l0 );
        //
        switch ( msg.getACmd() ) {
            case 0x01:
                recvA1Command ( msg );
                break;
            default:
                break;
        }
    }
};

/**
 * @brief The QQtServerProtocolManager class
 * ...
 */
class QQtServerProtocolManager : public QQtProtocolManager
{
    Q_OBJECT
public:
    explicit QQtServerProtocolManager ( QObject* parent = nullptr );

signals:

public slots:
};

QQtServerProtocolManager* QQtServerInstance ( QObject* parent = 0 );

#endif // QQTSERVERPROTOCOLMANAGER_H
