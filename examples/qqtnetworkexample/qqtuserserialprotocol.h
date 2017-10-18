#ifndef QQTUSERSERIALPROTOCOL_H
#define QQTUSERSERIALPROTOCOL_H

#include "qqtserialmessage.h"
#include "qqtprotocol.h"
#include "qqtserialport.h"
#include "qqtbluetoothclient.h"

#define _SERIAL_HAND            0x0001
#define _SERIAL_HANDACK         0x8001
#define _SERIAL_CLOSE           0x0002
#define _SERIAL_CLOSEACK        0x8002
#define _SERIAL_WRITEDEVNO      0x0003
#define _SERIAL_WRITEDEVNOACK   0x8003
#define _SERIAL_READDEVNO       0x0004
#define _SERIAL_READDEVNOACK    0x8004
#define _SERIAL_WRITEPASS       0x0005
#define _SERIAL_WRITEPASSACK    0x8005
#define _SERIAL_READPASS        0x0006
#define _SERIAL_READPASSACK     0x8006
#define _SERIAL_EXCEPTIONACK    0x800F


class QQTHandupAck : public QQTSerialMessage
{
    Q_OBJECT
public:
    explicit QQTHandupAck(QObject *parent = 0) : QQTSerialMessage(parent){}

    void pack(QByteArray& l);
};

class QQTCloseAck : public QQTSerialMessage
{
    Q_OBJECT
public:
    explicit QQTCloseAck(QObject *parent = 0) : QQTSerialMessage(parent){}

    void pack(QByteArray &l);
};

class QQTWriteSerialNoAck : public QQTSerialMessage
{
    Q_OBJECT
public:
    explicit QQTWriteSerialNoAck(QObject *parent = 0) : QQTSerialMessage(parent){}

    void pack(QByteArray& l);
};

class QQTReadSerialNoAck : public QQTSerialMessage
{
    Q_OBJECT
public:
    explicit QQTReadSerialNoAck(QObject *parent = 0) : QQTSerialMessage(parent){}

    void pack(QByteArray& l);
};

class QQTWritePassAck : public QQTSerialMessage
{
    Q_OBJECT
public:
    explicit QQTWritePassAck(QObject *parent = 0) : QQTSerialMessage(parent){}

    void pack(QByteArray &l);
};


class QQTReadPassAck : public QQTSerialMessage
{
    Q_OBJECT
public:
    explicit QQTReadPassAck(QObject *parent = 0) : QQTSerialMessage(parent){}

    void pack(QByteArray &l);
};


class QQTExceptionAck : public QQTSerialMessage
{
    Q_OBJECT
public:
    explicit QQTExceptionAck(QObject *parent = 0) : QQTSerialMessage(parent){}

    void pack(QByteArray &l);
};

/**
 * @brief The QQTUserSerialProtocol class
 * 用户使用这个串口操作机器
 */
class QQTUserSerialProtocol : public QQTProtocol
{
    Q_OBJECT
public:
    explicit QQTUserSerialProtocol(QObject *parent = 0);
    ~QQTUserSerialProtocol();

signals:
    void sigSerialUnlock();

public slots:
    void recvHandup(const QByteArray& l);
    void sendHandupAck();
    void recvClose(const QByteArray& l);
    void sendCloseAck();
    void recvWriteSerialNumber(const QByteArray& l);
    void sendWriteSerialNumberAck();
    void recvReadSerial(const QByteArray& l);
    void sendReadSerialAck();
    void recvWritePassword(const QByteArray& l);
    void sendWritePasswordAck();
    void recvReadPassword(const QByteArray& l);
    void sendReadPasswordAck();
    void sendExceptionAck();


    // QQTProtocol interface
public:
    quint16 minlength() override;
    quint16 maxlength() override;
    quint16 splitter(const QByteArray &s) override;
    bool dispatcher(const QByteArray &m) override;

private:
    QQTSerialPort* s0;
};

QQTSerialPort* QQTUserSerialPortInstance(QObject* parent = 0, QString name = "/dev/tty0", QSerialPort::BaudRate = QSerialPort::Baud57600);
QQtBluetoothClient* QQtUserBluetoothClientInstance(QObject* parent = 0);
#endif // QQTUSERSERIALPROTOCOL_H
