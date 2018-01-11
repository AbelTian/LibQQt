#include "qqtsockettcpserver.h"
#include "qqtnetwork.h"


QQtSocketTcpServer::QQtSocketTcpServer ( QObject* parent ) :
    QTcpServer ( parent )
{
}

QQtSocketTcpServer::~QQtSocketTcpServer()
{
    if ( isListening() )
        close();
}

void QQtSocketTcpServer::incomingConnection ( qintptr handle )
{
    QQtSocketTcpClient* clientSocket = new QQtSocketTcpClient ( this );
    clientSocket->setSocketDescriptor ( handle );
    connect ( clientSocket, SIGNAL ( disconnected() ), clientSocket, SLOT ( deleteLater() ) );
    clientSocket->installProtocol ( m_protocol );
}

void QQtSocketTcpServer::installProtocol ( QQtProtocol* stack )
{
    if ( m_protocol )
        return;

    m_protocol = stack;
}

void QQtSocketTcpServer::uninstallProtocol ( QQtProtocol* stack )
{
    Q_UNUSED ( stack )

    if ( !m_protocol )
        return;

    m_protocol = NULL;
}

QQtProtocol* QQtSocketTcpServer::installedProtocol()
{
    return m_protocol;
}

