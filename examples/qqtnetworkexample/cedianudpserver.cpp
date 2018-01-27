#include "cedianudpserver.h"
#include <QNetworkDatagram>

CedianUdpServer::CedianUdpServer ( QObject* parent ) : QQtSocketUdpClient ( parent )
{
}
