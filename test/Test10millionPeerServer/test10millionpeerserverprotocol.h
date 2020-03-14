#ifndef TEST10MILLIONPEERSERVERPROTOCOL_H
#define TEST10MILLIONPEERSERVERPROTOCOL_H

#include <qqtmessage.h>
#include <qqtprotocol.h>
#include <qqtprotocolmanager.h>
#include <qqttcpserver.h>

class Test10millionPeerServerMessage : public QQtMessage
{
    Q_OBJECT
public:
    explicit Test10millionPeerServerMessage ( QObject* parent = nullptr ) {
        mSize = 0x03;//报文定长
    }
    ~Test10millionPeerServerMessage() {

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
    virtual void packer ( QByteArray& l ) override {
        l << mSize;
        l << mCmd;
        l << mData;
    }
};

QDebug& operator << ( QDebug& dbg, const Test10millionPeerServerMessage& msg );

//业务层总是用这个协议工作，读来到的，写出去的。
class Test10millionPeerServerProtocol : public QQtProtocol
{
    Q_OBJECT
public:
    explicit Test10millionPeerServerProtocol ( QObject* parent = nullptr );
    ~Test10millionPeerServerProtocol();

    //收到外部发来的很多命令，处理一下告诉业务层干点什么。
    void recvCommand1 ( const Test10millionPeerServerMessage& msg );
    void recvCommand2 ( const Test10millionPeerServerMessage& msg );

    void sendCommand1();

signals:
    //给业务层发的信号
    void signalSendtoLogicLevelCode();

public slots:

    // QQtProtocol interface
protected:
    //报文的最小长度
    virtual quint16 minlength() override;
    //报文的最大长度
    virtual quint16 maxlength() override;
    //报文现在在流里，第一个字节，就是size，读出来，通过返回值告诉QQtProtocol
    virtual quint16 splitter ( const QByteArray& l ) override;

    //报文现在被切开，发了进来，第二个字节是cmd，解析出来，在函数里处理处理数据，告诉业务层，拿到数据了干点什么。
    virtual bool dispatcher ( const QByteArray& m ) override;
};

//用户使用这里的ProtocolManager进行必要的和客户端的通信。一般在Test10millionPeerServerProtocol里面解决。
QQtTcpServer* Test10millionPeerServerInstance ( QQtProtocolManager*& protocolManager, QObject* parent );

#endif // TEST10MILLIONPEERSERVERPROTOCOL_H
