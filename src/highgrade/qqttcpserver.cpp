#include "qqttcpserver.h"
#include "qqtnetwork.h"


QQtTcpServer::QQtTcpServer ( QObject* parent ) :
    QTcpServer ( parent )
{
    connect ( this, SIGNAL ( newConnection() ),
              this, SLOT ( slotNewConnection() ),
              Qt::AutoConnection );
}

QQtTcpServer::~QQtTcpServer()
{
    if ( isListening() )
        close();
}

void QQtTcpServer::incomingConnection ( qintptr handle )
{
    return QTcpServer::incomingConnection ( handle );

    QQtTcpClient* clientSocket = new QQtTcpClient ( this );
    clientSocket->setSocketDescriptor ( handle );
    connect ( clientSocket, SIGNAL ( disconnected() ), clientSocket, SLOT ( deleteLater() ) );
    QQtProtocol* protocolInstance = m_protocolManager->createProtocol();
    clientSocket->installProtocol ( protocolInstance );
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

void QQtTcpServer::slotNewConnection()
{
    bool has = hasPendingConnections();
    if ( !has )
        return;

    QTcpSocket* p = nextPendingConnection();

    QQtTcpClient* clientSocket = new QQtTcpClient ( this );
    clientSocket->setSocketDescriptor ( p->socketDescriptor() );

    connect ( clientSocket, SIGNAL ( disconnected() ), clientSocket, SLOT ( deleteLater() ) );
    QQtProtocol* protocolInstance = m_protocolManager->createProtocol();
    clientSocket->installProtocol ( protocolInstance );
}

