#ifndef QQTPROTOCOL_H
#define QQTPROTOCOL_H

#include <QObject>
#include "qqtmessage.h"

class QQTProtocol : public QObject
{
    Q_OBJECT
public:
    explicit QQTProtocol(QObject *parent = 0);

signals:
    qint64 write(const QByteArray& l);

public:
    virtual quint16 minlength() {}
    /**
     * @brief 最大包长
     * @return
     */
    virtual quint16 maxlength() {}
    /**
     * @brief 语法解析器 从流中解析报文长度
     * @param 接收到的数据段
     * @return 按照协议解析到的数据长度 可用，继续接收，丢弃，粘包。
     */
    virtual quint16 splitter(const QByteArray &s){}
    /**
     * @brief 语义解析器
     * @param 数据包
     * @return 0 no dispatched(others) 1 dispatched(own)
     */
    virtual bool dispatcher(const QByteArray &m){}
};

#endif // QQTPROTOCOL_H
