#ifndef QQTHGPROTOCOL_H
#define QQTHGPROTOCOL_H

#include <QObject>
#include <qqt-local.h>
#include "qqtcore.h"
#include "qqtmessage.h"

/**
 * @brief The QQtHgProtocol class
 * very good ideology and impliment
 */
class QQTSHARED_EXPORT QQtHgProtocol : public QObject
{
    Q_OBJECT
public:
    explicit QQtHgProtocol ( QObject* parent = 0 );
    virtual ~QQtHgProtocol();

signals:
    /**
     * @brief notifyToHgProtocolManager
     * 为服务器功能的ProtocolManager添加的，用户不必管理，必要时调用。
     *
     * 用户继承下去的协议里，在dispatcher的recv函数里，如果必要把收到的信息传递给上层，
     * 那么通过emit notifyToProtocolManager，传递给ProtocolManager
     * BusinessLevel对这些接收到的信息感兴趣，
     * 那么通过连接ProtocolManager的notifyToBusinessLevel对拿到的信息进行处理，会包括协议句柄，使用户方便写回客户。
     * 用户在子类主动调用
     * @param client
     * @param self
     * @param message
     */
    void notifyToHgProtocolManager ( const QAbstractSocket* client, const QQtHgProtocol* self, const QQtMessage* message );

Q_SIGNALS:
    /**
     * 群发
     * 这个write会发给所有的client instance
    */
    qint64 write ( const QByteArray& );
    /**
     * 单发
     */
    qint64 writeToClient ( const QAbstractSocket* client, const QByteArray& );
    /**
     * @brief notifyForDispatcher
     * 这是个上报报文的信号，在每次dispatcher的时候会自动调用。
     * 上报的一段字节序，正好一段报文。
     * @param client
     * @param bytes
     */
    void notifyForDispatcher ( const QAbstractSocket* client, const QByteArray& bytes );
    /*
     * 以下函数，用户必须继承下去，重写，need override
     */
protected:
    /**
     * @brief 最小包长
     * @return
     */
    inline virtual quint16 minlength() {
        return 0x00;
    }
    /**
     * @brief 最大包长
     * @return
     */
    inline virtual quint16 maxlength() {
        return 0x07FF;
    }
    /**
     * @brief 语法解析器 从流中解析报文长度
     * 不同用户的协议，这个，这一个协议，切分方式是一样的。
     * @param 接收到的数据段
     * @return 按照协议解析到的数据长度 可用，继续接收，丢弃，粘包。
     */
    inline virtual quint16 splitter ( const QByteArray& bytes ) { return 0; }
    /**
     * @brief 语义解析器
     * 不同用户的信息，在这里会被区分开。
     * @param 数据包
     * @return
     */
    inline virtual void dispatcher ( const QAbstractSocket* client, const QByteArray& bytes ) { return; }

    /*以下和用户无关*/
public:
    /**
     * @brief 协议处理器
     * 这个处理器是给HgSocket用的，不是给客户用的。
     * ProtocolManager，安装了这个协议，需要用户句柄。
     * virtual是为QQt内部的协议提供的。
     * @param Qt通讯口readAll()读到的bytes
     * @return
     */
    virtual void translator ( const QAbstractSocket* client, const QByteArray& bytes ) { return; }
    /**
     * 用于给Client提供独立的IOBuffer。
     * 用于流式传输协议，
     * 数据报式传输协议不需要。
     * 给HgSocket用，用户无关
     */
    void createClientBuffer ( const QAbstractSocket* client );
    void deleteClientBuffer ( const QAbstractSocket* client );
    QMap<QAbstractSocket*, QByteArray>& clientBuffer() { return mClientBuffer; }
private:
    QMap<QAbstractSocket*, QByteArray> mClientBuffer;
};

#endif // QQTHGPROTOCOL_H
