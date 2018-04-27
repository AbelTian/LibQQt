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
    clientSocket->installProtocol ( m_protocol );
}

void QQtTcpServer::installProtocol ( QQtProtocol* stack )
{
    if ( m_protocol )
        return;

    m_protocol = stack;
}

void QQtTcpServer::uninstallProtocol ( QQtProtocol* stack )
{
    Q_UNUSED ( stack )

    if ( !m_protocol )
        return;

    m_protocol = NULL;
}

QQtProtocol* QQtTcpServer::installedProtocol()
{
    return m_protocol;
}

