#include "qqtbluetoothserver.h"
#include "qqtnetwork.h"
#include "qqtbluetoothclient.h"

QQtBluetoothServer::QQtBluetoothServer(QBluetoothServiceInfo::Protocol serverType, QObject* parent) : QBluetoothServer(serverType, parent)
{
    connect(this, SIGNAL(newConnection()),
            this, SLOT(comingNewConnection()));
}

QQtBluetoothServer::~QQtBluetoothServer()
{
    close();
}


void QQtBluetoothServer::comingNewConnection()
{
    if (!hasPendingConnections())
        return;

    QBluetoothSocket* comingSocket = nextPendingConnection();
    QQtBluetoothClient* clientSocket = new QQtBluetoothClient(this);
    connect(clientSocket, SIGNAL(disconnected()), clientSocket, SLOT(deleteLater()));
    clientSocket->installProtocol(m_protocol);
    clientSocket->setSocketDescriptor(comingSocket->socketDescriptor(), QBluetoothServiceInfo::RfcommProtocol);
}

void QQtBluetoothServer::installProtocol(QQTProtocol* stack)
{
    if (m_protocol)
        return;

    m_protocol = stack;
}

void QQtBluetoothServer::uninstallProtocol(QQTProtocol* stack)
{
    Q_UNUSED(stack)
    if (!m_protocol)
        return;

    m_protocol = NULL;
}

QQTProtocol* QQtBluetoothServer::installedProtocol()
{
    return m_protocol;
}
