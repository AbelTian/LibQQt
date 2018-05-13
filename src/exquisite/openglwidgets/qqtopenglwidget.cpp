#include "qqtopenglwidget.h"

QQtOpenGLWidget::QQtOpenGLWidget ( QWidget* parent ) : QGLWidget ( parent )
{
    pmGLFunctions = new QGLFunctions ( this->context() );
    pline() << "Qt OpenGL Function GL feature:" << hex << pmGLFunctions->openGLFeatures();
}

QQtOpenGLWidget::~QQtOpenGLWidget()
{
    delete pmGLFunctions;
}


void QQtOpenGLWidget::initializeGL()
{
    glFuncs()->glBlendColor ( 0, 0, 0, 0 );
#if 0
    //设置清除时颜色
    glClearColor ( 0.0, 0.0, 0.0, 0 );
#endif
}

void QQtOpenGLWidget::resizeGL ( int w, int h )
{
#if 0
    //视口变换
    glViewport ( 0, 0, ( GLsizei ) w, ( GLsizei ) h );
    //投影变换
    glMatrixMode ( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective ( 40.0, ( GLdouble ) w / ( GLdouble ) h, 0.1, 10000.0 );
    视图变换
    glMatrixMode ( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt ( 0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );
#endif
}

void QQtOpenGLWidget::paintGL()
{
#if 0
    //清屏
    glClear ( GL_COLOR_BUFFER_BIT );
    //绘制矩形
    glColor3f ( 1.0, 1.0, 1.0 );
    glRectd ( 2.0, 2.0, 0.0, 0.0 );
#endif
    glFuncs()->glClearDepthf ( 0 );

}

void QQtOpenGLWidget::initializeOverlayGL()
{
}

void QQtOpenGLWidget::resizeOverlayGL ( int w, int h )
{
}

void QQtOpenGLWidget::paintOverlayGL()
{
}


void QQtOpenGLWidget::mousePressEvent ( QMouseEvent* event )
{
}

void QQtOpenGLWidget::mouseReleaseEvent ( QMouseEvent* event )
{
}

void QQtOpenGLWidget::mouseDoubleClickEvent ( QMouseEvent* event )
{
}
