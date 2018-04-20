#ifndef QQTOPENGLWIDGET_H
#define QQTOPENGLWIDGET_H


#include <QGLWidget>
#include <QOpenGLWidget>
#include <GL/gl.h>
#include <GL/glu.h>

/**
 * 现在遇到的问题：
 * QOpenGLWidget need? QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
 * 程序直接去调用了OpenGL ES库，而在OpenGL ES库中是不支持glBegin()等函数的，所以我们需要让程序去连接到OpenGL库
 */

/**
 * @brief The QQtOpenGLWidget class
 * 为了简便，用这一个，QGLWidget
 */
class QQtOpenGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit QQtOpenGLWidget ( QWidget* parent = nullptr );
    ~QQtOpenGLWidget() {

    }

signals:

public slots:

protected:
    //按钮信号 左键 右键 长按 带点

    // QGLWidget interface
protected:
    //用户继承下去，实现显示。
    //背景
    virtual void initializeGL() override;
    virtual void resizeGL ( int w, int h ) override;
    virtual void paintGL() override;
    //漂浮物
    virtual void initializeOverlayGL() override;
    virtual void resizeOverlayGL ( int w, int h ) override;
    virtual void paintOverlayGL() override;
};

#endif // QQTOPENGLWIDGET_H
