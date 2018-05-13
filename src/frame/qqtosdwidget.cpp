#include "qqtosdwidget.h"

QQtOSDWidget::QQtOSDWidget ( QWidget* parent ) : QQtWidget ( parent )
{
    setAttribute ( Qt::WA_TranslucentBackground, true );
    setAttribute ( Qt::WA_TransparentForMouseEvents, true );
}
