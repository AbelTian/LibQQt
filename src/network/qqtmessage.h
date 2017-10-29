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
    explicit QQtMessage(QObject* parent = 0) : QObject(parent) {}
    virtual ~QQtMessage() {}
public:
    /**
     * @brief 从流中解析报文
     * @param m
     * @param l
     */
    virtual void parser(const QByteArray&) {}
    /**
     * @brief 将报文组装为流
     * @param l
     * @param m
     */
    virtual void packer(QByteArray&) {}
    /**
     * @brief 最小包长
     * @return
     */

signals:

public slots:

private:
    //example
    //quint32 a;
    //QByteArray b;
    //quint8 c;
};


#endif // QQTMESSAGE_H
