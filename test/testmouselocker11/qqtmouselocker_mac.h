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

    void setTargetWidget ( QWidget* target );

    void startThread();
    void stopThread();

    // QThread interface
protected:
    virtual void run() override;

private:
    QMutex tex;
    QWidget* target;

    bool workflag;
};

class QQtMouseLockerImpl
{
public:
    explicit QQtMouseLockerImpl ( );
    virtual ~QQtMouseLockerImpl();

    void lockWindow ( QWidget* target );
    void unlockWindow ( QWidget* target );

public:
    virtual void focusInEvent ( QFocusEvent* event, QWidget* target = 0 );
    virtual void focusOutEvent ( QFocusEvent* event, QWidget* target = 0 );
    virtual void mouseMoveEvent ( QMouseEvent* event, QWidget* target = 0 );

private:
    QQtLockMouseThreadHelper* helper;
};

#endif //QQTMOUSELOCKER_MAC_H
