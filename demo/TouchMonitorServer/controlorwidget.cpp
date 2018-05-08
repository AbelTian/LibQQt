#include "controlorwidget.h"

ControlorWidget::ControlorWidget ( QWidget* parent ) : QQtOSDWidget ( parent )
{
    setWindowFlag ( Qt::FramelessWindowHint, true );
}
