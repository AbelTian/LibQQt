#ifndef QQTMOUSELOCKER_OTHER_H
#define QQTMOUSELOCKER_OTHER_H

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

#endif //QQTMOUSELOCKER_OTHER_H
