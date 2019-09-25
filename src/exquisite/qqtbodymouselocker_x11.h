#ifndef QQTBODYMOUSELOCKER_X11_H
#define QQTBODYMOUSELOCKER_X11_H

#include <QtCore/qglobal.h>
#include <QMouseEvent>
#include <QThread>
#include <QMutex>

class QQtBodyMouseMouseLockerThreadHelper : public QThread
{
    Q_OBJECT

public:
    //建议初始化
    static QQtBodyMouseMouseLockerThreadHelper* instance ( QObject* parent = 0 ) {
        static QQtBodyMouseMouseLockerThreadHelper* helper = 0;
        if ( !helper )
            helper = new QQtBodyMouseMouseLockerThreadHelper ( parent );
        return helper;
    }

    void setTargetGlobalRect ( QRect globalRect );
    QRect getTargetGlobalRect ();

    void startCapture();
    void stopCapture();

private:
    QQtBodyMouseMouseLockerThreadHelper ( QObject* parent = 0 );
    virtual ~QQtBodyMouseMouseLockerThreadHelper();

    // QThread interface
protected:
    virtual void run() override;

private:
    QMutex tex;
    QRect mGlobalRect;
    bool workflag;
};

class QQtBodyMouseLocker;
class QQtBodyMouseLockerPrivate
{
public:
    QQtBodyMouseLockerPrivate ( QQtBodyMouseLocker* q );
    virtual ~QQtBodyMouseLockerPrivate();

    //允许设置需要锁定的区域 QRect(0,0,0,0)为关闭。 = ClipCursor 输入全局坐标即可。
    void addRect ( const QRect globalRect );
    QRect getRect();

    //允许按照窗口进行定义
    void addWindow ( QWidget* target );

    //根据target窗口求出目标锁定区域，去除margin用。如果没有这个margin，锁定状态下根本无法放大。
    static QRect getTargetRect ( QWidget* target );

    //根据target窗口求出target的区域。SetHighDPIScaling
    static QRect getSourceRect ( QWidget* target );

    //允许手动开关
    void startCapture();
    void stopCapture();

private:
    QQtBodyMouseLocker* q_ptr;
    Q_DECLARE_PUBLIC ( QQtBodyMouseLocker )

    QQtBodyMouseMouseLockerThreadHelper* helper;
};

#endif // QQTBODYMOUSELOCKER_X11_H
