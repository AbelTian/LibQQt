#include "qqttcpserver.h"

QQtTcpServer::QQtTcpServer ( QObject* parent ) :
    QTcpServer ( parent )
{
    m_protocolManager = NULL;
}

QQtTcpServer::~QQtTcpServer()
{
    if ( isListening() )
        close();
}

void QQtTcpServer::incomingConnection ( qintptr handle )
{
    QQtTcpClient* clientSocket = new QQtTcpClient ( this );
    clientSocket->setSocketDescriptor ( handle );
    if ( !m_protocolManager )
    {
        pline() << "please install protocol manager for your server.";
        clientSocket->deleteLater();
        return;
    }

    connect ( clientSocket, SIGNAL ( disconnected() ), this, SLOT ( clientSocketDisConnected() ) );
    //如果崩溃，对这个操作进行加锁。
    QQtProtocol* protocol = m_protocolManager->createProtocol();
    clientSocket->installProtocol ( protocol );
}

void QQtTcpServer::clientSocketDisConnected()
{
    QObject* obj = sender();
    QQtTcpClient* clientSocket = ( QQtTcpClient* ) obj;
    QQtProtocol* protocol = clientSocket->installedProtocol();
    clientSocket->uninstallProtocol ( protocol );
    clientSocket->deleteLater();
    protocol->deleteLater();
}

void QQtTcpServer::installProtocolManager ( QQtProtocolManager* stackGroup )
{
    if ( m_protocolManager )
        return;

    m_protocolManager = stackGroup;
}

void QQtTcpServer::uninstallProtocolManager ( QQtProtocolManager* stackGroup )
{
    Q_UNUSED ( stackGroup )

    if ( !m_protocolManager )
        return;

    m_protocolManager = NULL;
}

QQtProtocolManager* QQtTcpServer::installedProtocolManager()
{
    return m_protocolManager;
}
