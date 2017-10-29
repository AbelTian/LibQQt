#ifndef QQTSERIALPORT_H
#define QQTSERIALPORT_H

#include "qqtprotocol.h"
#include <qqt-local.h>

#if defined (__QEXTSERIALPORT__ )
#include <qextserialport.h>
class QSerialPort : public QextSerialPort
{
    Q_OBJECT
public:
    explicit QSerialPort(QObject* parent = 0) {}
    virtual ~QSerialPort() {}
    enum BaudRate
    {
        Baud1200 = BAUD1200,
        Baud2400 = BAUD2400,
        Baud4800 = BAUD4800,
        Baud9600 = BAUD9600,
        Baud19200 = BAUD19200,
        Baud38400 = BAUD38400,
        Baud57600 = BAUD57600,
        Baud115200 = BAUD115200,
        UnknownBaud = -1
    };
    Q_ENUMS(BaudRate)
    enum DataBits
    {
        Data5 = DATA_5,
        Data6 = DATA_6,
        Data7 = DATA_7,
        Data8 = DATA_8,
        UnknownDataBits = -1
    };
    Q_ENUMS(DataBits)
    enum Parity
    {
        NoParity = PAR_NONE,
        EvenParity = PAR_EVEN,
        OddParity = PAR_ODD,
        SpaceParity = PAR_SPACE,
        MarkParity = PAR_MARK,
        UnknownParity = -1
    };
    Q_ENUMS(Parity)
    enum StopBits
    {
        OneStop = STOP_1,
        OneAndHalfStop = STOP_1_5,
        TwoStop = STOP_2,
        UnknownStopBits = -1
    };
    Q_ENUMS(StopBits)
    enum FlowControl
    {
        NoFlowControl = FLOW_OFF,
        HardwareControl = FLOW_HARDWARE,
        SoftwareControl = FLOW_XONXOFF,
        UnknownFlowControl = -1
    };
    Q_ENUMS(FlowControl)
    // QextSerialBase interface
public:
    virtual void setBaudRate(BaudRate v) { QextSerialPort::setBaudRate((BaudRateType)v); }
    virtual void setDataBits(DataBits v) { QextSerialPort::setDataBits((DataBitsType)v); }
    virtual void setParity(Parity v) { QextSerialPort::setParity((ParityType)v); }
    virtual void setStopBits(StopBits v) { QextSerialPort::setStopBits((StopBitsType)v); }
    virtual void setFlowControl(FlowControl v) { QextSerialPort::setFlowControl((FlowType)v); }
};
#else
#include <QSerialPort>
#endif

class QQTSHARED_EXPORT QQTSerialPort : public QSerialPort
{
    Q_OBJECT
public:
    explicit QQTSerialPort(QObject* parent = 0);
    ~QQTSerialPort();

    void installProtocol(QQtProtocol* stack);
    void uninstallProtocol(QQtProtocol* stack);
    QQtProtocol* installedProtocol();

private slots:
    void readyReadData();

private:
    QQtProtocol* m_protocol;
};

#endif // QQTSERIALPORT_H
