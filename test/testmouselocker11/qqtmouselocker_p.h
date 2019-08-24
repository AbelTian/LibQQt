#ifndef QQTMOUSELOCKER_P_H
#define QQTMOUSELOCKER_P_H

#include <QtCore/qglobal.h>

#include <QMouseEvent>

#ifdef __DESKTOP_WIN__
#include "qqtmouselocker_win.h"
#elif defined (__DESKTOP_DARWIN__)
#include "qqtmouselocker_mac.h"
#elif defined (__DESKTOP_LINUX__)
#include "qqtmouselocker_x11.h"
#else
#include "qqtmouselocker_other.h"
#endif

class QQtMouseLocker;
class QQtMouseLockerPrivate
{
public:
    QQtMouseLockerPrivate ( QQtMouseLocker* q );
    ~QQtMouseLockerPrivate();

public:
    virtual void focusInEvent ( QFocusEvent* event, QWidget* target = 0 );
    virtual void focusOutEvent ( QFocusEvent* event, QWidget* target = 0 );
    virtual void mouseMoveEvent ( QMouseEvent* event, QWidget* target = 0 );

private:
    QQtMouseLocker* q_ptr;
    Q_DECLARE_PUBLIC ( QQtMouseLocker )

    QQtMouseLockerImpl* i_ptr;
};

#endif //QQTMOUSELOCKER_P_H
