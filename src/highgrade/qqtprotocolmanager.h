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
 */
class QQTSHARED_EXPORT QQtProtocolManager : public QObject
{
    Q_OBJECT
public:
    explicit QQtProtocolManager ( QObject* parent = 0 );
    virtual ~QQtProtocolManager();

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
     * 这个用户在生成ProtocolManager对象的时候，需要注册一下自己的协议类，需要调用一次。
     * 注意：
     * registerProtocol<QQtXXXProtocol>("QQtXXXProtocol"); ... 如此
     */
    template <typename T>
    void registerProtocol () {
        //pline() << typeid ( T ) << typeid ( T ).name();
        mProtocolName = T::staticMetaObject.className();
        QQtObjectFactory::registerObject<T>();
    }

    /**
     * @brief createProtocol
     * 这个函数给QQtSocketServer用的，不是给用户用的。
     * 用于生成用户协议对象实例。
     * @param protocolTypeName
     * @return
     */
    QQtProtocol* createProtocol () {
        //如果不能生成，根本不返回，而是崩溃。
        QQtProtocol* p0 = ( QQtProtocol* ) QQtObjectFactory::createObject ( mProtocolName, this );
        //帮助Protocol给用户发数据。
        connect ( p0, SIGNAL ( notifyToProtocolManager ( const QQtProtocol*, const QQtMessage* ) ),
                  this, SIGNAL ( notifyToBusinessLevel ( const QQtProtocol*, const QQtMessage* ) ) );
        return p0;
    }

private:
    QByteArray mProtocolName;

#if 0
    /*
     * 建议：用户在继承类里的函数里直接调用[emit] write(...)
    */
Q_SIGNALS:
    qint64 write ( const QByteArray& );

public:
    /**
     * @brief 协议处理器
     * 这个处理器是给QQtTcpSocket用的，不是给客户用的。
     * @param Qt通讯口readAll()读到的bytes
     * @return
     */
    void translator ( const QByteArray& bytes );

    /*
     * 以下函数，用户必须继承下去，重写，need override
     */
protected:
    /**
     * @brief 最小包长
     * @return
     */
    inline virtual quint16 minlength() { return 0; }
    /**
     * @brief 最大包长
     * @return
     */
    inline virtual quint16 maxlength() { return 0xFFFF; }
    /**
     * @brief 语法解析器 从流中解析报文长度
     * @param 接收到的数据段
     * @return 按照协议解析到的数据长度 可用，继续接收，丢弃，粘包。
     */
    inline virtual quint16 splitter ( const QByteArray& ) { return 0; }
    /**
     * @brief 语义解析器
     * @param 数据包
     * @return 0 no dispatched(others) 1 dispatched(own)
     */
    inline virtual bool dispatcher ( const QByteArray& ) { return 0; }
#endif
};

#endif // QQTPROTOCOLMANAGER_H
