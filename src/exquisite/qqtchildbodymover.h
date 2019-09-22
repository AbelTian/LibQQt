#ifndef QQTCHILDBODYMOVER_H
#define QQTCHILDBODYMOVER_H

#include <QObject>
#include <QMargins>
#include <QMouseEvent>
#include <QWidget>

#include <qqt-local.h>

/**
 * @brief The QQtChildBodyMover class
 * 摁住子窗体就能在父窗体里移动
 *
 * 允许使用这一个句柄为多个窗口安装，各自独立工作，互不干扰。
 * 应用于子窗口，会导致其在主窗口中移动。
 * 应用于主窗体，能正常移动。
 * 在Windows、macOS、Linux等系统下表现一致。
 */
class QQTSHARED_EXPORT QQtChildBodyMover : public QObject
{
    Q_OBJECT
public:
    QQtChildBodyMover ( QObject* parent = 0 );
    virtual ~QQtChildBodyMover();

    QMargins& margins();

protected:
    virtual void mousePressEvent ( QMouseEvent* event, QWidget* target = 0 );
    virtual void mouseReleaseEvent ( QMouseEvent* event, QWidget* target = 0 );
    virtual void mouseMoveEvent ( QMouseEvent* event, QWidget* target = 0 );

    // QObject interface
public:
    virtual bool eventFilter ( QObject* watched, QEvent* event ) override;

private:
    bool bMousePressed;
    QPoint pressedPoint;

    QMargins m_margins;
};


#endif // QQTCHILDBODYMOVER_H
