#include "qqtlocalserver.h"

QQtLocalServer::QQtLocalServer ( QObject* parent ) :
    QLocalServer ( parent )
{
    connect ( this, SIGNAL ( newConnection() ),
              this, SLOT ( comingNewConnection() ),
              Qt::QueuedConnection );
    m_protocolManager = NULL;
}

QQtLocalServer::~QQtLocalServer()
{
    if ( isListening() )
        close();
}

void QQtLocalServer::clientSocketDisConnected()
{
    QObject* obj = sender();
    QQtLocalClient* clientSocket = ( QQtLocalClient* ) obj;
    QQtProtocol* protocol = clientSocket->installedProtocol();
    clientSocket->uninstallProtocol ( protocol );
    clientSocket->deleteLater();
    m_clientList.removeOne ( clientSocket );
    m_protocolManager->deleteProtocol ( protocol );
}

void QQtLocalServer::comingNewConnection()
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

        QQtLocalClient* clientSocket = new QQtLocalClient ( this );
        clientSocket->setSocketDescriptor ( comingSocket->socketDescriptor() );

        connect ( clientSocket, SIGNAL ( disconnected() ),
                  this, SLOT ( clientSocketDisConnected() ) );
        //如果崩溃，对这个操作进行加锁。
        QQtProtocol* protocol = m_protocolManager->createProtocol();
        clientSocket->installProtocol ( protocol );
        m_clientList.push_back ( clientSocket );
    }
}

void QQtLocalServer::installProtocolManager ( QQtProtocolManager* stackGroup )
{
    if ( m_protocolManager )
        return;

    m_protocolManager = stackGroup;
}

void QQtLocalServer::uninstallProtocolManager ( QQtProtocolManager* stackGroup )
{
    Q_UNUSED ( stackGroup )

    if ( !m_protocolManager )
        return;

    m_protocolManager = NULL;
}

QQtProtocolManager* QQtLocalServer::installedProtocolManager()
{
    return m_protocolManager;
}

QQtLocalClient* QQtLocalServer::findClientByProtocolInstance ( QQtProtocol* protocol )
{
    QListIterator<QQtLocalClient*> itor ( m_clientList );
    while ( itor.hasNext() )
    {
        QQtLocalClient* client = itor.next();
        QQtProtocol* cprotocol = client->installedProtocol();
        if ( cprotocol == protocol )
        {
            return client;
        }
    }
    return NULL;
}

QQtLocalClient* QQtLocalServer::findClientByIPAddress ( QString ip )
{
    QListIterator<QQtLocalClient*> itor ( m_clientList );
    while ( itor.hasNext() )
    {
        QQtLocalClient* client = itor.next();
        QString aip = client->peerName();
        if ( aip == ip )
        {
            return client;
        }
    }
    return NULL;
}
