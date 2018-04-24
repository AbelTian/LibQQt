#ifndef QQTSERVER2PROTOCOLMANAGER_H
#define QQTSERVER2PROTOCOLMANAGER_H

#include <qqtmessage.h>
#include <qqtprotocol.h>
#include <qqttcpserver.h>

class QQtClient2Message : public QQtMessage
{
    Q_OBJECT
public:
    explicit QQtClient2Message ( QObject* parent = nullptr ) {

    }
    ~QQtClient2Message() {

    }

    quint16& size() { return mSize; }
    const quint16& size() const { return mSize; }
    quint8& cmd() { return mCmd; }
    const quint8& cmd() const { return mCmd; }
    QByteArray& data() { return mData; }
    const QByteArray& data() const { return mData; }

    void translate() {
        mSize = 3 + mData.size();
    }

private:
    //格式
    //|quint8 size|quint8 cmd|quint8 data|
    quint16 mSize;
    quint8 mCmd;
    QByteArray mData;

    // QQtMessage interface
public:
    //把报文这条流解析出字段
    virtual void parser ( const QByteArray& l ) override {
        QByteArray _l = l;
        _l >> mSize;
        _l >> mCmd;
        mData.resize ( mSize - 3 );
        _l >> mData;
    }
    //把报文字段组装成流
    virtual void packer ( QByteArray& l ) const override {
        l << mSize;
        l << mCmd;
        l << mData;
    }
};

QDebug& operator << ( QDebug&, const QQtClient2Message& msg );




//业务层总是用这个协议工作，读来到的，写出去的。
class QQtServer2Protocol : public QQtProtocol
{
    Q_OBJECT
public:
    explicit QQtServer2Protocol ( QObject* parent = nullptr ) {

    }
    ~QQtServer2Protocol() {

    }

    //收到外部发来的很多命令，处理一下告诉业务层干点什么。
    void recvCommand1 ( const QQtClient2Message& msg ) {
        //what do you want to do?
        pline() << "recv msg 1" << msg.data();
        sendCommand1();
    }
    void recvCommand2 ( const QQtClient2Message& msg ) {
        //what do you want to do?
        pline() << "dddd";
    }

    void sendCommand() {
        pline() << "ffff";
    }

    void sendCommand1() {
        QQtClient2Message msg;
        msg.cmd() = 0x0a;
        msg.data() = "FFFF";
        msg.translate();

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
        return 0x02;
    }
    //报文的最大长度
    virtual quint16 maxlength() override {
        return 0x07FF;
    }
    //报文现在在流里，第一个字节，就是size，读出来，通过返回值告诉QQtProtocol
    virtual quint16 splitter ( const QByteArray& l ) override { //stream
        QByteArray s0 = l.left ( 2 );
        quint16 size = 0;
        s0 >> size;
        return size;
    }

    //报文现在被切开，发了进来，第二个字节是cmd，解析出来，在函数里处理处理数据，告诉业务层，拿到数据了干点什么。
    virtual bool dispatcher ( const QByteArray& m ) override { //message
        bool ret = true;

        QQtClient2Message qMsg;
        qMsg.parser ( m );
        pline() << qMsg;

        switch ( qMsg.cmd() ) {
            case 0x01://protocol command 1
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
QQtProtocolManager* QQtServer2ConnectionInstance ( QObject* parent = 0 );

#endif // QQTSERVER2PROTOCOL_H
