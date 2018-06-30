#ifndef QQTNFCCLIENT_H
#define QQTNFCCLIENT_H

#include <QObject>
#include <QtNfc>
#include "qqtprotocol.h"
#include "qqtcore.h"
#include "qqt-local.h"

/**
 * @brief The QQtNfcClient class
 * NfcClient既可以作为Client，也可以作为Server，它是无连接的，基于数据报的协议。
 * 在继承自QQtProtocol的xxxProtocol里，直接使用QNdefMessage就可以，不必使用QQtMessage强制转换。
 * 这里发送和接收都是QByteArray，可以和QNdefMessage之间进行直接转换。消息没有ID，用户自行分辨Message。
 *
 * 这个Client是个raw客户端，数据全都在Message里的各个Record的PayLoad里，
 * 而PayLoad里的数据格式，用户自行编订。
 */
class QQTSHARED_EXPORT QQtNfcClient : public QNearFieldTarget
{
    Q_OBJECT
public:
    explicit QQtNfcClient ( QObject* parent = Q_NULLPTR );
    virtual ~QQtNfcClient() {}

    /**
     * Target信息
     */

    /**
     * 协议安装器
     */
    void installProtocol ( QQtProtocol* stack );
    void uninstallProtocol ( QQtProtocol* stack );
    QQtProtocol* installedProtocol();

signals:
    //readOnly
    //用户接收这个信号，用QNdefMessage fromByteArray获取Message
    void readyRead ( const QByteArray& bytes );

public slots:

signals:

private slots:
    void errorOccured ( QNearFieldTarget::Error, const QNearFieldTarget::RequestId& );

protected slots:
    void readyReadNdefMessage ( const QNdefMessage& );

public slots:
    void slotWriteData ( const QByteArray& bytes );

protected:
    /**
     * @brief translator
     * 用于拆分和分发数据报
     * @param bytes
     */
    virtual void translator ( const QByteArray& bytes );

private:
    QQtProtocol* m_protocol;

    // QNearFieldTarget interface
public:
    virtual QByteArray uid() const override { return mUid; }
    virtual Type type() const override { return mType; }
    virtual AccessMethods accessMethods() const override { return mAccessMethods; }

    virtual void setUid ( QByteArray uid ) { mUid = uid; }
    virtual void setType ( Type type ) { mType = type; }
    virtual void setAccessMethods ( AccessMethods methods ) { mAccessMethods = methods; }
protected:

private:
    //这三个应用于targetDetected。
    QByteArray mUid;
    Type mType;
    AccessMethods mAccessMethods;
};

#endif // QQTNFCCLIENT_H
