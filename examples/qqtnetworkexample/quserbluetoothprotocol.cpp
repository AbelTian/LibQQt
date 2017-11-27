#include "quserbluetoothprotocol.h"
#include "qqtsocketbluetoothclient.h"
#include "qqtbluetoothmanager.h"

QUserBluetoothProtocol::QUserBluetoothProtocol ( QObject* parent ) : QObject ( parent )
{

}

QQtSocketBluetoothClient* QQtUserBluetoothClientInstance ( QObject* parent )
{
    static QQtSocketBluetoothClient* cli = nullptr;

    if ( !cli )
    {
        QQtBluetoothManager* inst = QQtBluetoothManager::Instance ( parent );
        inst->getDeviceList().first().address();
        cli = new QQtSocketBluetoothClient ( QBluetoothServiceInfo::RfcommProtocol, parent );
        cli->setServiceAddress ( inst->getDeviceList().first().address() );

    }

    return cli;
}
