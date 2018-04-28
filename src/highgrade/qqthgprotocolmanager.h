#ifndef QQTHGPROTOCOLMANAGER_H
#define QQTHGPROTOCOLMANAGER_H

#include <QObject>
#include "qqtmessage.h"
#include "qqthgprotocol.h"
#include <qqtobjectmanager.h>

#include "qqtcore.h"
#include <qqt-local.h>

/**
 * @brief The QQtHgProtocolManager class
 * very good ideology and impliment
 * 用于管理多个Protocol实例
 * 用户实现的协议注册到这里，当协议当中有消息需要告知业务层，从这里告知。
 *
 * 注释：
 * 讲解notify过程，
 * QQtSocketServer，管理QQtSocketClient句柄
 * QQtHgProtocolManager，管理QQtHgProtocol句柄
 * cli -> proto, dispatcher, recvFunc, notifyToProtocolManager,
 * protoManager -> businessLevel, 完全信号传递。
 *
 * 关于识别Protocl，
 * 这个Manager可以安装多个Protocol，并且用于多个客户端
 * Multi-protocol，Multi-client。
 * Multi-message。
 *
 * 注意：
 * 多客户端，单协议，比较多见。
 * 单客户端，多协议，不多见。
 * 单客户端，单协议，最多使用。
 * 多客户端，多协议，很晕眩。
 *
 * 这个类的信号主要用于，业务层感兴趣的信息发送到上层。
 */
class QQTSHARED_EXPORT QQtHgProtocolManager : public QObject
{
    Q_OBJECT
public:
    explicit QQtHgProtocolManager ( QObject* parent = 0 );
    virtual ~QQtHgProtocolManager();

    //这里列举的函数是给BusinessLevel用的，Protocol里面不要用
    //findProtocolInstanceByXXX(...);
    //findClientInfoByProtocolInstance(Protocol);
    //sendMessageToProtocolInstance(Protocol, Message);
    //sendMessageToAllProtocolInstance(...);

signals:
    /**
     * @brief notifyToUser
     * 这个信号是给用户的，用户可以接收下来，转换为自己的协议使用。注释：如果必要。一般在协议里就处理完了。
     * 用户使用这个ProtocolManager，Protocol需要提交给用户处理的命令，提交到这里，在这里提交给用户。
     * ProtocolManager -> BusinessLevel
     * 某个用户 安装的某个协议 发来某个消息
     * @param client
     * @param protocol
     * @param message
     */
    void notifyToBusinessLevel ( const QAbstractSocket* client,  const QQtHgProtocol* protocol, const QQtMessage* message );
    /**
     * @brief sendMessageToClient
     * 这个信号是给用户的，
     * 发送给某个用户，按照某个协议，发送的消息。
     * @param client
     * @param protocol
     * @param message
     */
    void sendMessageToClientSocket ( const QAbstractSocket* client,  const QQtHgProtocol* protocol,
                                     const QQtMessage* message );

public:
    /**
     * 允许安装多个协议
     * client需要解析的协议都在这里，一个client会进入这里的每一个协议。
     */
    void installProtocol ( QQtHgProtocol* stack );
    void uninstallProtocol ( QQtHgProtocol* stack );
    QList<QQtHgProtocol*>& installedProtocol();

private:
    QList<QQtHgProtocol*> mProtoList;
};

#endif // QQTHGPROTOCOLMANAGER_H
