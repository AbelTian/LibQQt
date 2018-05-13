#ifndef QQTOPENGLWIDGET_H
#define QQTOPENGLWIDGET_H

#include <QGLWidget>
#include <QGLFunctions>

#include "qqtcore.h"
#include "qqt-local.h"

#if 0
#include <GL/gl.h>
#include <GL/glu.h>
#endif

/**
 * 现在遇到的问题：
 * QOpenGLWidget need? QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
 * 程序直接去调用了OpenGL ES库，而在OpenGL ES库中是不支持glBegin()等函数的，所以我们需要让程序去连接到OpenGL库
 */

/**
 * @brief The QQtOpenGLWidget class
 * 为了简便，用这一个，QGLWidget
 *
 * Windows平台 支持
 * Android平台
 */
class QQTSHARED_EXPORT QQtOpenGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit QQtOpenGLWidget ( QWidget* parent = nullptr );
    ~QQtOpenGLWidget();

    //获取GL操作函数
    QGLFunctions* glFuncs() const { return pmGLFunctions; }
    //用户自定义GLWidget Context。
    void useCustomContext ( QGLContext* context ) {
        setContext ( context );
        glFuncs()->initializeGLFunctions ( context );
    }

signals:

public slots:

protected:

    // 用户继承下去，实现显示。
    // QGLWidget interface
protected:
    //背景
    virtual void initializeGL() override;
    virtual void resizeGL ( int w, int h ) override;
    virtual void paintGL() override;
    //漂浮物
    virtual void initializeOverlayGL() override;
    virtual void resizeOverlayGL ( int w, int h ) override;
    virtual void paintOverlayGL() override;

protected:
private:
    QGLFunctions* pmGLFunctions;

    // 按钮信号 左键 右键 长按 带点
    // QWidget interface
protected:
    virtual void mousePressEvent ( QMouseEvent* event ) override;
    virtual void mouseReleaseEvent ( QMouseEvent* event ) override;
    virtual void mouseDoubleClickEvent ( QMouseEvent* event ) override;
};

#endif // QQTOPENGLWIDGET_H
