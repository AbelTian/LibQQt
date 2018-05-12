#include "qqtlabel.h"

QQtLabel::QQtLabel ( QWidget* parent ) : QLabel ( parent )
{
    m_lcTimer = new QTimer ( this );
    m_lcTimer->setSingleShot ( true );
    m_lcTimer->setInterval ( 2200 );
    connect ( m_lcTimer, SIGNAL ( timeout() ),
              this, SLOT ( slot_timeout() ) );
}


void QQtLabel::mouseReleaseEvent ( QMouseEvent* event )
{
    if ( m_lcTimer->isActive() )
    {
        m_lcTimer->stop();
        emit click();
    }

    return QLabel::mouseReleaseEvent ( event );
}


void QQtLabel::mouseDoubleClickEvent ( QMouseEvent* event )
{
    emit doubleClick();
    return QLabel::mouseDoubleClickEvent ( event );
}

void QQtLabel::slot_timeout()
{
    emit longClick();
}


void QQtLabel::mousePressEvent ( QMouseEvent* event )
{
    m_lcTimer->start();
    return QLabel::mousePressEvent ( event );
}
