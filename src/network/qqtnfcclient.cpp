#include "qqtnfcclient.h"
#include <qqtcore.h>

QQtNfcClient::QQtNfcClient ( QObject* parent ) : QNearFieldTarget ( parent )
{
    connect ( this, SIGNAL ( error ( QNearFieldTarget::Error, const QNearFieldTarget::RequestId& ) ),
              this, SLOT ( errorOccured ( QNearFieldTarget::Error, const QNearFieldTarget::RequestId& ) ) );

    connect ( this, SIGNAL ( ndefMessageRead ( const QNdefMessage& ) ),
              this, SLOT ( readyReadNdefMessage ( const QNdefMessage& ) ) );

    m_protocol = nullptr;
}

void QQtNfcClient::installProtocol ( QQtProtocol* stack )
{
    if ( m_protocol )
        return;
    m_protocol = stack;

    connect ( m_protocol, SIGNAL ( write ( const QByteArray& ) ),
              this, SLOT ( slotWriteData ( const QByteArray& ) ) );
    m_protocol->attach();
}

void QQtNfcClient::uninstallProtocol ( QQtProtocol* stack )
{
    Q_UNUSED ( stack )

    if ( !m_protocol )
        return;

    disconnect ( stack, SIGNAL ( write ( const QByteArray& ) ),
                 this, SLOT ( slotWriteData ( const QByteArray& ) ) );
    m_protocol->detach();
    m_protocol = NULL;
}

QQtProtocol* QQtNfcClient::installedProtocol()
{
    return m_protocol;
}

void QQtNfcClient::errorOccured ( QNearFieldTarget::Error err, const QNearFieldTarget::RequestId& id )
{
    pline() << err;
    QVariant cc = requestResponse ( id );
    pline() << cc;
}

void QQtNfcClient::readyReadNdefMessage ( const QNdefMessage& message )
{
    QByteArray bytes = message.toByteArray();
    translator ( bytes );
}

void QQtNfcClient::slotWriteData ( const QByteArray& bytes )
{
    sendCommand ( bytes );
}

void QQtNfcClient::translator ( const QByteArray& bytes )
{
    m_protocol->dispatcher ( bytes );
}
