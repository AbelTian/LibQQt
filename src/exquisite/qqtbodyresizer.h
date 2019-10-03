#ifndef QQTBODYRESIZER_H
#define QQTBODYRESIZER_H

#include <QObject>
#include <QMargins>

#include "qqt-local.h"

/**
 * @brief The QQtBodyResizer class
 * 摁住窗体的边缘就能伸缩窗体。
 *
 * 使用方法：
 * QWidget* w;//需要实现功能的窗口。
 * w->setMouseTracking(True);//必要 !!!
 * //w->setFocusPolicy(Qt::StrongFocus);//不必要设置Focus。
 * QQtBodyResizer* helper = new QQtBodyResizer(parent) ;
 * w->installEventFilter(helper);//一步设置即可。
 * 允许使用这一个句柄为多个窗口安装，各自独立工作，互不干扰。
 * 要求用户设置适当的margins
 *
 * 工作原理：
 * 鼠标在窗口边缘的时候，截获鼠标消息，使窗口伸缩。
 * 支持所有QWidget及其子类，不支持QMainWindow。
 * 支持windows、macOS、Linux、e-linux等操作系统。
 *
 */
class QQtBodyResizerPrivate;
class QQTSHARED_EXPORT QQtBodyResizer : public QObject
{
    Q_OBJECT

public:
    QQtBodyResizer ( QObject* parent = 0 );
    virtual ~QQtBodyResizer();

    // QObject interface
public:
    virtual bool eventFilter ( QObject* watched, QEvent* event ) override;

private:
    QQtBodyResizerPrivate* d_ptr;
    Q_DECLARE_PRIVATE ( QQtBodyResizer )
};

#endif // QQTBODYRESIZER_H
