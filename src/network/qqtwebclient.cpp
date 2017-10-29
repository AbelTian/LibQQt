#include "qqtwebclient.h"

QQtWebClient::QQtWebClient(QObject* parent, const QString& origin, QWebSocketProtocol::Version version) :
    QWebSocket(origin, version, parent)
{

}
