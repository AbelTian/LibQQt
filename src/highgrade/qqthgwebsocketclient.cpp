#include "qqthgwebsocketclient.h"

QQtHgWebSocketClient::QQtHgWebSocketClient ( QObject* parent, const QString& origin,
                                             QWebSocketProtocol::Version version ) :
    QWebSocket ( origin, version, parent )
{

}
