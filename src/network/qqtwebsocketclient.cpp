#include "qqtwebsocketclient.h"

QQtWebSocketClient::QQtWebSocketClient ( QObject* parent, const QString& origin, QWebSocketProtocol::Version version ) :
    QWebSocket ( origin, version, parent )
{

}
