#ifndef QQTBODYMOUSELOCKER_P_H
#define QQTBODYMOUSELOCKER_P_H

#include <QtCore/qglobal.h>
#include <QMouseEvent>
#include <QThread>

class QQtBodyMouseMouseLockerThreadHelper : public QThread
{
    Q_OBJECT
public:
    QQtBodyMouseMouseLockerThreadHelper ( QObject* parent = 0 );
    virtual ~QQtBodyMouseMouseLockerThreadHelper();

    void setTargetWidget ( QWidget* target );

    void startCapture();
    void stopCapture();

    // QThread interface
protected:
    virtual void run() override;

private:
    QMutex tex;
    QWidget* target;
    bool workflag;
};

class QQtBodyMouseLocker;
class QQtBodyMouseLockerPrivate
{
public:
    QQtBodyMouseLockerPrivate ( QQtBodyMouseLocker* q );
    virtual ~QQtBodyMouseLockerPrivate();

    void startCapture();
    void stopCapture();

    void addWindow ( QWidget* target );
    void removeWindow ( QWidget* target );

protected:
    virtual void focusInEvent ( QFocusEvent* event, QWidget* target = 0 );
    virtual void focusOutEvent ( QFocusEvent* event, QWidget* target = 0 );
    virtual void mouseMoveEvent ( QMouseEvent* event, QWidget* target = 0 );

private:
    QQtBodyMouseLocker* q_ptr;
    Q_DECLARE_PUBLIC ( QQtBodyMouseLocker )

    QQtBodyMouseMouseLockerThreadHelper* helper;
};

#endif //QQTBODYMOUSELOCKER_P_H
