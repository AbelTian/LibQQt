#ifndef QQTOPENGLWIDGET_H
#define QQTOPENGLWIDGET_H

/**
 * QOpenGL与QGL不同，
 * QOpenGLWidget属于Widgets库，QOpenGLFunctions属于GUI库;
 * QGLWidget属于opengl库，QGLFunctions属于opengl库。
 * 在多个平台上，ARMHF32、Android，Qt对opengl库支持的并不好，所以关闭。
 */
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include "qqtcore.h"
#include "qqt-local.h"

#if 0
#include <GL/gl.h>
#include <GL/glu.h>
#endif

/**
 * @brief The QQtOpenGLWidget class
 * 为了简便，用这一个，QOpenGLWidget
 *
 * Windows平台 支持
 * Android平台
 */
class QQTSHARED_EXPORT QQtOpenGLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit QQtOpenGLWidget ( QWidget* parent = nullptr );
    ~QQtOpenGLWidget();

    //获取GL操作函数
    QOpenGLFunctions* glFuncs() const { return pmGLFunctions; }

signals:

public slots:

protected:

    // 用户继承下去，实现显示。
    // QOpenGLWidget interface
protected:
    //背景
    virtual void initializeGL() override;
    virtual void resizeGL ( int w, int h ) override;
    virtual void paintGL() override;
    //漂浮物
    virtual void initializeOverlayGL();
    virtual void resizeOverlayGL ( int w, int h );
    virtual void paintOverlayGL();

protected:
private:
    QOpenGLFunctions* pmGLFunctions;
};

#endif // QQTOPENGLWIDGET_H
