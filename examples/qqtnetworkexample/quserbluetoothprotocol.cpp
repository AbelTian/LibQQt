#include "quserbluetoothprotocol.h"
#include "qqtbluetoothclient.h"
#include "qqtbluetoothmanager.h"

QUserBluetoothProtocol::QUserBluetoothProtocol ( QObject* parent ) : QObject ( parent )
{

}

QQtBluetoothClient* QQtUserBluetoothClientInstance ( QObject* parent )
{
    static QQtBluetoothClient* cli = nullptr;

    if ( !cli )
    {
        QQtBluetoothManager* inst = QQtBluetoothManager::Instance ( parent );
        inst->getDeviceList().first().address();
        cli = new QQtBluetoothClient ( QBluetoothServiceInfo::RfcommProtocol, parent );
        cli->setServiceAddress ( inst->getDeviceList().first().address() );

    }

    return cli;
}
