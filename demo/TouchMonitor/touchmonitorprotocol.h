#ifndef TOUCHMONITORPROTOCOL_H
#define TOUCHMONITORPROTOCOL_H

#include <qqtmessage.h>
#include <qqtprotocol.h>
#include <qqttcpclient.h>

/**
 * quint8 quint8 quint16 quint16
 * size cmd xP yP
 */
class TouchMonitorMessage : public QQtMessage
{
    Q_OBJECT
public:
    explicit TouchMonitorMessage ( QObject* parent = nullptr ) {
        mSize = 0x06;//报文定长
    }
    ~TouchMonitorMessage() {

    }

    quint8& size() { return mSize; }
    const quint8& size() const { return mSize; }
    quint8& cmd() { return mCmd; }
    const quint8& cmd() const { return mCmd; }
    quint16& x() { return mX; }
    const quint16& x() const { return mX; }
    quint16& y() { return mY; }
    const quint16& y() const { return mY; }

private:
    //格式
    //|quint8 size|quint8 cmd|quint8 data|
    quint8 mSize;
    quint8 mCmd;
    quint16 mX;
    quint16 mY;

    // QQtMessage interface
public:
    //把报文这条流解析出字段
    virtual void parser ( const QByteArray& l ) override {
        QByteArray _l = l;
        _l >> mSize;
        _l >> mCmd;
        _l >> mX;
        _l >> mY;
    }
    //把报文字段组装成流
    virtual void packer ( QByteArray& l ) const override {
        l << mSize;
        l << mCmd;
        l << mX;
        l << mY;
    }
};

QDebug& operator << ( QDebug&, const TouchMonitorMessage& msg );


//业务层总是用这个协议工作，读来到的，写出去的。
class TouchMonitorProtocol : public QQtProtocol
{
    Q_OBJECT
public:
    explicit TouchMonitorProtocol ( QObject* parent = nullptr ) {

    }
    ~TouchMonitorProtocol() {

    }

    //收到外部发来的很多命令，处理一下告诉业务层干点什么。
    //客户端不干什么
    void recvCommand1 ( const TouchMonitorMessage& msg ) {
        //what do you want to do?
    }
    void recvCommand2 ( const TouchMonitorMessage& msg ) {
        //what do you want to do?
    }

    /**
     * 0x0a 提交分辨率
     * 0x0b 提交点击位置
     */

    void sendCommand0a ( QPoint point ) {
        //what do you want to do?
        //获取窗口的大小，发给Server
        TouchMonitorMessage msg;
        msg.cmd() = 0x0a;
        msg.x() = point.x();
        msg.y() = point.y();

        QByteArray l;
        msg.packer ( l );
        write ( l );
    }

    void sendCommand0b ( QPoint point ) {
        //根据当前点击位置，发送坐标给Server
        TouchMonitorMessage msg;
        msg.cmd() = 0x0b;
        msg.x() = point.x();
        msg.y() = point.y();

        QByteArray l;
        msg.packer ( l );
        write ( l );
    }

signals:
    //给业务层发的信号
    void signalSendtoLogicLevelCode();

public slots:

    // QQtProtocol interface
protected:
    //报文的最小长度
    virtual quint16 minlength() override {
        return 0x06;
    }
    //报文的最大长度
    virtual quint16 maxlength() override {
        return 0x06;
    }
    //报文现在在流里，第一个字节，就是size，读出来，通过返回值告诉QQtProtocol
    virtual quint16 splitter ( const QByteArray& l ) override { //stream
        QByteArray s0 = l.left ( 1 );
        quint8 size = 0;
        s0 >> size;
        //0x06;
        return size;
    }

    //报文现在被切开，发了进来，第二个字节是cmd，解析出来，在函数里处理处理数据，告诉业务层，拿到数据了干点什么。
    virtual bool dispatcher ( const QByteArray& m ) override { //message
        bool ret = true;

        TouchMonitorMessage qMsg;
        qMsg.parser ( m );
        pline() << qMsg;

        switch ( qMsg.cmd() ) {
            case 0x0a ://protocol command 1
                recvCommand1 ( qMsg );
                break;

            case 0x0b ://protocol command 2
                recvCommand2 ( qMsg );
                break;

            default:
                ret = false;
                pline() << "receive unknown command:" << hex << qMsg.cmd();
                break;
        }

        return ret;
    }
};

#endif // TOUCHMONITORPROTOCOL_H
