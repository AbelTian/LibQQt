#ifndef QQTNAMEDPIPE_H
#define QQTNAMEDPIPE_H

#include <qqt-local.h>
#include <qqtcore.h>

#include <qqtlocalclient.h>

/**
 * @brief The QQtNamedPipe class
 * 类似于QSharedMemory使用方式。只不过底层使用Pipe(QLocalSocket)实现。
 * 支持同时使用多个命名管道。
 *
 * 原理：
 * 按照key区分管道。
 * initializer里面的create、attach提供对管道的创建和关联。
 * packer把自己的数据结构打包写进管道。
 * parser把管道的数据解包到本地变量。
 *
 * 注意：one key，管道里的数据是顺序的，流的，存在数据结构。
 * 注意：每一次写的数据，读取一次就能读出来。这一次的数据读写长度没有限制。
 * 注意：管道里的数据是顺序的，顺序的，顺序的！谁都可以读也可以写。只要key对号。
 *
 * 多路管道的格式：
 * QString  QByteArray
 * key1     pipe1
 * key2     pipe2
 * ...      ...
 */
class QQTSHARED_EXPORT QQtNamedPipe : public QQtLocalClient
{
    Q_OBJECT
public:
    explicit QQtNamedPipe ( const QString& key, QObject* parent = Q_NULLPTR ) : QQtLocalClient ( parent ) {

    }
    ~QQtNamedPipe() {}

    virtual void initializer() {
        //user set payload size.
        //这个只需要调用一次，但是调用多次也正常使用。我在这个教程父类里面给的是1024.子类可变可改。这个是最大约束，万万不能超过。
        //create ( 1024 );
        //这个每个变量都必须调用！是这个函数保证data()指针有数的。
        //attach();
    }

    //需要重写，实现把局部变量打包到共享内存块。（注释部分。）
    //这个函数保证写入共享内存。
    virtual void packer() {
        //lock();

        //user data struct
        QByteArray bytes;
        //bytes << a;

        //这个是无论如何不应该发生的，用户在申请空间的时候应当申请足够的以供变动的空间。
        if ( bytes.size() > size() ) {
            pline() << "bytes size out payload..., create more...";
            //unlock();
            return;
        }
        //memcpy ( data(), bytes.constData(), bytes.size() );
        //unlock();
    }

    //需要重写，实现把共享内存块解压到局部变量。（注释部分。）
    //这个函数保证从共享内存读取。
    virtual void parser() {
        //lock();
        QByteArray bytes;
        bytes.resize ( size() );
        //memcpy ( bytes.data(), data(), size() );

        //user data struct
        //bytes >> a;

        //unlock();
    }

    /*以下函数提供操作方便。*/

    QByteArray readShortString ( QByteArray& bytes ) {
        quint16 s0;
        QByteArray str;
        bytes >> s0;
        str.resize ( s0 );
        bytes >> str;
        return str;
    }

    void writeShortString ( QByteArray& bytes, QByteArray& shortString ) {
        quint16 s0 = shortString.size();
        bytes << s0;
        bytes << shortString;
    }

    QByteArray readString ( QByteArray& bytes ) {
        quint32 s0;
        QByteArray str;
        bytes >> s0;
        str.resize ( s0 );
        bytes >> str;
        return str;
    }

    void writeString ( QByteArray& bytes, QByteArray& shortString ) {
        quint32 s0 = shortString.size();
        bytes << s0;
        bytes << shortString;
    }

signals:

public slots:

private:
    /**
     * example
     * quint32 a;
     * QByteArray b;
     * quint8 c;
     */
};

#include <qqtmessage.h>
#include <qqtprotocol.h>
#include <qqtlocalclient.h>

class QQtNamedPipeClientMessage : public QQtMessage
{
    Q_OBJECT
public:
    explicit QQtNamedPipeClientMessage ( QObject* parent = nullptr );
    ~QQtNamedPipeClientMessage();

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

QDebug& operator << ( QDebug&, const QQtNamedPipeClientMessage& msg );

//业务层总是用这个协议工作，读来到的，写出去的。
class QQtNamedPipeClientProtocol : public QQtProtocol
{
    Q_OBJECT
public:
    explicit QQtNamedPipeClientProtocol ( QObject* parent = nullptr );
    ~QQtNamedPipeClientProtocol();

    //没连接上：创建Server，发送I Create you (0x0a). Server回复，I Accept you (0x0a)。
    //连接上了，发送I Find you (0x0b)。Server回复，存在Server (0x0b)，告诉上层，关闭程序。

    //收到外部发来的很多命令，处理一下告诉业务层干点什么。
    void recvCommand0x0a ( const QQtNamedPipeClientMessage& msg );
    void recvCommand0x0b ( const QQtNamedPipeClientMessage& msg );
    void sendCommand0x0a();
    void sendCommand0x0b();

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

#include <qqtprotocolmanager.h>
#include <qqtlocalserver.h>

class QQtNamedPipeServerMessage : public QQtMessage
{
    Q_OBJECT
public:
    explicit QQtNamedPipeServerMessage ( QObject* parent = nullptr );
    ~QQtNamedPipeServerMessage();

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

QDebug& operator << ( QDebug&, const QQtNamedPipeServerMessage& msg );


//业务层总是用这个协议工作，读来到的，写出去的。
class QQtNamedPipeServerProtocol : public QQtProtocol
{
    Q_OBJECT
public:
    explicit QQtNamedPipeServerProtocol ( QObject* parent = nullptr );
    ~QQtNamedPipeServerProtocol();

    //收到外部发来的很多命令，处理一下告诉业务层干点什么。
    void recvCommand0x0a ( const QQtNamedPipeServerMessage& msg );
    void recvCommand0x0b ( const QQtNamedPipeServerMessage& msg );
    void sendCommand0x0a();
    void sendCommand0x0b();

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

#endif // QQTNAMEDPIPE_H
