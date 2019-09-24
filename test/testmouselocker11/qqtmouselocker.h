#ifndef QQTMOUSELOCKER_H
#define QQTMOUSELOCKER_H

#include <QObject>

//#include "qqt-local.h"
#define QQTSHARED_EXPORT

/**
 * @brief The QQtMouseLocker class
 * 将鼠标移动轨迹锁定在窗口内部。
 *
 * 使用方法：
 * QWidget* w;//需要锁定鼠标的窗口。
 * //w->setMouseTracking(True);//不必要
 * //w->setFocusPolicy(Qt::StrongFocus);//不必要设置Focus。
 * QQtMouseLocker* helper = new QQtMouseLocker(parent) ;
 * helper->lockWindow(w);//一步设置即可。
 * helper->unlockWindow(w);//如果不使用了
 * 允许使用这一个句柄为多个窗口安装，各自独立工作，互不干扰。
 *
 * 工作原理：
 * 在鼠标move的时候，截获鼠标消息，将其锁定。
 * 支持所有QWidget及其子类，不支持QMainWindow。
 * 支持windows、macOS、Linux等桌面操作系统。
 */
class QQtMouseLockerPrivate;
class QQTSHARED_EXPORT QQtMouseLocker : public QObject
{
    Q_OBJECT

public:
    QQtMouseLocker ( QObject* parent = 0 );
    virtual ~QQtMouseLocker();

    //这里是开关锁定作用的接口。
    void lockWindow ( QWidget* target );
    void unlockWindow ( QWidget* target );

    //用户不可以installEventFilter。

    // QObject interface
protected:
    virtual bool eventFilter ( QObject* watched, QEvent* event ) override;

private:
    QQtMouseLockerPrivate* d_ptr;
    Q_DECLARE_PRIVATE ( QQtMouseLocker )
};

#endif // QQTMOUSELOCKER_H
