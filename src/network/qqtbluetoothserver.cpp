#include "qqtbluetoothserver.h"
#include "qqtbluetoothclient.h"

QQtBluetoothServer::QQtBluetoothServer ( QBluetoothServiceInfo::Protocol serverType,
                                         QObject* parent ) : QBluetoothServer ( serverType, parent )
{
    connect ( this, SIGNAL ( newConnection() ),
              this, SLOT ( comingNewConnection() ) );
}

QQtBluetoothServer::~QQtBluetoothServer()
{
    close();
}


void QQtBluetoothServer::comingNewConnection()
{
    while ( hasPendingConnections() )
    {
        QBluetoothSocket* comingSocket = nextPendingConnection();

        if ( !m_protocolManager )
        {
            pline() << "please install protocol manager for your server.";
            comingSocket->deleteLater();
            return;
        }

        QQtBluetoothClient* clientSocket = new QQtBluetoothClient ( this );
        connect ( clientSocket, SIGNAL ( disconnected() ), this, SLOT ( clientSocketDisConnected() ) );
        //如果崩溃，对这个操作进行加锁。
        QQtProtocol* protocol = m_protocolManager->createProtocol();
        clientSocket->installProtocol ( protocol );
        clientSocket->setSocketDescriptor ( comingSocket->socketDescriptor(), QBluetoothServiceInfo::RfcommProtocol );
        m_clientList.push_back ( clientSocket );
    }
}

void QQtBluetoothServer::clientSocketDisConnected()
{
    QObject* obj = sender();
    QQtBluetoothClient* clientSocket = ( QQtBluetoothClient* ) obj;
    QQtProtocol* protocol = clientSocket->installedProtocol();
    clientSocket->uninstallProtocol ( protocol );
    clientSocket->deleteLater();
    m_clientList.removeOne ( clientSocket );
    m_protocolManager->deleteProtocol ( protocol );
}

void QQtBluetoothServer::installProtocolManager ( QQtProtocolManager* stackGroup )
{
    if ( m_protocolManager )
        return;

    m_protocolManager = stackGroup;
}

void QQtBluetoothServer::uninstallProtocolManager ( QQtProtocolManager* stackGroup )
{
    Q_UNUSED ( stackGroup )

    if ( !m_protocolManager )
        return;

    m_protocolManager = NULL;
}

QQtProtocolManager* QQtBluetoothServer::installedProtocolManager()
{
    return m_protocolManager;
}

QQtBluetoothClient* QQtBluetoothServer::findClientByProtocolInstance ( QQtProtocol* protocol )
{
    QListIterator<QQtBluetoothClient*> itor ( m_clientList );
    while ( itor.hasNext() )
    {
        QQtBluetoothClient* client = itor.next();
        QQtProtocol* cprotocol = client->installedProtocol();
        if ( cprotocol == protocol )
        {
            return client;
        }
    }
    return NULL;
}

QQtBluetoothClient* QQtBluetoothServer::findClientByIPAddress ( QString ip, quint16 port )
{
    QListIterator<QQtBluetoothClient*> itor ( m_clientList );
    while ( itor.hasNext() )
    {
        QQtBluetoothClient* client = itor.next();
        QString aip = client->peerAddress().toString();
        quint16 aport = client->peerPort();
        if ( aip == ip && aport == port )
        {
            return client;
        }
    }
    return NULL;
}
