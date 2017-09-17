#ifndef QQTSERIALPORT_H
#define QQTSERIALPORT_H

#include "qqtprotocol.h"
#include <qqt-local.h>

#if defined (__QTEXTSERIALPORT__ )
#include <qextserialport.h>
typedef QextSerialPort QSerialPort;
#else
#include <QSerialPort>
#endif

class QQTSHARED_EXPORT QQTSerialPort : public QSerialPort
{
    Q_OBJECT
public:
    explicit QQTSerialPort(QObject *parent = 0);

    ~QQTSerialPort();

    void installProtocol(QQTProtocol* stack);
    void uninstallProtocol(QQTProtocol* stack);
    QQTProtocol* installedProtocol();

private slots:
    void readyReadData();

private:
    QQTProtocol* m_protocol;
};

#endif // QQTSERIALPORT_H
