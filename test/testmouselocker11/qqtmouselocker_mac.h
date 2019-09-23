#ifndef QQTMOUSELOCKER_MAC_H
#define QQTMOUSELOCKER_MAC_H

#include <QMouseEvent>
#include <QWidget>

#include <QThread>


class QQtLockMouseThreadHelper : public QThread
{
    Q_OBJECT
public:
    QQtLockMouseThreadHelper ( QObject* parent = 0 );
    virtual ~QQtLockMouseThreadHelper();

    // QThread interface
protected:
    virtual void run() override;
};

class QQtMouseLockerImpl
{
public:
    explicit QQtMouseLockerImpl();

public:
    virtual void focusInEvent ( QFocusEvent* event, QWidget* target = 0 );
    virtual void focusOutEvent ( QFocusEvent* event, QWidget* target = 0 );
    virtual void mouseMoveEvent ( QMouseEvent* event, QWidget* target = 0 );
};

#endif //QQTMOUSELOCKER_MAC_H
