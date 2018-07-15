#ifndef QQTNAMEDPIPE_H
#define QQTNAMEDPIPE_H

#include <qqt-local.h>
#include <qqtcore.h>

#include <qlocalsocket.h>
#include <qlocalserver.h>

class QQtNamedPipeClientProtocol;
class QQtNamedPipeClient;

class QQtNamedPipeServerProtocolManager;
class QQtNamedPipeServer;

QQtNamedPipeClient* QQtNamedPipeClientInstance ( QQtNamedPipeClientProtocol*& protocol, QObject* parent = 0 );
QQtNamedPipeServer* QQtNamedPipeServerInstance ( QQtNamedPipeServerProtocolManager*& protocol, QObject* parent = 0 );

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
 *
 * 升级：增加一个静态接口，外部创建Server
 *
 * 文件用于储存数据，管道不用于储存数据，而是作为一个通信设备的驱动，这个通信设备就是个管道。
 * QQtNamedPipeServer监控这个管道的读写，提交给业务层数据处理。
 * QQtNamedPipeClient往这个管道里面读写，读取和写入都允许进行。
 * QQtNamedPipePrivate实现了一个通信协议，包括read业务、write业务。
 * QQtNamedPipe使用这个协议，开放给用户接口。（也叫做Wrapper，没有这个wrapper管道读写不好实施呀，数据结构、通信架构都说不清楚。）
 *
 * Windows Timer和QEventLoop堵塞都存在问题，不支持。
 */
class QQTSHARED_EXPORT QQtNamedPipe : public QObject
{
    Q_OBJECT
public:
    explicit QQtNamedPipe ( const QString& key, QObject* parent = Q_NULLPTR );
    ~QQtNamedPipe();

    virtual bool initializer ( );
    void write ( const QByteArray& bytes );
    QByteArray read ( int size );

public slots:
    void slotConnectSuccess();
    void slotConnectFail();

signals:
    void signalConnectComeBack();
    void signalStartNamedPipeServer ( QQtNamedPipeServer* );
public slots:

private:

protected:
    virtual bool hasServer();
    virtual bool create();
    virtual bool attach();
    virtual bool setKey();
private:
    QQtNamedPipeClientProtocol* p0;
    QQtNamedPipeClient* c0;

    QQtNamedPipeServerProtocolManager* pm0;
    QQtNamedPipeServer* s0;

    QString mKey;

    bool mHasServer;
    bool bAccepted;

    QEventLoop* eLoop;
};

#endif // QQTNAMEDPIPE_H
