#include "cedianudpserver.h"
#include <QNetworkDatagram>

CedianUdpServer::CedianUdpServer ( QObject* parent ) : QQtUdpClient ( parent )
{
}
