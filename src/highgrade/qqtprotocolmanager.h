#ifndef QQTPROTOCOLMANAGER_H
#define QQTPROTOCOLMANAGER_H

#include <QObject>
#include <qqt-local.h>
#include "qqtmessage.h"
#include "qqtcore.h"

/**
 * @brief The QQtProtocolManager class
 * very good ideology and impliment
 */
class QQTSHARED_EXPORT QQtProtocolManager : public QObject
{
    Q_OBJECT
public:
    explicit QQtProtocolManager ( QObject* parent = 0 );
    virtual ~QQtProtocolManager();

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
};

#endif // QQTPROTOCOLMANAGER_H
