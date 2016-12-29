#ifndef QQTMESSAGE_H
#define QQTMESSAGE_H

#include <QObject>


/**
 * @brief 语法类 定义报文格式
 */
class QQTMessage : public QObject
{
    Q_OBJECT
public:
    explicit QQTMessage(QObject *parent = 0);

public:
    /**
     * @brief 从流中解析报文
     * @param m
     * @param l
     */
    virtual void parser(const QByteArray &l) = 0;
    /**
     * @brief 将报文组装为流
     * @param l
     * @param m
     */
    virtual void packer(QByteArray& l) = 0;
    /**
     * @brief 最小包长
     * @return
     */

signals:

public slots:

private:
};


#endif // QQTMESSAGE_H
