#ifndef QQTBODYMOUSELOCKER_WIN_H
#define QQTBODYMOUSELOCKER_WIN_H

#include <QtCore/qglobal.h>
#include <QRect>
#include <QWidget>

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

    //根据target窗口求出target的区域，在windows下这个数值是需要放大的。SetHighDPIScaling
    static QRect getSourceRect ( QWidget* target );

    //允许手动开关
    void startCapture();
    void stopCapture();

private:
    QQtBodyMouseLocker* q_ptr;
    Q_DECLARE_PUBLIC ( QQtBodyMouseLocker )
};

#endif //QQTBODYMOUSELOCKER_WIN_H
