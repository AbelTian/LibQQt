#include "qqtlogicvideomanager.h"
#include "qqtlogicvideomanager_p.h"

QQtLogicVideoManager::QQtLogicVideoManager ( QObject* parent ) :
    d_ptr ( new QQtLogicVideoManagerPrivate ( this, this ) ), QObject ( parent )
{
}

QQtLogicVideoManager::~QQtLogicVideoManager()
{
    Q_D ( QQtLogicVideoManager );
    d->deleteLater();
}

bool QQtLogicVideoManager::open ( QString devName )
{
    Q_D ( QQtLogicVideoManager );
    return d->open ( devName );
}

bool QQtLogicVideoManager::close()
{
    Q_D ( QQtLogicVideoManager );
    return d->close();
}
