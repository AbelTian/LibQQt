#include "qqtclicklabel.h"

QQtClickLabel::QQtClickLabel ( QWidget* parent ) :
    QQtCanClickLabel ( parent )
{
    mClickHelper = new QQtClickHelper ( this );
    installClickHelper();
}

QQtClickLabel::~QQtClickLabel()
{
}

void QQtClickLabel::installClickHelper()
{
    if ( !mClickHelper )
        return;

    connect ( mClickHelper, SIGNAL ( click() ), this, SIGNAL ( click() ) );
    connect ( mClickHelper, SIGNAL ( longClick() ), this, SIGNAL ( longClick() ) );
    connect ( mClickHelper, SIGNAL ( clickWithPoint ( QPoint ) ), this, SIGNAL ( clickWithPoint ( QPoint ) ) );
    connect ( mClickHelper, SIGNAL ( longClickWithPoint ( QPoint ) ), this, SIGNAL ( longClickWithPoint ( QPoint ) ) );
}

void QQtClickLabel::uninstallClickHelper()
{
    if ( !mClickHelper )
        return;

    disconnect ( mClickHelper, SIGNAL ( click() ), this, SIGNAL ( click() ) );
    disconnect ( mClickHelper, SIGNAL ( longClick() ), this, SIGNAL ( longClick() ) );
    disconnect ( mClickHelper, SIGNAL ( clickWithPoint ( QPoint ) ), this, SIGNAL ( clickWithPoint ( QPoint ) ) );
    disconnect ( mClickHelper, SIGNAL ( longClickWithPoint ( QPoint ) ), this, SIGNAL ( longClickWithPoint ( QPoint ) ) );
}

