#ifndef CEDIANUDPMESSAGE_H
#define CEDIANUDPMESSAGE_H

#include <qqtmessage.h>
#include <qqtcore.h>
#include <QDebug>

class CedianUdpMessage : public QQtMessage
{
    Q_OBJECT
public:
    explicit CedianUdpMessage(QObject *parent = nullptr);
    virtual ~CedianUdpMessage() {}

    /*用函数把成员变量公开出来*/
    //qint8 getSite(void) { return mSite; }

    /*用函数设置成员变量*/
    //void setSite(qint8 mSite) { this->mSite = mSite; }

    /*比较简便的处理成员变量的方式。读写都用这个函数。*/
    //获取mVAA
    qreal& getVAA() { return mVAA; }
    const qreal& getVAA() const { return mVAA; }
    //获取mVAB
    qreal& getVAB() { return mVAB; }
    const qreal& getVAB() const { return mVAB; }
    //获取mVAC
    qreal& getVAC() { return mVAC; }
    const qreal& getVAC() const { return mVAC; }
    //获取mVPA
    qreal& getVPA() { return mVPA; }
    const qreal& getVPA() const { return mVPA; }
    //获取mVPB
    qreal& getVPB() { return mVPB; }
    const qreal& getVPB() const { return mVPB; }
    //获取mVPC
    qreal& getVPC() { return mVPC; }
    const qreal& getVPC() const { return mVPC; }
    //获取mIAA
    qreal& getIAA() { return mIAA; }
    const qreal& getIAA() const { return mIAA; }
    //获取mIAB
    qreal& getIAB() { return mIAB; }
    const qreal& getIAB() const { return mIAB; }
    //获取mIAC
    qreal& getIAC() { return mIAC; }
    const qreal& getIAC() const { return mIAC; }
    //获取mIPA
    qreal& getIPA() { return mIPA; }
    const qreal& getIPA() const { return mIPA; }
    //获取mIPB
    qreal& getIPB() { return mIPB; }
    const qreal& getIPB() const { return mIPB; }
    //获取mIPC
    qreal& getIPC() { return mIPC; }
    const qreal& getIPC() const { return mIPC; }
    //获取mFA
    qreal& getFA() { return mFA; }
    const qreal& getFA() const { return mFA; }
    //获取mFB
    qreal& getFB() { return mFB; }
    const qreal& getFB() const { return mFB; }
    //获取mFC
    qreal& getFC() { return mFC; }
    const qreal& getFC() const { return mFC; }
    //获取mDateTime
    QString& getDateTime() { return mDateTime; }
    const QString& getDateTime() const { return mDateTime; }
    //获取mBuffer
    quint8& getBuffer() { return mBuffer; }
    const quint8& getBuffer() const { return mBuffer; }

    QByteArray& getQbaVAA() { return mqbaVAA; }
    const QByteArray& getQbaVAA() const { return mqbaVAA; }
    QByteArray& getQbaVAB() { return mqbaVAB; }
    const QByteArray& getQbaVAB() const { return mqbaVAB; }
    QByteArray& getQbaVAC() { return mqbaVAC; }
    const QByteArray& getQbaVAC() const { return mqbaVAC; }
    QByteArray& getQbaVPA() { return mqbaVPA; }
    const QByteArray& getQbaVPA() const { return mqbaVPA; }
    QByteArray& getQbaVPB() { return mqbaVPB; }
    const QByteArray& getQbaVPB() const { return mqbaVPB; }
    QByteArray& getQbaVPC() { return mqbaVPC; }
    const QByteArray& getQbaVPC() const { return mqbaVPC; }
    QByteArray& getQbaIAA() { return mqbaIAA; }
    const QByteArray& getQbaIAA() const { return mqbaIAA; }
    QByteArray& getQbaIAB() { return mqbaIAB; }
    const QByteArray& getQbaIAB() const { return mqbaIAB; }
    QByteArray& getQbaIAC() { return mqbaIAC; }
    const QByteArray& getQbaIAC() const { return mqbaIAC; }
    QByteArray& getQbaIPA() { return mqbaIPA; }
    const QByteArray& getQbaIPA() const { return mqbaIPA; }
    QByteArray& getQbaIPB() { return mqbaIPB; }
    const QByteArray& getQbaIPB() const { return mqbaIPB; }
    QByteArray& getQbaIPC() { return mqbaIPC; }
    const QByteArray& getQbaIPC() const { return mqbaIPC; }
    QByteArray& getQbaFA() { return mqbaFA; }
    const QByteArray& getQbaFA() const { return mqbaFA; }
    QByteArray& getQbaFB() { return mqbaFB; }
    const QByteArray& getQbaFB() const { return mqbaFB; }
    QByteArray& getQbaFC() { return mqbaFC; }
    const QByteArray& getQbaFC() const { return mqbaFC; }
    QByteArray& getQbaDateTime() { return mqbaDateTime; }
    const QByteArray& getQbaDateTime() const { return mqbaDateTime; }
    QByteArray& getQbaBuffer() { return mqbaBuffer; }
    const QByteArray& getQbaBuffer() const { return mqbaBuffer; }
signals:

public slots:

    // QQtMessage interface
public:
    virtual void parser(const QByteArray &) override;
    virtual void packer(QByteArray &) const override;

private:
    QByteArray mqbaVAA;
    QByteArray mqbaVAB;
    QByteArray mqbaVAC;
    QByteArray mqbaVPA;
    QByteArray mqbaVPB;
    QByteArray mqbaVPC;
    QByteArray mqbaIAA;
    QByteArray mqbaIAB;
    QByteArray mqbaIAC;
    QByteArray mqbaIPA;
    QByteArray mqbaIPB;
    QByteArray mqbaIPC;
    QByteArray mqbaFA;
    QByteArray mqbaFB;
    QByteArray mqbaFC;
    QByteArray mqbaDateTime;
    QByteArray mqbaBuffer;

    qreal mVAA;
    qreal mVAB;
    qreal mVAC;
    qreal mVPA;
    qreal mVPB;
    qreal mVPC;
    qreal mIAA;
    qreal mIAB;
    qreal mIAC;
    qreal mIPA;
    qreal mIPB;
    qreal mIPC;
    qreal mFA;
    qreal mFB;
    qreal mFC;
    QString mDateTime;
    quint8 mBuffer;
};

QDebug operator<<(QDebug dbg, const CedianUdpMessage &c);

#endif // CEDIANUDPMESSAGE_H
