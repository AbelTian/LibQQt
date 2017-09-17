#ifndef QQTSERIALPORT_H
#define QQTSERIALPORT_H

#include <QSerialPort>
#include "qqtcore.h"
#include "qqtprotocol.h"
#include <qqt.h>

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
