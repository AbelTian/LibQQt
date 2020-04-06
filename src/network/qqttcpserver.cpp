#include "qqttcpserver.h"

QQtTcpServer::QQtTcpServer ( QObject* parent ) :
    QTcpServer ( parent )
{
    connect ( this, SIGNAL ( newConnection() ),
              this, SLOT ( comingNewConnection() ),
              Qt::QueuedConnection );
    m_protocolManager = NULL;
}

QQtTcpServer::~QQtTcpServer()
{
    if ( isListening() )
        close();
}

void QQtTcpServer::installProtocolManager ( QQtProtocolManager* stackGroup )
{
    if ( m_protocolManager )
        return;

    m_protocolManager = stackGroup;
    m_protocolManager->setServerHandler ( this );
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

QQtTcpClient* QQtTcpServer::findClientByProtocolInstance ( QQtProtocol* protocol )
{
    QListIterator<QQtTcpClient*> itor ( m_clientList );
    while ( itor.hasNext() )
    {
        QQtTcpClient* client = itor.next();
        QQtProtocol* cprotocol = client->installedProtocol();
        if ( cprotocol == protocol )
        {
            return client;
        }
    }
    return NULL;
}

QQtTcpClient* QQtTcpServer::findClientByIPAddress ( QString ip, quint16 port )
{
    QListIterator<QQtTcpClient*> itor ( m_clientList );
    while ( itor.hasNext() )
    {
        QQtTcpClient* client = itor.next();
        QString aip = client->peerAddress().toString();
        quint16 aport = client->peerPort();
        if ( aip == ip && aport == port )
        {
            return client;
        }
    }
    return NULL;
}

void QQtTcpServer::incomingConnection ( qintptr handle )
{
    return QTcpServer::incomingConnection ( handle );
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
    m_clientList.push_back ( clientSocket );
}

void QQtTcpServer::clientSocketDisConnected()
{
    QObject* obj = sender();
    QQtTcpClient* clientSocket = ( QQtTcpClient* ) obj;
    QQtProtocol* protocol = clientSocket->installedProtocol();
    clientSocket->uninstallProtocol ( protocol );
    clientSocket->deleteLater();
    m_clientList.removeOne ( clientSocket );
    m_protocolManager->deleteProtocol ( protocol );
}

void QQtTcpServer::comingNewConnection()
{
    while ( hasPendingConnections() )
    {
        QTcpSocket* comingSocket = nextPendingConnection();
        if ( !m_protocolManager )
        {
            pline() << "please install protocol manager for your server.";
            comingSocket->deleteLater();
            return;
        }

        QQtTcpClient* clientSocket = new QQtTcpClient ( this );
        clientSocket->setSocketDescriptor ( comingSocket->socketDescriptor() );

        connect ( clientSocket, SIGNAL ( disconnected() ),
                  this, SLOT ( clientSocketDisConnected() ) );
        //如果崩溃，对这个操作进行加锁。
        QQtProtocol* protocol = m_protocolManager->createProtocol();
        clientSocket->installProtocol ( protocol );
        m_clientList.push_back ( clientSocket );
    }
}
