#ifndef QQTMOUSELOCKER_X11_H
#define QQTMOUSELOCKER_X11_H

#include <QMouseEvent>
#include <QWidget>

class QQtMouseLockerImpl
{
public:
    explicit QQtMouseLockerImpl();

public:
    virtual void focusInEvent ( QFocusEvent* event, QWidget* target = 0 );
    virtual void focusOutEvent ( QFocusEvent* event, QWidget* target = 0 );
    virtual void mouseMoveEvent ( QMouseEvent* event, QWidget* target = 0 );
};

#endif //QQTMOUSELOCKER_X11_H
