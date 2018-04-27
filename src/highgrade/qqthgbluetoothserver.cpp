#include "qqthgbluetoothserver.h"
#include "qqthgbluetoothclient.h"

QQtHgBluetoothServer::QQtHgBluetoothServer ( QBluetoothServiceInfo::Protocol serverType,
                                             QObject* parent ) : QBluetoothServer ( serverType, parent )
{
    connect ( this, SIGNAL ( newConnection() ),
              this, SLOT ( comingNewConnection() ) );
}

QQtHgBluetoothServer::~QQtHgBluetoothServer()
{
    close();
}


void QQtHgBluetoothServer::comingNewConnection()
{
    if ( !hasPendingConnections() )
        return;

    QBluetoothSocket* comingSocket = nextPendingConnection();
    QQtHgBluetoothClient* clientSocket = new QQtHgBluetoothClient ( this );
    connect ( clientSocket, SIGNAL ( disconnected() ), clientSocket, SLOT ( deleteLater() ) );
    clientSocket->installProtocol ( m_protocol );
    clientSocket->setSocketDescriptor ( comingSocket->socketDescriptor(), QBluetoothServiceInfo::RfcommProtocol );
}

void QQtHgBluetoothServer::installProtocol ( QQtHgProtocol* stack )
{
    if ( m_protocol )
        return;

    m_protocol = stack;
}

void QQtHgBluetoothServer::uninstallProtocol ( QQtHgProtocol* stack )
{
    Q_UNUSED ( stack )

    if ( !m_protocol )
        return;

    m_protocol = NULL;
}

QQtHgProtocol* QQtHgBluetoothServer::installedProtocol()
{
    return m_protocol;
}
