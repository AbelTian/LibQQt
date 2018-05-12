#ifndef QQTOPENGLWINDOW_H
#define QQTOPENGLWINDOW_H

#include <QGLWidget>

#include "qqtcore.h"
#include "qqt-local.h"

/**
 * @brief The QQtOpenGLWindow class
 * Apple平台和Windows平台对OpenGL API使用加以了限制，一些会导致使用bug的限制。
 * Qt建议使用一个OpenGL Widget Parent窗口来解决这些限制可能引起的bug。
 * LibQQt要求，用户把所有的Qt OpenGL Widget都必须在这个OpenGL parent下成为子孙，包括背景GLWidget和漂浮GLWidget，这个类是Qt OpenGL Widget唯一的Root父亲。
 * main函数里，这个类或者唯一子类作为OpenGL窗口的唯一入口。
 * 建议用户继承下去，方便添加子GL窗口，也可以闲置，仅仅作为OpenGL Widget的parent存在。
 * 好比在MainWindow下添加centralWidget。
 */
class QQTSHARED_EXPORT QQtOpenGLWindow : public QGLWidget
{
    Q_OBJECT
public:
    explicit QQtOpenGLWindow ( QWidget* parent = nullptr ) : QGLWidget ( parent ) {

    }
    ~QQtOpenGLWindow() {

    }
signals:

public slots:
};

#endif // QQTOPENGLWINDOW_H
