#include "qqttcpserver.h"
#include "qqtnetwork.h"


QQtTcpServer::QQtTcpServer ( QObject* parent ) :
    QTcpServer ( parent )
{
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

