#include "qqtmouselocker_p.h"
#include "qqtmouselocker.h"

QQtMouseLockerPrivate::QQtMouseLockerPrivate ( QQtMouseLocker* q )
{
    q_ptr = q;
    i_ptr = new QQtMouseLockerImpl();
}

QQtMouseLockerPrivate::~QQtMouseLockerPrivate()
{
    delete i_ptr;
}

void QQtMouseLockerPrivate::focusInEvent ( QFocusEvent* event, QWidget* target )
{
    i_ptr->focusInEvent ( event, target );
}

void QQtMouseLockerPrivate::focusOutEvent ( QFocusEvent* event, QWidget* target )
{
    i_ptr->focusOutEvent ( event, target );
}

void QQtMouseLockerPrivate::mouseMoveEvent ( QMouseEvent* event, QWidget* target )
{
    i_ptr->mouseMoveEvent ( event, target );
}
