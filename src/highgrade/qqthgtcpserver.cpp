#include "qqthgtcpserver.h"

QQtHgTcpServer::QQtHgTcpServer ( QObject* parent ) :
    QTcpServer ( parent )
{
}

QQtHgTcpServer::~QQtHgTcpServer()
{
    if ( isListening() )
        close();
}

void QQtHgTcpServer::incomingConnection ( qintptr handle )
{
    QQtHgTcpClient* clientSocket = new QQtHgTcpClient ( this );
    clientSocket->setSocketDescriptor ( handle );
    connect ( clientSocket, SIGNAL ( disconnected() ), this, SLOT ( clientSocketDisConnected() ) );
    if ( !m_protocolManager )
    {
        pline() << "please install protocol manager for your server.";
        clientSocket->deleteLater();
        return;
    }
    clientSocket->installProtocolManager ( m_protocolManager );
}

void QQtHgTcpServer::clientSocketDisConnected()
{
    QObject* obj = sender();
    QQtHgTcpClient* clientSocket = ( QQtHgTcpClient* ) obj;
    if ( !m_protocolManager )
    {
        pline() << "please install protocol manager for your server.";
        clientSocket->deleteLater();
        return;
    }
    clientSocket->uninstallProtocolManager ( m_protocolManager );
    clientSocket->deleteLater();
}

void QQtHgTcpServer::installProtocolManager ( QQtHgProtocolManager* stackGroup )
{
    if ( m_protocolManager )
        return;

    m_protocolManager = stackGroup;
}

void QQtHgTcpServer::uninstallProtocolManager ( QQtHgProtocolManager* stackGroup )
{
    Q_UNUSED ( stackGroup )

    if ( !m_protocolManager )
        return;

    m_protocolManager = NULL;
}

QQtHgProtocolManager* QQtHgTcpServer::installedProtocolManager()
{
    return m_protocolManager;
}
