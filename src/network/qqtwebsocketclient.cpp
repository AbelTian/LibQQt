#include "qqtwebsocketclient.h"

QQtWebSocketClient::QQtWebSocketClient ( QObject* parent, const QString& origin, QWebSocketProtocol::Version version ) :
    QWebSocket ( origin, version, parent )
{
    connect ( this, SIGNAL ( binaryMessageReceived ( QByteArray ) ),
              this, SLOT ( slotReadData ( QByteArray ) ) );
}

void QQtWebSocketClient::installProtocol ( QQtProtocol* stack )
{
    if ( m_protocol )
        return;
    m_protocol = stack;

    connect ( m_protocol, SIGNAL ( write ( const QByteArray& ) ),
              this, SLOT ( slotWriteData ( const QByteArray& ) ) );
    m_protocol->attach();
}

void QQtWebSocketClient::uninstallProtocol ( QQtProtocol* stack )
{
    Q_UNUSED ( stack )

    if ( !m_protocol )
        return;

    disconnect ( m_protocol, SIGNAL ( write ( const QByteArray& ) ),
                 this, SLOT ( slotWriteData ( const QByteArray& ) ) );
    m_protocol->detach();
    m_protocol = NULL;
}

QQtProtocol* QQtWebSocketClient::installedProtocol()
{
    return m_protocol;
}

void QQtWebSocketClient::slotReadData ( const QByteArray& bytes )
{
    translator ( bytes );
}

void QQtWebSocketClient::slotWriteData ( const QByteArray& bytes )
{
    sendBinaryMessage ( bytes );
}

void QQtWebSocketClient::translator ( const QByteArray& bytes )
{
    m_protocol->dispatcher ( bytes );
}
