#include "qqtserver.h"
#include "qqtnetwork.h"


QQTServer::QQTServer(QObject *parent) :
    QTcpServer(parent)
{
}

QQTServer::~QQTServer()
{
    close();
}

void QQTServer::incomingConnection(int handle)
{
    QQTClient* clientSocket = new QQTClient(this);
    clientSocket->setSocketDescriptor(handle);
    connect(clientSocket, SIGNAL(disconnected()), clientSocket, SLOT(deleteLater()));
    clientSocket->installProtocol(m_protocol);
}

void QQTServer::installProtocol(QQTProtocol *stack)
{
    if(m_protocol)
        return;

    m_protocol = stack;
    connect(m_protocol, SIGNAL(write(const QByteArray&)), this, SLOT(write(const QByteArray&)));
}

void QQTServer::uninstallProtocol(QQTProtocol *stack)
{
    if(!m_protocol)
        return;

    disconnect(m_protocol, SIGNAL(write(const QByteArray&)), this, SLOT(write(const QByteArray&)));
    m_protocol = NULL;
}

QQTProtocol *QQTServer::installedProtocol()
{
    return m_protocol;
}

QQTServer *QQTSingleServer(QObject *parent)
{
    static QQTServer* s = new QQTServer(parent);
    s->listen(QHostAddress::Any, 8000);
    return s;
}

