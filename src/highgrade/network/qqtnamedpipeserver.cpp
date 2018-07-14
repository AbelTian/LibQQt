#include "qqtnamedpipeserver.h"

QQtNamedPipeServer::QQtNamedPipeServer ( QObject* parent ) :
    QLocalServer ( parent )
{
    connect ( this, SIGNAL ( newConnection() ),
              this, SLOT ( comingNewConnection() ),
              Qt::QueuedConnection );
    m_protocolManager = NULL;
}

QQtNamedPipeServer::~QQtNamedPipeServer()
{
    if ( isListening() )
        close();
}

void QQtNamedPipeServer::clientSocketDisConnected()
{
    QObject* obj = sender();
    QQtNamedPipeClient* clientSocket = ( QQtNamedPipeClient* ) obj;
    QQtProtocol* protocol = clientSocket->installedProtocol();
    clientSocket->uninstallProtocol ( protocol );
    clientSocket->deleteLater();
    m_clientList.removeOne ( clientSocket );
    m_protocolManager->deleteProtocol ( protocol );
}

void QQtNamedPipeServer::comingNewConnection()
{
    while ( hasPendingConnections() )
    {
        QLocalSocket* comingSocket = nextPendingConnection();
        if ( !m_protocolManager )
        {
            pline() << "please install protocol manager for your server.";
            comingSocket->deleteLater();
            return;
        }

        QQtNamedPipeClient* clientSocket = new QQtNamedPipeClient ( this );
        clientSocket->setSocketDescriptor ( comingSocket->socketDescriptor() );

        connect ( clientSocket, SIGNAL ( disconnected() ),
                  this, SLOT ( clientSocketDisConnected() ) );
        //如果崩溃，对这个操作进行加锁。
        QQtProtocol* protocol = m_protocolManager->createProtocol();
        clientSocket->installProtocol ( protocol );
        m_clientList.push_back ( clientSocket );
    }
}

void QQtNamedPipeServer::installProtocolManager ( QQtProtocolManager* stackGroup )
{
    if ( m_protocolManager )
        return;

    m_protocolManager = stackGroup;
}

void QQtNamedPipeServer::uninstallProtocolManager ( QQtProtocolManager* stackGroup )
{
    Q_UNUSED ( stackGroup )

    if ( !m_protocolManager )
        return;

    m_protocolManager = NULL;
}

QQtProtocolManager* QQtNamedPipeServer::installedProtocolManager()
{
    return m_protocolManager;
}

QQtNamedPipeClient* QQtNamedPipeServer::findClientByProtocolInstance ( QQtProtocol* protocol )
{
    QListIterator<QQtNamedPipeClient*> itor ( m_clientList );
    while ( itor.hasNext() )
    {
        QQtNamedPipeClient* client = itor.next();
        QQtProtocol* cprotocol = client->installedProtocol();
        if ( cprotocol == protocol )
        {
            return client;
        }
    }
    return NULL;
}

QQtNamedPipeClient* QQtNamedPipeServer::findClientByIPAddress ( QString ip )
{
    QListIterator<QQtNamedPipeClient*> itor ( m_clientList );
    while ( itor.hasNext() )
    {
        QQtNamedPipeClient* client = itor.next();
        QString aip = client->peerName();
        if ( aip == ip )
        {
            return client;
        }
    }
    return NULL;
}
