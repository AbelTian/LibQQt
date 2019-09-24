#ifndef QQTBODYMOUSELOCKER_H
#define QQTBODYMOUSELOCKER_H

#include <QObject>
#include <QWidget>
#include <QEvent>

#include "qqt-local.h"

/**
 * @brief The QQtBodyMouseLocker class
 * 将鼠标移动轨迹锁定在窗口内部。
 *
 * 使用方法：
 * QWidget* w;                              //需要锁定鼠标的窗口。
 * //w->setMouseTracking(True);             //不必要。
 * //w->setFocusPolicy(Qt::StrongFocus);    //不必要设置Focus。
 * QQtBodyMouseLocker* helper = new QQtBodyMouseLocker(parent) ;
 * w->installEventFilter(helper);           //一步设置即可。
 *
 * 手动使用方法：
 * 用户可以不用installEventFilter的方法，
 * 允许实时手动添加、移除需要锁定鼠标的窗口，add/removeWindow(w);
 * 允许实时手动开启、停止锁定功能，start/stopCapture(); //默认开启
 *
 * 允许使用这一个句柄为多个窗口安装，各自独立工作，互不干扰。
 * setMouseTracking(true) 鼠标划过就能捕获
 * setMouseTracking(false) 鼠标点击才能捕获
 * 无论mouseTracking如何，在窗口从非active到active的时候，最近一次捕获鼠标的窗口，会立即捕获鼠标。
 *
 * 功能约束：
 * 用户必须手动停止capture，内部也有帮助停止，但是还是要依赖手动停止，
 * 或者，用户必须手动delete本helper，在delete ui之前释放掉。
 * 两者选1，要不然程序会崩溃。
 * 简而言之，用户在释放ui之前必须手动停掉本locker的线程，用stopCapture()，或者，必须手动释放本locker，触发内部关闭线程。
 * 只要内部线程关闭了，应用程序想什么时候释放本locker的资源就什么时候释放。
 *
 * 内部检测widget的activeWindow状态，是个异步检测，强烈依赖widget存在。
 * 在开启本locker之前，必须把ui准备好。
 * 在关停程序、释放ui之前，无论如何要先关掉本helper。
 *
 * 工作原理：
 * 在鼠标move的时候，截获鼠标消息，将其锁定。
 * 支持所有QWidget及其子类。
 * 支持windows、macOS、Linux等桌面操作系统，行为表现一致。
 */
class QQtBodyMouseLockerPrivate;
class QQTSHARED_EXPORT QQtBodyMouseLocker : public QObject
{
    Q_OBJECT

public:
    QQtBodyMouseLocker ( QObject* parent = 0 );
    virtual ~QQtBodyMouseLocker();

    //这里开启、停止锁定功能。默认已经开启。
    void startCapture();
    void stopCapture();

    //这里添加、移除需要锁定的窗口。[和内部的自动过程有很多重复，无所谓了。]
    void addWindow ( QWidget* target );
    void removeWindow ( QWidget* target );

    // QObject interface
protected:
    virtual bool eventFilter ( QObject* watched, QEvent* event ) override;

private:
    QQtBodyMouseLockerPrivate* d_ptr;
    Q_DECLARE_PRIVATE ( QQtBodyMouseLocker )
};

#endif // QQTBODYMOUSELOCKER_H
