#include "qqtdoubleclickwidget.h"

QQtDoubleClickWidget::QQtDoubleClickWidget ( QWidget* parent ) :
    QQtCanClickWidget ( parent )
{
    mClickHelper = new QQtDoubleClickHelper ( this );
    installClickHelper();
}

QQtDoubleClickWidget::~QQtDoubleClickWidget()
{
}

void QQtDoubleClickWidget::installClickHelper()
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

void QQtDoubleClickWidget::uninstallClickHelper()
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

