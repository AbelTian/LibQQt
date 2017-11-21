#include "qqtserver.h"
#include "qqtnetwork.h"


QQtServer::QQtServer(QObject* parent) :
    QTcpServer(parent)
{
}

QQtServer::~QQtServer()
{
    close();
}

void QQtServer::incomingConnection(qintptr handle)
{
    QQtClient* clientSocket = new QQtClient(this);
    clientSocket->setSocketDescriptor(handle);
    connect(clientSocket, SIGNAL(disconnected()), clientSocket, SLOT(deleteLater()));
    clientSocket->installProtocol(m_protocol);
}

void QQtServer::installProtocol(QQtProtocol* stack)
{
    if (m_protocol)
        return;

    m_protocol = stack;
}

void QQtServer::uninstallProtocol(QQtProtocol* stack)
{
    Q_UNUSED(stack)

    if (!m_protocol)
        return;

    m_protocol = NULL;
}

QQtProtocol* QQtServer::installedProtocol()
{
    return m_protocol;
}

