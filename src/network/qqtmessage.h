#ifndef QQTMESSAGE_H
#define QQTMESSAGE_H

#include <QObject>
#include <qqt-local.h>

/**
 * @brief 语法类 定义报文格式
 */
class QQTSHARED_EXPORT QQtMessage : public QObject
{
    Q_OBJECT
public:
    inline explicit QQtMessage(QObject* parent = 0) : QObject(parent) {}
    inline virtual ~QQtMessage() {}
public:
    /**
     * @brief 从流中解析报文
     * 这个函数会更改局部变量
     * @param m
     * @param l
     */
    inline virtual void parser(const QByteArray&) {}
    /**
     * @brief 将报文组装为流
     * 这个函数不会更改局部变量
     * @param l
     * @param m
     */
    inline virtual void packer(QByteArray&) const {}
    /**
     * @brief 最小包长
     * @return
     */

signals:

public slots:

private:
    /**
     * example
     * quint32 a;
     * QByteArray b;
     * quint8 c;
     */
};


#endif // QQTMESSAGE_H
