#ifndef QQTSINGLETONAPPLICATIONPRIVATE_H
#define QQTSINGLETONAPPLICATIONPRIVATE_H

#include <qqt-local.h>
#include <qqtcore.h>
#include <qlocalsocket.h>
#include <qlocalserver.h>

#include <qqtmessage.h>
#include <qqtprotocol.h>
#include <qqtlocalclient.h>

class QQtSingleTonLocalClientMessage : public QQtMessage
{
    Q_OBJECT
public:
    explicit QQtSingleTonLocalClientMessage ( QObject* parent = nullptr );
    ~QQtSingleTonLocalClientMessage();

    quint8& size();
    const quint8& size() const;
    quint8& cmd();
    const quint8& cmd() const;
    quint8& data();
    const quint8& data() const;

private:
    //格式
    //|quint8 size|quint8 cmd|quint8 data|
    quint8 mSize;
    quint8 mCmd;
    quint8 mData;

    // QQtMessage interface
public:
    //把报文这条流解析出字段
    virtual void parser ( const QByteArray& l ) override;
    //把报文字段组装成流
    virtual void packer ( QByteArray& l ) const override;
};

QDebug& operator << ( QDebug&, const QQtSingleTonLocalClientMessage& msg );

//业务层总是用这个协议工作，读来到的，写出去的。
class QQtSingleTonLocalClientProtocol : public QQtProtocol
{
    Q_OBJECT
public:
    explicit QQtSingleTonLocalClientProtocol ( QObject* parent = nullptr );
    ~QQtSingleTonLocalClientProtocol();

    //没连接上：创建Server，发送I Create you (0x0a). Server回复，I Accept you (0x0a)。
    //连接上了，发送I Find you (0x0b)。Server回复，存在Server (0x0b)，告诉上层，关闭程序。

    //收到外部发来的很多命令，处理一下告诉业务层干点什么。
    void recvCommand1 ( const QQtSingleTonLocalClientMessage& msg );
    void recvCommand2 ( const QQtSingleTonLocalClientMessage& msg );
    void sendCommand1();
    void sendCommand2();

signals:
    //给业务层发的信号
    void signalSendtoLogicLevelCode();
    void signalAccept();
    void signalReject();

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

#include <qqtprotocolmanager.h>
#include <qqtlocalserver.h>

class QQtSingleTonLocalServerMessage : public QQtMessage
{
    Q_OBJECT
public:
    explicit QQtSingleTonLocalServerMessage ( QObject* parent = nullptr );
    ~QQtSingleTonLocalServerMessage();

    quint8& size();
    const quint8& size() const;
    quint8& cmd();
    const quint8& cmd() const;
    quint8& data();
    const quint8& data() const;

private:
    //格式
    //|quint8 size|quint8 cmd|quint8 data|
    quint8 mSize;
    quint8 mCmd;
    quint8 mData;

    // QQtMessage interface
public:
    //把报文这条流解析出字段
    virtual void parser ( const QByteArray& l ) override;
    //把报文字段组装成流
    virtual void packer ( QByteArray& l ) const override;
};

QDebug& operator << ( QDebug&, const QQtSingleTonLocalServerMessage& msg );


//业务层总是用这个协议工作，读来到的，写出去的。
class QQtSingleTonLocalServerProtocol : public QQtProtocol
{
    Q_OBJECT
public:
    explicit QQtSingleTonLocalServerProtocol ( QObject* parent = nullptr );
    ~QQtSingleTonLocalServerProtocol();

    //收到外部发来的很多命令，处理一下告诉业务层干点什么。
    void recvCommand1 ( const QQtSingleTonLocalServerMessage& msg );
    void recvCommand2 ( const QQtSingleTonLocalServerMessage& msg );
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


#endif //QQTSINGLETONAPPLICATIONPRIVATE_H
