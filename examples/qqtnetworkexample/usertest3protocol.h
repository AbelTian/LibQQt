#ifndef USERTEST3PROTOCOL_H
#define USERTEST3PROTOCOL_H

#include <qqtmessage.h>
#include <qqtprotocol.h>
#include <qqtsockettcpserver.h>

class UserTest3Message : public QQtMessage
{
    Q_OBJECT
public:
    explicit UserTest3Message ( QObject* parent = nullptr ) {
        mSize = 0x03;//报文定长
    }
    ~UserTest3Message() {

    }

    quint8& size() { return mSize; }
    const quint8& size() const { return mSize; }
    quint8& cmd() { return mCmd; }
    const quint8& cmd() const { return mCmd; }
    quint8& data() { return mData; }
    const quint8& data() const { return mData; }

private:
    //格式
    //|quint8 size|quint8 cmd|quint8 data|
    quint8 mSize;
    quint8 mCmd;
    quint8 mData;

    // QQtMessage interface
public:
    //把报文这条流解析出字段
    virtual void parser ( const QByteArray& l ) override {
        QByteArray _l = l;
        _l >> mSize;
        _l >> mCmd;
        _l >> mData;
    }
    //把报文字段组装成流
    virtual void packer ( QByteArray& l ) const override {
        l << mSize;
        l << mCmd;
        l << mData;
    }
};

QDebug& operator << ( QDebug&, const UserTest3Message& msg );


//业务层总是用这个协议工作，读来到的，写出去的。
class UserTest3Protocol : public QQtProtocol
{
    Q_OBJECT
public:
    explicit UserTest3Protocol ( QObject* parent = nullptr ) {

    }
    ~UserTest3Protocol() {

    }

    //收到外部发来的很多命令，处理一下告诉业务层干点什么。
    void recvCommand1 ( const UserTest3Message& msg ) {
        //what do you want to do?
    }
    void recvCommand2 ( const UserTest3Message& msg ) {
        //what do you want to do?
    }

signals:
    //给业务层发的信号
    void signalSendtoLogicLevelCode();

public slots:

    // QQtProtocol interface
protected:
    //报文的最小长度
    virtual quint16 minlength() override {
        return 0x0a;
    }
    //报文的最大长度
    virtual quint16 maxlength() override {
        return 0x07FF;
    }
    //报文现在在流里，第一个字节，就是size，读出来，通过返回值告诉QQtProtocol
    virtual quint16 splitter ( const QByteArray& l ) override { //stream
        QByteArray s0 = l.left ( 1 );
        quint8 size = 0;
        s0 >> size;
        return size;
    }

    //报文现在被切开，发了进来，第二个字节是cmd，解析出来，在函数里处理处理数据，告诉业务层，拿到数据了干点什么。
    virtual bool dispatcher ( const QByteArray& m ) override { //message
        bool ret = true;

        UserTest3Message qMsg;
        qMsg.parser ( m );
        pline() << qMsg;

        switch ( qMsg.cmd() ) {
            case 0x0a://protocol command 1
                recvCommand1 ( qMsg );
                break;

            case 0x0b://protocol command 2
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

//业务层初始化一下这个实例，总是从这里获取协议句柄进行对外读写。
UserTest3Protocol* UserTest3ConnectionInstance ( QObject* parent = 0 );

#endif // USERTEST3PROTOCOL_H
