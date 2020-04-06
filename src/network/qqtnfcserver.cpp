#include <qqtnfcserver.h>

QQtNfcServer::QQtNfcServer ( QObject* parent )
{
    connect ( this, SIGNAL ( targetDetected ( QNearFieldTarget* ) ),
              this, SLOT ( hasPendingTarget ( QNearFieldTarget* ) ) );
    connect ( this, SIGNAL ( targetLost ( QNearFieldTarget* ) ),
              this, SLOT ( hasTargetLosted ( QNearFieldTarget* ) ) );
    m_protocolManager = NULL;
}

QQtNfcServer::~QQtNfcServer() {}

void QQtNfcServer::installProtocolManager ( QQtProtocolManager* stackGroup )
{
    if ( m_protocolManager )
        return;
    m_protocolManager = stackGroup;
    m_protocolManager->setServerHandler ( this );
}

void QQtNfcServer::uninstallProtocolManager ( QQtProtocolManager* stackGroup )
{
    Q_UNUSED ( stackGroup )
    if ( !m_protocolManager )
        return;
    m_protocolManager = NULL;
}

QQtProtocolManager* QQtNfcServer::installedProtocolManager()
{
    return m_protocolManager;
}

void QQtNfcServer::hasPendingTarget ( QNearFieldTarget* target )
{
    QQtNfcClient* clientSocket = new QQtNfcClient ( this );

    clientSocket->setUid ( target->uid() );
    clientSocket->setType ( target->type() );
    clientSocket->setAccessMethods ( target->accessMethods() );

    connect ( target, SIGNAL ( requestCompleted ( QNearFieldTarget::RequestId ) ),
              clientSocket, SIGNAL ( requestCompleted ( QNearFieldTarget::RequestId ) ) );
    connect ( target, SIGNAL ( error ( QNearFieldTarget::Error, QNearFieldTarget::RequestId ) ),
              clientSocket, SIGNAL ( error ( QNearFieldTarget::Error, QNearFieldTarget::RequestId ) ) );
    //connect(target, SIGNAL(destroyed(QObject*)),
    //        clientSocket, SIGNAL(destroyed(QObject*)));

    //connect(target, SIGNAL(disconnected()),
    //        clientSocket, SIGNAL(disconnected()));

    connect ( target, SIGNAL ( ndefMessageRead ( QNdefMessage ) ),
              clientSocket, SIGNAL ( ndefMessageRead ( QNdefMessage ) ) );
    connect ( target, SIGNAL ( ndefMessagesWritten() ),
              clientSocket, SIGNAL ( ndefMessagesWritten() ) );

    QQtProtocol* protocol = m_protocolManager->createProtocol();
    clientSocket->installProtocol ( protocol );
    m_clientList.push_back ( clientSocket );
}

void QQtNfcServer::hasTargetLosted ( QNearFieldTarget* target )
{
    pline();
    QQtNfcClient* clientSocket = findInstanceByUid ( target->uid() );
    target->deleteLater();

    if ( !clientSocket )
        return;
    QQtProtocol* protocol = clientSocket->installedProtocol();
    clientSocket->uninstallProtocol ( protocol );
    clientSocket->deleteLater();
    m_clientList.removeOne ( clientSocket );
    m_protocolManager->deleteProtocol ( protocol );
}

QQtNfcClient* QQtNfcServer::findInstanceByUid ( QByteArray uid )
{
    QListIterator<QQtNfcClient*> itor ( m_clientList );
    while ( itor.hasNext() )
    {
        QQtNfcClient* inst = itor.next();
        if ( inst->uid() == uid )
            return inst;
    }
    return 0;
}
