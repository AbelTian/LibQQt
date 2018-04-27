#include "qqthgprotocol.h"

QQtHgProtocol::QQtHgProtocol ( QObject* parent ) : QObject ( parent )
{

}

QQtHgProtocol::~QQtHgProtocol()
{

}

void QQtHgProtocol::createClientBuffer ( const QAbstractSocket* client )
{
    if ( mClientBuffer.contains ( client ) )
        return;

    mClientBuffer.insert ( client, QByteArray() );
}

void QQtHgProtocol::deleteClientBuffer ( const QAbstractSocket* client )
{
    if ( !mClientBuffer.contains ( client ) )
        return;

    mClientBuffer.remove ( client );
}
