#include "qqtcanclickwidget.h"

QQtCanClickWidget::QQtCanClickWidget ( QWidget* parent ) :
    QQtWidget ( parent )
{
    mClickHelper = 0;
}

QQtCanClickWidget::~QQtCanClickWidget()
{
}


void QQtCanClickWidget::mousePressEvent ( QMouseEvent* event )
{
//    if ( mClickHelper )
//        mClickHelper->mousePressEvent ( event, this );
    return QQtWidget::mousePressEvent ( event );
}

void QQtCanClickWidget::mouseReleaseEvent ( QMouseEvent* event )
{
    if ( mClickHelper )
        mClickHelper->mouseReleaseEvent ( event, this );
    return QQtWidget::mouseReleaseEvent ( event );
}

void QQtCanClickWidget::mouseDoubleClickEvent ( QMouseEvent* event )
{
    if ( mClickHelper )
        mClickHelper->mouseDoubleClickEvent ( event, this );
    return QQtWidget::mouseDoubleClickEvent ( event );
}


