#ifndef TEST10MILLIONPEERCLIENTPROTOCOL_H
#define TEST10MILLIONPEERCLIENTPROTOCOL_H

#include <qqtmessage.h>
#include <qqtprotocol.h>
#include <qqttcpclient.h>

class Test10millionPeerClientMessage : public QQtMessage
{
    Q_OBJECT
public:
    explicit Test10millionPeerClientMessage ( QObject* parent = nullptr ) {
        mSize = 0x03;//报文定长
    }
    ~Test10millionPeerClientMessage() {

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

QDebug& operator << ( QDebug&, const Test10millionPeerClientMessage& msg );


//业务层总是用这个协议工作，读来到的，写出去的。
class Test10millionPeerClientProtocol : public QQtProtocol
{
    Q_OBJECT
public:
    explicit Test10millionPeerClientProtocol ( QObject* parent = nullptr );
    ~Test10millionPeerClientProtocol();

    //收到外部发来的很多命令，处理一下告诉业务层干点什么。
    void recvCommand1 ( const Test10millionPeerClientMessage& msg );
    void recvCommand2 ( const Test10millionPeerClientMessage& msg );
    void sendCommand1();
    void sendCommand2();

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

//业务层初始化一下这个实例，总是从这里获取协议句柄进行对外读写。
QQtTcpClient* Test10millionPeerClientInstance ( Test10millionPeerClientProtocol*& protocol, QObject* parent = 0 );

#endif // TEST10MILLIONPEERCLIENTPROTOCOL_H
