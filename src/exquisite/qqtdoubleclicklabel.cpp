#include "qqtdoubleclicklabel.h"

QQtDoubleClickLabel::QQtDoubleClickLabel ( QWidget* parent ) :
    QQtCanClickLabel ( parent )
{
    mClickHelper = new QQtDoubleClickHelper ( this );
    installClickHelper();
}

QQtDoubleClickLabel::~QQtDoubleClickLabel()
{
}

void QQtDoubleClickLabel::installClickHelper()
{
    if ( !mClickHelper )
        return;
    connect ( mClickHelper, SIGNAL ( click() ), this, SIGNAL ( click() ) );
    connect ( mClickHelper, SIGNAL ( longClick() ), this, SIGNAL ( longClick() ) );
    connect ( mClickHelper, SIGNAL ( doubleClick() ), this, SIGNAL ( doubleClick() ) );
    connect ( mClickHelper, SIGNAL ( clickWithPoint ( QPoint ) ), this, SIGNAL ( clickWithPoint ( QPoint ) ) );
    connect ( mClickHelper, SIGNAL ( longClickWithPoint ( QPoint ) ), this, SIGNAL ( longClickWithPoint ( QPoint ) ) );
    connect ( mClickHelper, SIGNAL ( doubleClickWithPoint ( QPoint ) ), this, SIGNAL ( doubleClickWithPoint ( QPoint ) ) );
}

void QQtDoubleClickLabel::uninstallClickHelper()
{
    if ( !mClickHelper )
        return;
    disconnect ( mClickHelper, SIGNAL ( click() ), this, SIGNAL ( click() ) );
    disconnect ( mClickHelper, SIGNAL ( longClick() ), this, SIGNAL ( longClick() ) );
    disconnect ( mClickHelper, SIGNAL ( doubleClick() ), this, SIGNAL ( doubleClick() ) );
    disconnect ( mClickHelper, SIGNAL ( clickWithPoint ( QPoint ) ), this, SIGNAL ( clickWithPoint ( QPoint ) ) );
    disconnect ( mClickHelper, SIGNAL ( longClickWithPoint ( QPoint ) ), this, SIGNAL ( longClickWithPoint ( QPoint ) ) );
    disconnect ( mClickHelper, SIGNAL ( doubleClickWithPoint ( QPoint ) ), this,
                 SIGNAL ( doubleClickWithPoint ( QPoint ) ) );
}
