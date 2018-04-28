#include "qqthgprotocolmanager.h"

QQtHgProtocolManager::QQtHgProtocolManager ( QObject* parent ) : QObject ( parent )
{

}

QQtHgProtocolManager::~QQtHgProtocolManager()
{

}

void QQtHgProtocolManager::installProtocol ( QQtHgProtocol* stack )
{
    if ( mProtoList.contains ( stack ) )
        return;

    mProtoList.push_back ( stack );
    connect ( stack, SIGNAL ( notifyToHgProtocolManager ( const QAbstractSocket*, const QQtHgProtocol*,
                                                          const QQtMessage*  ) ),
              this, SIGNAL ( notifyToBusinessLevel ( const QAbstractSocket*, const QQtHgProtocol*, const QQtMessage* ) ) );
}

void QQtHgProtocolManager::uninstallProtocol ( QQtHgProtocol* stack )
{
    if ( !mProtoList.contains ( stack ) )
        return;

    mProtoList.removeOne ( stack );
    disconnect ( stack, SIGNAL ( notifyToHgProtocolManager ( const QAbstractSocket*, const QQtHgProtocol*,
                                                             const QQtMessage*  ) ),
                 this, SIGNAL ( notifyToBusinessLevel ( const QAbstractSocket*, const QQtHgProtocol*, const QQtMessage* ) ) );
}

QList<QQtHgProtocol*>& QQtHgProtocolManager::installedProtocol()
{
    return mProtoList;
}

