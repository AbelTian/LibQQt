#include "qqtwebsocketserver.h"

QQtWebSocketServer::QQtWebSocketServer ( const QString& serverName, SslMode secureMode,
                                         QObject* parent ) : QWebSocketServer ( serverName, secureMode, parent )
{
    connect ( this, SIGNAL ( newConnection() ),
              this, SLOT ( comingNewConnection() ) );

    m_protocolManager = NULL;
}

void QQtWebSocketServer::installProtocolManager ( QQtProtocolManager* stackGroup )
{
    if ( m_protocolManager )
        return;

    m_protocolManager = stackGroup;
}

void QQtWebSocketServer::uninstallProtocolManager ( QQtProtocolManager* stackGroup )
{
    Q_UNUSED ( stackGroup )

    if ( !m_protocolManager )
        return;

    m_protocolManager = NULL;
}

QQtWebSocketClient* QQtWebSocketServer::findClientByProtocolInstance ( QQtProtocol* protocol )
{
    QListIterator<QQtWebSocketClient*> itor ( m_clientList );
    while ( itor.hasNext() )
    {
        QQtWebSocketClient* client = itor.next();
        QQtProtocol* cprotocol = client->installedProtocol();
        if ( cprotocol == protocol )
        {
            return client;
        }
    }
    return NULL;
}

QQtWebSocketClient* QQtWebSocketServer::findClientByIPAddress ( QString ip, quint16 port )
{
    QListIterator<QQtWebSocketClient*> itor ( m_clientList );
    while ( itor.hasNext() )
    {
        QQtWebSocketClient* client = itor.next();
        QString aip = client->peerAddress().toString();
        quint16 aport = client->peerPort();
        if ( aip == ip && aport == port )
        {
            return client;
        }
    }
    return NULL;
}

void QQtWebSocketServer::comingNewConnection()
{
    while ( hasPendingConnections() )
    {
        QQtWebSocketClient* clientSocket = ( QQtWebSocketClient* ) nextPendingConnection();
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
        m_clientList.push_back ( clientSocket );
    }
}

void QQtWebSocketServer::clientSocketDisConnected()
{
    QObject* obj = sender();
    QQtWebSocketClient* clientSocket = ( QQtWebSocketClient* ) obj;
    QQtProtocol* protocol = clientSocket->installedProtocol();
    clientSocket->uninstallProtocol ( protocol );
    clientSocket->deleteLater();
    m_clientList.removeOne ( clientSocket );
}

QQtProtocolManager* QQtWebSocketServer::installedProtocolManager()
{
    return m_protocolManager;
}
