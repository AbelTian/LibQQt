#include "qqtlogicvideomanager.h"
#include "qqtlogicvideomanager_p.h"

QQtLogicVideoInput::QQtLogicVideoInput ( QObject* parent ) :
    d_ptr ( new QQtLogicVideoInputPrivate ( this, this ) ), QObject ( parent )
{
}

QQtLogicVideoInput::~QQtLogicVideoInput()
{
    Q_D ( QQtLogicVideoInput );
    d->deleteLater();
}

bool QQtLogicVideoInput::open ( QString devName )
{
    Q_D ( QQtLogicVideoInput );
    return d->open ( devName );
}

bool QQtLogicVideoInput::close()
{
    Q_D ( QQtLogicVideoInput );
    return d->close();
}

QQtLogicVideoManager::QQtLogicVideoManager ( QObject* parent )
    : QObject ( parent )
{
    mInputManager = new QQtLogicVideoInput ( this );
    connect ( mInputManager, SIGNAL ( readyRead ( const QImage& ) ),
              this, SIGNAL ( readyRead ( const QImage& ) ) );
}

QQtLogicVideoManager::~QQtLogicVideoManager() {}

bool QQtLogicVideoManager::openInput ( QString devName )
{
    return mInputManager->open ( devName );
}

bool QQtLogicVideoManager::closeInput()
{
    return mInputManager->close();
}
