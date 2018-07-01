#ifndef QQTPROTOCOLMANAGER_H
#define QQTPROTOCOLMANAGER_H

#include <QObject>
#include "qqtmessage.h"
#include "qqtprotocol.h"
#include <qqtobjectmanager.h>

#include "qqtcore.h"
#include <qqt-local.h>

/**
 * @brief The QQtProtocolManager class
 * very good ideology and impliment
 * 用于管理多个Protocol实例
 * 用户实现的协议注册到这里，当协议当中有消息需要告知业务层，从这里告知。
 *
 * 注释：
 * 讲解notify过程，
 * QQtSocketServer，管理QQtSocketClient句柄
 * QQtProtocolManager，管理QQtProtocol句柄
 * cli -> proto, dispatcher, recvFunc, notifyToProtocolManager,
 * protoManager -> businessLevel, 完全信号传递。
 *
 * 关于识别Protocl，
 * 用户的客户端可以发个人信息上来，Protocol保存在句柄内部。
 *
 * 定位：
 * 只可以安装同一种类型的句柄。
 * 可以通过多次注册改变内部的句柄数量。
 *
 * 模型：
 * 业  PM  S           业
 * 务  |   |           务
 * 层  P - C :: C - P  层
 */
class QQTSHARED_EXPORT QQtProtocolManager : public QObject
{
    Q_OBJECT
public:
    explicit QQtProtocolManager ( QObject* parent = 0 );
    virtual ~QQtProtocolManager();

    //获取Protocol列表
    //这里列举的函数是给BusinessLevel用的，Protocol里面不要用
    //findProtocolInstanceByXXX(...);
    //findClientInfoByProtocolInstance(Protocol);
    //sendMessageToProtocolInstance(Protocol, Message);
    //sendMessageToAllProtocolInstance(...);

signals:
    /**
     * @brief notifyToUser
     * 这个信号是给用户的，用户可以接收下来，转换为自己的协议使用。注释：如果必要。
     * 用户使用这个ProtocolManager，Protocol需要提交给用户处理的命令，提交到这里，在这里提交给用户。
     * ProtocolManager -> BusinessLevel
     * @param protocol
     * @param message
     */
    void notifyToBusinessLevel ( const QQtProtocol* protocol, const QQtMessage* message );

public:
    /**
     * 注册用户协议类型
     * 模板函数
     * 用于ProtocolManager内部生成用户协议实例。
     * 这个用户在生成ProtocolManager对象的时候，需要注册一下自己的协议类，需要调用至少一次。
     *
     * 注意：
     * registerProtocol<QQtXXXProtocol>(1); //这样只预备了一个句柄。
     * 可以根据Protocol ObjectName区分Protocol 或者metaObject()->className()
     *
     * 用法：
     * 用户连接remanentProtocolChanged，当发现小于某个约束数目的时候，就调用这个函数进行注册，
     * 注册用户认为合理的数量即可。
     * 如果客户端数量存在上限，调用一次这个函数就可以了，不必检测剩余句柄数目。默认一次创建1024个句柄。
     */
    template <typename T>
    bool registerProtocol ( int count = 1024 ) {
        for ( int i = 0; i < count; i++ ) {
            QQtProtocol* p0 = new T ( this );
            m_protocol_list.push_back ( p0 );
        }
        return true;
    }

signals:
    //内部每次协议句柄列表发生变动都会发射这个信号。
    //剩余的可用句柄数目
    void remanentProtocolChanged ( int num );
    void remainingProtocolChanged ( int num );

    /**
     * 以下和用户无关
     */
public:
    /**
     * @brief createProtocol
     * 创建一个Protocol句柄，开始使用。
     *
     * 这个函数给QQtSocketServer用的，不是给用户用的。
     * 用于生成用户协议对象实例。
     *
     * @param protocolTypeName
     * @return
     */
    QQtProtocol* createProtocol ();
    /**
     * 使用完，删除。
     *
     * Protocol的deattach和这个功能不同，它表示使用状态切换为不使用。
     * 而deleteProtocol表示，这个句柄要删除了。
     * 如果只是deattach，那么这个句柄重新被attach以后，用户把内部的变量都reset了吗？其实如果reset了，不必要删除句柄。
     * 但是，内部实现的，支持reset，在attach的时候调用。可是没有太多作用，因为，这个句柄在不用了的时候会在这里被delete掉。
     *
     * 这个机制会导致初始注册了一些句柄以后，使用使用就变少了，逐渐的就用完了。所以必须频繁根据句柄数量变动进行注册。
     * 经过考虑，我决定不删除句柄，用户继承QQtProtocol句柄的时候override init函数初始化句柄，可以避免句柄逐渐变少引起的频繁注册。
     * Protocol的init函数，只需要在必要初始化句柄的时候重写。
     *
     * 内部没有对QList加锁，所以不要movetothread里用。
     */
    void deleteProtocol ( QQtProtocol* stack );
protected:
    QQtProtocol* findDetachedInstance();
private:
    QList<QQtProtocol*> m_protocol_list;
};

#endif // QQTPROTOCOLMANAGER_H
