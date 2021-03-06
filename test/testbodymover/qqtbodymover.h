#ifndef QQTBODYMOVER_H
#define QQTBODYMOVER_H

#include <QObject>

//#include "qqt-local.h"
#define QQTSHARED_EXPORT

/**
 * @brief The QQtBodyMover class
 * 摁住窗体就能移动窗口。
 *
 * 使用方法：
 * QWidget* w;//需要锁定鼠标的窗口。
 * w->setMouseTracking(True);//不必要
 * //w->setFocusPolicy(Qt::StrongFocus);//不必要设置Focus。
 * QQtBodyMover* helper = new QQtBodyMover(parent) ;
 * w->installEventFilter(helper);//一步设置即可。
 * 允许使用这一个句柄为多个窗口安装，各自独立工作，互不干扰。
 *
 * 工作原理：
 * 在鼠标move的时候，截获鼠标消息，使窗口移动。
 * 支持所有QWidget及其子类，不支持QMainWindow。
 * 支持windows、macOS、Linux等桌面操作系统。
 */
class QQtBodyMoverPrivate;
class QQTSHARED_EXPORT QQtBodyMover : public QObject
{
    Q_OBJECT

public:
    QQtBodyMover ( QObject* parent = 0 );
    ~QQtBodyMover();

    // QObject interface
public:
    virtual bool eventFilter ( QObject* watched, QEvent* event ) override;

private:
    QQtBodyMoverPrivate* d_ptr;
    Q_DECLARE_PRIVATE ( QQtBodyMover )
};

#endif // QQTBODYMOVER_H
