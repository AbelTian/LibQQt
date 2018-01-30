#ifndef KONGZHIQIUDPMESSAGE_H
#define KONGZHIQIUDPMESSAGE_H

#include <qqtmessage.h>
#include <qqtcore.h>

class KongzhiqiUdpMessage : public QQtMessage
{
    Q_OBJECT
public:
    explicit KongzhiqiUdpMessage(QObject *parent = nullptr);
    virtual ~KongzhiqiUdpMessage() {}
    /*比较简便的处理成员变量的方式。读写都用这个函数。*/
    //获取mDesType的引用
    quint8& getDesType() { return mDesType; }
    const quint8& getDesType() const { return mDesType; }
    //获取mCommand的引用
    quint8& getCommand() { return mCommand; }
    const quint8& getCommand() const { return mCommand; }
signals:

public slots:

    // QQtMessage interface
public:
    virtual void parser(const QByteArray &) override;
    virtual void packer(QByteArray &command) const override;
private:
    quint8 mDesType;
    quint8 mCommand;
};

#endif // KONGZHIQIUDPMESSAGE_H
