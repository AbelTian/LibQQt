#ifndef QQTNAMEDPIPEPRIVATE_H
#define QQTNAMEDPIPEPRIVATE_H

#include <qqt-local.h>
#include <qqtcore.h>

#include <qqtmessage.h>

class QQtNamedPipeMessage : public QQtMessage
{
    Q_OBJECT
public:
    explicit QQtNamedPipeMessage ( QObject* parent = nullptr );
    ~QQtNamedPipeMessage();

    quint16& size();
    const quint16& size() const;
    quint8& cmd();
    const quint8& cmd() const;
    QByteArray& data();
    const QByteArray& data() const;

    void translate();

private:
    //格式
    //|quint16 size|quint8 cmd|QByteArray data|
    quint16 mSize;
    quint8 mCmd;
    QByteArray mData;

    // QQtMessage interface
public:
    //把报文这条流解析出字段
    virtual void parser ( const QByteArray& l ) override;
    //把报文字段组装成流
    virtual void packer ( QByteArray& l ) const override;
};

QDebug& operator << ( QDebug&, const QQtNamedPipeMessage& msg );

#include <qqtprotocol.h>
#include <qqtnamedpipeclient.h>

//业务层总是用这个协议工作，读来到的，写出去的。
class QQtNamedPipeClientProtocol : public QQtProtocol
{
    Q_OBJECT
public:
    explicit QQtNamedPipeClientProtocol ( QObject* parent = nullptr );
    ~QQtNamedPipeClientProtocol();

    //收到外部发来的很多命令，处理一下告诉业务层干点什么。
    void recvCommand0x01 ( const QQtNamedPipeMessage& msg );
    void recvCommand0x0a ( const QQtNamedPipeMessage& msg );
    void recvCommand0x0b ( const QQtNamedPipeMessage& msg );

    void sendCommand0x01 ( QString key );
    void sendCommand0x0a ( quint16 size );
    void sendCommand0x0b ( const QByteArray& data );

    QByteArray& bytes() { return mBytes; }
private:
    //读到的
    QByteArray mBytes;
signals:
    //给业务层发的信号
    void signalSendtoLogicLevelCode();
    void signalSuccessCommand();

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
#include <qqtnamedpipeserver.h>

//业务层总是用这个协议工作，读来到的，写出去的。
class QQtNamedPipeServerProtocol : public QQtProtocol
{
    Q_OBJECT
public:
    explicit QQtNamedPipeServerProtocol ( QObject* parent = nullptr );
    ~QQtNamedPipeServerProtocol();

    //收到外部发来的很多命令，处理一下告诉业务层干点什么。
    void recvCommand0x01 ( const QQtNamedPipeMessage& msg );
    void recvCommand0x0a ( const QQtNamedPipeMessage& msg );
    void recvCommand0x0b ( const QQtNamedPipeMessage& msg );

    void sendCommand0x01();
    void sendCommand0x0a ( const QByteArray& data );
    void sendCommand0x0b();

    QString& key() { return mKey; }
private:
    //key
    QString mKey;

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

class QQtNamedPipeServerProtocolManager : public QQtProtocolManager
{
    Q_OBJECT
public:
    explicit QQtNamedPipeServerProtocolManager ( QObject* parent = 0 );
    virtual ~QQtNamedPipeServerProtocolManager();

private slots:
    void slotAcceptNotify ( const QQtProtocol* protocol, const QQtMessage* message );
private:
    //注意此处，不必加锁，因为，Server和Protocol是在同一个线程里执行的，所有的协议都顺序在这个线程里读写，没有跨线程。
    QMap<QString, QByteArray> mBytesMap;
};

class QQtNamedPipeThread : public QThread
{
    Q_OBJECT
public:
    explicit QQtNamedPipeThread ( QObject* parent = 0 ) : QThread ( parent ) {

    }

public slots:
    void slotStartNamedPipeServer ( QQtNamedPipeServer* s0 ) {
        s0->listen ( "QQtNamedPipeServer" );
        while ( !s0->isListening() ) {
            QApplication::processEvents ( QEventLoop::AllEvents | QEventLoop::WaitForMoreEvents );
        }
    }
};

#endif //QQTNAMEDPIPEPRIVATE_H
