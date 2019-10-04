#ifndef QQTROOTBODYMOVER_H
#define QQTROOTBODYMOVER_H

#include <QObject>
#include <QMouseEvent>
#include <QMargins>

#include <qqt-local.h>
/**
 * @brief The QQtRootBodyMover class
 * 摁住窗体就能移动窗口。
 *
 * 使用方法：
 * QWidget* w;//需要实现这个功能的窗口。
 * w->setMouseTracking(True);//不必要
 * //w->setFocusPolicy(Qt::StrongFocus);//不必要设置Focus。
 * QQtBodyMover* helper = new QQtBodyMover(parent) ;
 * w->installEventFilter(helper);//一步设置即可。
 * 允许使用这一个句柄为多个窗口安装，各自独立工作，互不干扰。
 * 允许用户设置适当的margins
 *
 * 工作原理：
 * 在鼠标move的时候，截获鼠标消息，使窗口移动。
 * 支持所有QWidget及其子类，不支持QMainWindow。
 * 支持windows、macOS、Linux、e-linux等操作系统。
 *
 * 应用于子窗口，会导致窗口整体移动。
 * 应用于主窗口，能够正常移动，Windows下还会有titlebar的作用。
 * 在Windows、macOS、Linux等系统下表现一致。
 *
 */
class QQTSHARED_EXPORT QQtRootBodyMover : public QObject
{
    Q_OBJECT

public:
    explicit QQtRootBodyMover ( QObject* parent = 0 );
    virtual ~QQtRootBodyMover();

protected:
    virtual void mousePressEvent ( QMouseEvent* event, QWidget* target = 0 );
    virtual void mouseReleaseEvent ( QMouseEvent* event, QWidget* target = 0 );
    virtual void mouseMoveEvent ( QMouseEvent* event, QWidget* target = 0 );

private:
    bool bMousePressed;
    QPoint pressedPoint;

    // QObject interface
public:
    virtual bool eventFilter ( QObject* watched, QEvent* event ) override;
};

#endif // QQTROOTBODYMOVER_H

