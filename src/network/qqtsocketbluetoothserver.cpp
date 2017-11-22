#include "qqtsocketbluetoothserver.h"
#include "qqtnetwork.h"
#include "qqtsocketbluetoothclient.h"

QQtSocketBluetoothServer::QQtSocketBluetoothServer ( QBluetoothServiceInfo::Protocol serverType,
                                                     QObject* parent ) : QBluetoothServer ( serverType, parent )
{
    connect ( this, SIGNAL ( newConnection() ),
              this, SLOT ( comingNewConnection() ) );
}

QQtSocketBluetoothServer::~QQtSocketBluetoothServer()
{
    close();
}


void QQtSocketBluetoothServer::comingNewConnection()
{
    if ( !hasPendingConnections() )
        return;

    QBluetoothSocket* comingSocket = nextPendingConnection();
    QQtSocketBluetoothClient* clientSocket = new QQtSocketBluetoothClient ( this );
    connect ( clientSocket, SIGNAL ( disconnected() ), clientSocket, SLOT ( deleteLater() ) );
    clientSocket->installProtocol ( m_protocol );
    clientSocket->setSocketDescriptor ( comingSocket->socketDescriptor(), QBluetoothServiceInfo::RfcommProtocol );
}

void QQtSocketBluetoothServer::installProtocol ( QQtProtocol* stack )
{
    if ( m_protocol )
        return;

    m_protocol = stack;
}

void QQtSocketBluetoothServer::uninstallProtocol ( QQtProtocol* stack )
{
    Q_UNUSED ( stack )

    if ( !m_protocol )
        return;

    m_protocol = NULL;
}

QQtProtocol* QQtSocketBluetoothServer::installedProtocol()
{
    return m_protocol;
}
