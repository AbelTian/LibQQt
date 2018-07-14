#ifndef QQTNAMEDPIPE_H
#define QQTNAMEDPIPE_H

#include <qqt-local.h>
#include <qqtcore.h>

#include <qlocalsocket.h>
#include <qlocalserver.h>

class QQtNamedPipeClientProtocol;
class QQtLocalClient;

class QQtNamedPipeServerProtocolManager;
class QQtLocalServer;

QQtLocalClient* QQtNamedPipeClientInstance ( QQtNamedPipeClientProtocol*& protocol, QObject* parent = 0 );
QQtLocalServer* QQtNamedPipeServerInstance ( QQtNamedPipeServerProtocolManager*& protocol, QObject* parent = 0 );

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
 */
class QQTSHARED_EXPORT QQtNamedPipe : public QObject
{
    Q_OBJECT
public:
    explicit QQtNamedPipe ( const QString& key, QObject* parent = Q_NULLPTR );
    ~QQtNamedPipe();

    virtual bool initializer();

    void write ( const QByteArray& bytes );

    QByteArray read ( int size );

public slots:
    void slotSocketStateChanged ( QLocalSocket::LocalSocketState );
    void slotConnectSuccess();
    void slotConnectFail();

signals:

public slots:

private:

protected:
    virtual bool create();
    virtual bool attach();
private:
    QQtNamedPipeClientProtocol* p0;
    QQtLocalClient* c0;

    QQtNamedPipeServerProtocolManager* pm0;
    QQtLocalServer* s0;

    QString mKey;

    bool hasServer;
    bool bAccepted;

    QEventLoop* eLoop;
};


#endif // QQTNAMEDPIPE_H
