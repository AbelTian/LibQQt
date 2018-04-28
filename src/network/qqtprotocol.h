#ifndef QQTPROTOCOL_H
#define QQTPROTOCOL_H

#include <QObject>
#include <qqt-local.h>
#include "qqtmessage.h"
#include "qqtcore.h"

/**
 * @brief The QQtProtocol class
 * very good ideology and impliment
 *
 * 特点
 * C-P
 * ClientSocket Protocol 1:1的关系
 */
class QQTSHARED_EXPORT QQtProtocol : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit QQtProtocol ( QObject* parent = 0 ) : QObject ( parent ) {

    }
    virtual ~QQtProtocol() {

    }

    /*
     * 建议：用户在继承类里的函数里直接调用[emit] write(...)
    */
Q_SIGNALS:
    qint64 write ( const QByteArray& );
    /*
     * 以下函数，用户必须继承下去，重写，need override
     */
public:
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
     * /.../quint16 size/.../.../...
     * @param 接收到的数据段
     * @return 按照协议解析到的数据长度 可用，继续接收，丢弃，粘包。
     */
    inline virtual quint16 splitter ( const QByteArray& ) { return 0; }
    /**
     * @brief 语义解析器
     * /.../quint16 size/.../QByteArray data/.../
     * @param 数据包
     * @return 0 no dispatched(others) 1 dispatched(own)
     */
    inline virtual bool dispatcher ( const QByteArray& ) { return 0; }

signals:
    /**
     * @brief notifyToProtocolManager
     * 为服务器功能的ProtocolManager添加的，用户不必管理，必要时调用。
     *
     * 用户继承下去的协议里，在dispatcher的recv函数里，如果必要把收到的信息传递给上层，
     * 那么通过emit notifyToProtocolManager，传递给ProtocolManager
     * BusinessLevel对这些接收到的信息感兴趣，
     * 那么通过连接ProtocolManager的notifyToBusinessLevel对拿到的信息进行处理，会包括协议句柄，使用户方便写回客户。
     * @param self
     * @param message
     */
    void notifyToProtocolManager ( const QQtProtocol* self, const QQtMessage* message );
};

#endif // QQTPROTOCOL_H
