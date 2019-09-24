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
 * 允许实时手动添加、移除需要锁定鼠标的窗口，add/removeWindow(w);
 * 允许实时手动开启、停止锁定功能，start/stopCapture(); //默认开启
 *
 * 允许使用这一个句柄为多个窗口安装，各自独立工作，互不干扰。
 * setMouseTracking(true) 鼠标划过就能捕获
 * setMouseTracking(false) 鼠标点击才能捕获
 *
 * 在窗口从非active到active的时候，不会立即捕获鼠标，需要用户自行实现，
 * 方法：安装目标窗口eventFilter到Root窗口，实现WindowActivate，把titlebar过滤出去，手动设置、移除目标窗体，然后return true。
 * 这样，在启动时捕获鼠标也可以了。testmouselocker11介绍了使用方法。
 * 这个功能不简单。
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

public:
    //这里开启、停止锁定功能。默认已经开启。
    void startCapture();
    void stopCapture();

    //这里添加需要锁定的窗口。[可以重复添加，每次只会一个rect生效，其实就是设置新的rect。]
    void addWindow ( QWidget* target );
    //移除锁定的窗口。其实就是把rect置0.
    void removeWindow ( QWidget* target );

    /*
     * 有的时候，用户希望自己设置rect来达到锁定鼠标的目的。
     */

    //允许设置需要锁定的区域 QRect(0,0,0,0)为关闭。 = ClipCursor 输入全局坐标即可。
    void addClipCursor ( const QRect globalRect );
    //获取锁定区域
    QRect getClipCursor();

    //根据target窗口求出目标锁定区域，去除margin用。如果没有这个margin，锁定状态下根本无法放大。Scaled.
    QRect getContentRect ( QWidget* target );
    //根据target窗口求出target的区域。Scaled.
    QRect getSourceRect ( QWidget* target );

    // QObject interface
protected:
    virtual bool eventFilter ( QObject* watched, QEvent* event ) override;

private:
    QQtBodyMouseLockerPrivate* d_ptr;
    Q_DECLARE_PRIVATE ( QQtBodyMouseLocker )
};

//如果用户感兴趣
QQTSHARED_EXPORT void QQtClipCursor ( const QRect globalRect );
QQTSHARED_EXPORT QRect QQtGetClipCursor ( );

QQTSHARED_EXPORT void QQtClipCursorToWindow ( QWidget* target );


/* example
bool MainWindow::eventFilter ( QObject* watched, QEvent* event )
{
    if ( event->type() == QEvent::Paint )
        return QObject::eventFilter ( watched, event );
    switch ( event->type() )
    {
        case QEvent::WindowActivate:
        {
            //原来答案在这里，用户如果希望窗口在activate的时候，目标窗口捕获鼠标，可是还要过滤掉标题栏，在这里实现！
            QMouseEvent* e = ( QMouseEvent* ) event;
            //QRect r0 = frameGeometry();
            //QRect r1 = geometry();
            //if ( r0.contains ( e->globalPos() ) && !r1.contains ( e->globalPos() ) )
            //    helper->stopCapture();

            QWidget& w = *this;
            QRect frameR0 = frameGeometry();
            QPoint p0, p1;
            p0 = frameR0.topLeft();
            p1 = frameR0.bottomRight();
            //p0 = w.mapToGlobal ( p0 );
            //p1 = w.mapToGlobal ( p1 );

            QPoint mousePos = QCursor::pos();

            qreal ratio = 1; w.devicePixelRatioF();
            QRect r0 = QRect ( p0, p1 );
            QRect qr0 = QRect ( QPoint ( r0.left() * ratio, r0.top() * ratio ),
                                QPoint ( r0.right() * ratio, r0.bottom() * ratio ) );

            QRect r1 = rect();
            QRect qr1 = QRect ( w.mapToGlobal ( r1.topLeft() ), w.mapToGlobal ( r1.bottomRight() ) );
            r1 = geometry();

            if ( qr0.contains ( mousePos ) && !qr1.contains ( mousePos ) )
                helper->removeWindow ( ui->widget ); //helper->addWindow ( ui->widget );
            else
                helper->addWindow ( ui->widget );
            event->accept();
            pline() << qr0 << qr1 << mousePos;
            return true;

        }
    }
    return QMainWindow::eventFilter ( watched, event );
}
*/

#endif // QQTBODYMOUSELOCKER_H
