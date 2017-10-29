#include "qqtserver.h"
#include "qqtnetwork.h"


QQTServer::QQTServer(QObject* parent) :
    QTcpServer(parent)
{
}

QQTServer::~QQTServer()
{
    close();
}

void QQTServer::incomingConnection(qintptr handle)
{
    QQTClient* clientSocket = new QQTClient(this);
    clientSocket->setSocketDescriptor(handle);
    connect(clientSocket, SIGNAL(disconnected()), clientSocket, SLOT(deleteLater()));
    clientSocket->installProtocol(m_protocol);
}

void QQTServer::installProtocol(QQTProtocol* stack)
{
    if (m_protocol)
        return;

    m_protocol = stack;
}

void QQTServer::uninstallProtocol(QQTProtocol* stack)
{
    Q_UNUSED(stack)

    if (!m_protocol)
        return;

    m_protocol = NULL;
}

QQTProtocol* QQTServer::installedProtocol()
{
    return m_protocol;
}

