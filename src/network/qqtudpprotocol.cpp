#include "qqtudpprotocol.h"

QQtUdpProtocol::QQtUdpProtocol ( QObject* parent ) : QObject ( parent )
{

}

void QQtUdpProtocol::translator ( const QNetworkDatagram& dg )
{
    dispatcher ( dg );
}
