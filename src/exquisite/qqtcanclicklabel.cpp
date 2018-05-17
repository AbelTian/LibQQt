#include "qqtcanclicklabel.h"

QQtCanClickLabel::QQtCanClickLabel ( QWidget* parent ) :
    QQtLabel ( parent )
{
    mClickHelper = 0;
}

QQtCanClickLabel::~QQtCanClickLabel()
{
}


void QQtCanClickLabel::mousePressEvent ( QMouseEvent* event )
{
    if ( mClickHelper )
        mClickHelper->mousePressEvent ( event, this );
    return QQtLabel::mousePressEvent ( event );
}

void QQtCanClickLabel::mouseReleaseEvent ( QMouseEvent* event )
{
    if ( mClickHelper )
        mClickHelper->mouseReleaseEvent ( event, this );
    return QQtLabel::mouseReleaseEvent ( event );
}

void QQtCanClickLabel::mouseDoubleClickEvent ( QMouseEvent* event )
{
    if ( mClickHelper )
        mClickHelper->mouseDoubleClickEvent ( event, this );
    return QQtLabel::mouseDoubleClickEvent ( event );
}


