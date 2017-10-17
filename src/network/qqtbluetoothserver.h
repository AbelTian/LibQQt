#ifndef QQTBLUETOOTHSERVER_H
#define QQTBLUETOOTHSERVER_H

#include <QBluetoothServer>
#include "qqtprotocol.h"
#include <qqt-local.h>

class QQTSHARED_EXPORT QQtBluetoothServer : public QBluetoothServer
{
    Q_OBJECT
public:
    explicit QQtBluetoothServer(QBluetoothServiceInfo::Protocol serverType, QObject *parent = nullptr);
    ~QQtBluetoothServer();

    void installProtocol(QQTProtocol* stack);
    void uninstallProtocol(QQTProtocol* stack);
    QQTProtocol* installedProtocol();

signals:

public slots:

signals:

private slots:
    void comingNewConnection();

private:
    QQTProtocol* m_protocol;
};

#endif // QQTBLUETOOTHSERVER_H
