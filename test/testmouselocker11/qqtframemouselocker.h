#ifndef QQTFRAMEMOUSELOCKER_H
#define QQTFRAMEMOUSELOCKER_H

#include <QObject>
#include <QWidget>

/**
 * @brief The QQtFrameMouseLocker class
 * 将鼠标移动轨迹锁定在窗口内部。
 *
 * 使用方法：
 * QWidget* w;//需要锁定鼠标的窗口。
 * w->setMouseTracking(True);//必要
 * //w->setFocusPolicy(Qt::StrongFocus);//不必要设置Focus。
 * QQtFrameMouseLocker* helper = new QQtFrameMouseLocker(parent) ;
 * w->installEventFilter(helper);//一步设置即可。
 * 允许使用这一个句柄为多个窗口安装，各自独立工作，互不干扰。
 *
 * 工作原理：
 * 在鼠标move的时候，截获鼠标消息，将其锁定。
 * 支持所有QWidget，不支持QMainWindow。
 * 支持windows、macOS、Linux。
 */
class QQtFrameMouseLocker : public QObject
{
    Q_OBJECT
public:
    QQtFrameMouseLocker ( QObject* parent = 0 );
    virtual ~QQtFrameMouseLocker();

    void attachClipCursor ( QWidget* targetWidget ) {}
    void detachClipCursor ( QWidget* targetWidget ) {}

    // QObject interface
public:
    virtual bool eventFilter ( QObject* watched, QEvent* event ) override;

protected:
    virtual void focusInEvent ( QFocusEvent* event, QWidget* target = 0 );
    virtual void focusOutEvent ( QFocusEvent* event, QWidget* target = 0 );
    virtual void mouseMoveEvent ( QMouseEvent* event, QWidget* target = 0 );
};

#endif // QQTFRAMEMOUSELOCKER_H
