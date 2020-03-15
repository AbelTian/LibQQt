#ifndef QQTFINDSERVERMANAGER_H
#define QQTFINDSERVERMANAGER_H

#include <QObject>
#include <QHostAddress>

#include <qqtprotocol.h>
#include <qqtstandardprotocol.h>
#include <qqtprotocolmanager.h>

#include <qqtudpclient.h>
#include <qqtudpserver.h>

#include <qqt-local.h>

/**
 * @brief The QQtFindServerManager class
 * 在局域网查找存在的服务器。
 * CLIENT使用这个类。
 */
class QQtFindServerProtocol;
class QQTSHARED_EXPORT QQtFindServerManager : public QObject
{
    Q_OBJECT

public:
    explicit QQtFindServerManager ( QObject* parent = 0 )
        : QObject ( parent ) {}
    virtual ~QQtFindServerManager() {}

    //准备查找服务器，本地发送、接收信息的端口
    void setLocalListenPort ( int port = 4407 );
    //准备查找服务器，QQtBeServerManager监听的端口
    void setServerListenPort ( int port = 4408 );

    //客户端主动，发起查找，只要BeServer存在，就能找到。
    void sendFindServerRequest();

signals:
    void signalFindServer ( QString ip, int port );

protected:

private:

};

/**
 * @brief The QQtBeServerManager class
 * 在局域网中被查找，并告知客户端服务器的节点信息。
 * SERVER用。
 */
class QQtBeServerProtocol;
class QQtBeServerProtocolManager;
class QQTSHARED_EXPORT QQtBeServerManager : public QObject
{
    Q_OBJECT
public:
    explicit QQtBeServerManager ( QObject* parent = 0 );
    virtual ~QQtBeServerManager();

    //准备查找服务器，QQtBeServerManager监听的端口
    void setServerListenPort ( int port = 4408 ) {
        mLocalPort = port;
    }

    //查找服务器成功，告诉客户端的服务器IP、端口。
    void setTellClientServerAddress ( QString ip, int port = 5010 );

    //主动发起告知客户端。
    void sendTellClientServerAddress();

private:
    QQtBeServerProtocolManager* m0;
    QQtUdpServer* s0;

    int mLocalPort;
};



/**
 * @brief The QQtBeServerProtocolManager class
 */
class QQTSHARED_EXPORT QQtBeServerProtocolManager : public QQtProtocolManager
{
    Q_OBJECT
public:
    explicit QQtBeServerProtocolManager ( QObject* parent = 0 );
    virtual ~QQtBeServerProtocolManager();

    void setLocalIpPort ( QString ip, int port );

private:
    QString mIP;
    int mPort;

    // QQtProtocolManager interface
public:
    virtual QQtProtocol* createProtocol() override;
};

enum MsgSecName
{
    CMD_TYPE = 0,
    CMD_CONTENT,
    CMD_MAX
};

/**
 * @brief The QQtBeServerProtocol class
 * 1. 支持客户端查找服务器
 * 2. 支持服务器主动发布自己的IP、端口
 * server
 *
 * cmd_type: "find_server", "server_ack"
 *
 * [0] "find_server"
 *     ...
 *
 * [0] "server_ack"
 * [1]
 *     ["ip"]
 *     ["port"]
 */
class QQTSHARED_EXPORT QQtBeServerProtocol : public QQtStandardProtocol
{
    Q_OBJECT

public:
    explicit QQtBeServerProtocol ( QObject* parent = 0 );
    virtual ~QQtBeServerProtocol();

    void setLocalIpPort ( QString ip, int port );
    void sendBeServerMessage();

protected:

private:

signals:

    // QQtStandardProtocol interface
public:
    virtual void recvMessage ( const QQtDataSerialization& data ) override;

private:
    QString mIP;
    int mPort;
};

/**
 * @brief The QQtFindServerProtocol class
 * 1. 支持客户端查找服务器
 * 2. 支持服务器主动发布自己的IP、端口
 * client
 *
 * cmd_type
 * [0] "find_server", "server_ack"
 *
 * [0] "find_server"
 *     ...
 *
 * [0] "server_ack"
 * [1]
 *     ["ip"]
 *     ["port"]
 */
class QQTSHARED_EXPORT QQtFindServerProtocol : public QQtStandardProtocol
{
    Q_OBJECT

public:
    explicit QQtFindServerProtocol ( QObject* parent = 0 );
    virtual ~QQtFindServerProtocol();

    void sendFindServerRequest();
protected:

private:

signals:
    void signalFindServer ( QString ip, int port );

    // QQtStandardProtocol interface
public:
    virtual void recvMessage ( const QQtDataSerialization& data ) override;

private:
    QString mIP;
    int mPort;
};

#endif // QQTFINDSERVERMANAGER_H

