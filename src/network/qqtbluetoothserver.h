#ifndef QQTBLUETOOTHSERVER_H
#define QQTBLUETOOTHSERVER_H

#include <QBluetoothServer>
#include <qqtbluetoothclient.h>
#include "qqtprotocolmanager.h"
#include <qqt-local.h>

class QQTSHARED_EXPORT QQtBluetoothServer : public QBluetoothServer
{
    Q_OBJECT
public:
    explicit QQtBluetoothServer ( QBluetoothServiceInfo::Protocol serverType, QObject* parent = nullptr );
    virtual ~QQtBluetoothServer();

    void installProtocolManager ( QQtProtocolManager* stackGroup );
    void uninstallProtocolManager ( QQtProtocolManager* stackGroup );
    QQtProtocolManager* installedProtocolManager();

public:
    QQtBluetoothClient* findClientByProtocolInstance ( QQtProtocol* protocol );
    QQtBluetoothClient* findClientByIPAddress ( QString ip, quint16 port );
    QList<QQtBluetoothClient*>& clientList() { return m_clientList; }

signals:

public slots:

signals:

private slots:
    void comingNewConnection();
public slots:
    void clientSocketDisConnected();
private:
    QQtProtocolManager* m_protocolManager;
    QList<QQtBluetoothClient*> m_clientList;
};

#endif // QQTBLUETOOTHSERVER_H
