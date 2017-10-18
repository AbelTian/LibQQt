#include "qqtuserserialprotocol.h"
#include "qqtcore.h"
#include "qqt-qt.h"
#include "qqtbluetoothmanager.h"

void QQTWritePassAck::pack(QByteArray &l)
{
    setCmd(_SERIAL_WRITEPASSACK);
    translate();
    QQTSerialMessage::packer(l);
}


void QQTWriteSerialNoAck::pack(QByteArray &l)
{
    setCmd(_SERIAL_WRITEDEVNOACK);
    translate();
    QQTSerialMessage::packer(l);
}


void QQTHandupAck::pack(QByteArray &l)
{
    setCmd(_SERIAL_HANDACK);
    translate();
    QQTSerialMessage::packer(l);
}


void QQTCloseAck::pack(QByteArray &l)
{
    setCmd(_SERIAL_CLOSEACK);
    translate();
    QQTSerialMessage::packer(l);
}


void QQTReadSerialNoAck::pack(QByteArray &l)
{
    setCmd(_SERIAL_READDEVNOACK);
    translate();
    QQTSerialMessage::packer(l);
}


void QQTReadPassAck::pack(QByteArray &l)
{
    setCmd(_SERIAL_READPASSACK);
    translate();
    QQTSerialMessage::packer(l);
}


void QQTExceptionAck::pack(QByteArray &l)
{
    setCmd(_SERIAL_EXCEPTIONACK);
    translate();
    QQTSerialMessage::packer(l);
}

QQTUserSerialProtocol::QQTUserSerialProtocol(QObject *parent) :
    QQTProtocol(parent)
{
#ifdef __MIPS_LINUX__
    QString portName("/dev/ttyS2");
#else
    QString portName("/dev/ttyS2");
#endif
    s0 = QQTUserSerialPortInstance(this, portName, QSerialPort::Baud57600);

    if(s0->open(QIODevice::ReadWrite)) //Open Port dev.
        pline() << QString("serial port %1 open success!").arg(portName);
    else
        pline() << QString("serial port %1 open failed! errcode =").arg(portName) << s0->errorString();
}

QQTUserSerialProtocol::~QQTUserSerialProtocol()
{
    s0->close();
}

void QQTUserSerialProtocol::recvHandup(const QByteArray &l)
{
    sendHandupAck();
}

void QQTUserSerialProtocol::sendHandupAck()
{
    //status c51 + local
    QByteArray s;
    s << quint8(0x00);
    QByteArray l;
    QQTHandupAck ack;
    ack.setData(s);
    ack.pack(l);
    write(l);
}

void QQTUserSerialProtocol::recvClose(const QByteArray &l)
{
    sendCloseAck();
}

void QQTUserSerialProtocol::sendCloseAck()
{
    QByteArray s;
    s << quint8(0x00);
    QByteArray l;
    QQTCloseAck ack;
    ack.setData(s);
    ack.pack(l);
    write(l);
}

void QQTUserSerialProtocol::recvWriteSerialNumber(const QByteArray &l)
{
    QSettings set;
    set.setValue("Device/DeviceNo", l);
    set.sync();
    sendWriteSerialNumberAck();
    emit sigSerialUnlock();
}

void QQTUserSerialProtocol::sendWriteSerialNumberAck()
{
    QQTWriteSerialNoAck ack;
    QSettings set;
    QByteArray sn = set.value("/Device/DeviceNo").toByteArray();
    ack.setData(sn);
    QByteArray l;
    ack.pack(l);
    write(l);
}

void QQTUserSerialProtocol::recvReadSerial(const QByteArray &l)
{
    sendReadSerialAck();
}

void QQTUserSerialProtocol::sendReadSerialAck()
{
    QSettings set;
    QByteArray serial = set.value("Device/DeviceNo").toByteArray();
    QByteArray l;
    QQTReadSerialNoAck ack;
    ack.setData(serial);
    ack.pack(l);
    write(l);
}

void QQTUserSerialProtocol::recvWritePassword(const QByteArray &l)
{
    QSettings set;
    set.setValue("Device/Password", l);
    set.sync();
    sendWritePasswordAck();
}

void QQTUserSerialProtocol::sendWritePasswordAck()
{
    QQTWritePassAck ack;
    QSettings set;
    QByteArray sn = set.value("/Device/Password").toByteArray();
    ack.setData(sn);
    QByteArray l;
    ack.pack(l);
    write(l);
}

void QQTUserSerialProtocol::  recvReadPassword(const QByteArray &l)
{
    sendReadPasswordAck();
}

void QQTUserSerialProtocol::sendReadPasswordAck()
{
    QSettings set;
    QByteArray serial = set.value("Device/Password").toByteArray();
    QByteArray l;
    QQTReadPassAck ack;
    ack.setData(serial);
    ack.pack(l);
    write(l);
}

void QQTUserSerialProtocol::sendExceptionAck()
{
    /*
     * 机器运行出现异常自动通过这个串口上报
     */
    QByteArray l;
    QQTExceptionAck ack;
    //ack.setData("");
    ack.pack(l);
    write(l);
}

quint16 QQTUserSerialProtocol::minlength()
{
    return 10;
}

quint16 QQTUserSerialProtocol::maxlength()
{
    return 128;
}

quint16 QQTUserSerialProtocol::splitter(const QByteArray &s)
{
    QByteArray l = s.left(4);
    quint16 b0 = 0, b1 = 0;
    l >> b0 >> b1;
    return b1;
}


bool QQTUserSerialProtocol::dispatcher(const QByteArray &m)
{
    bool ret = true;

    QQTSerialMessage qMsg;
    qMsg.parser(m);
    pline() << qMsg;

    switch(qMsg.cmd())
    {
    case _SERIAL_HAND:
        recvHandup(qMsg.data());
        break;
    case _SERIAL_CLOSE:
        recvClose(qMsg.data());
        break;
    case _SERIAL_WRITEDEVNO:
        recvWriteSerialNumber(qMsg.data());
        break;
    case _SERIAL_READDEVNO:
        recvReadSerial(qMsg.data());
        break;
    case _SERIAL_WRITEPASS:
        recvWritePassword(qMsg.data());
        break;
    case _SERIAL_READPASS:
        recvReadPassword(qMsg.data());
        break;
    default:
        ret = false;
        pline() << "receive unknown command:" << hex << qMsg.cmd();
        break;
    }
    return ret;
}

QQTSerialPort *QQTUserSerialPortInstance(QObject *parent, QString name, QSerialPort::BaudRate)
{
    static QQTSerialPort* s0 = NULL;
    if(s0 == 0)
    {
        s0 = new QQTSerialPort(parent);
        s0->setPortName(name);
        s0->setBaudRate(QSerialPort::Baud57600);
        s0->setDataBits(QSerialPort::Data8);
        s0->setParity(QSerialPort::NoParity);
        s0->setStopBits(QSerialPort::OneStop);
        s0->setFlowControl(QSerialPort::NoFlowControl);
    }
    return s0;
}

QQtBluetoothClient *QQtUserBluetoothClientInstance(QObject *parent)
{
    static QQtBluetoothClient* cli = nullptr;
    if (!cli) {
        QQtBluetoothManager* inst = QQtBluetoothManager::Instance(parent);
        inst->getDeviceList().first().address();
        cli = new QQtBluetoothClient(QBluetoothServiceInfo::RfcommProtocol, parent);
        cli->setServiceAddress(inst->getDeviceList().first().address());

    }
    return cli;
}
