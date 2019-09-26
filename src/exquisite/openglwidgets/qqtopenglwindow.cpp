#include "qqtopenglwindow.h"


QQtOpenGLWindow::QQtOpenGLWindow ( QWidget* parent ) : QOpenGLWidget ( parent )
{
}

QQtOpenGLWindow::~QQtOpenGLWindow()
{

}

void QQtOpenGLWindow::initializeGL()
{
    initializeOpenGLFunctions();
    pline() << "Qt OpenGL Function GL feature:" << hex << openGLFeatures();


    initializeUnderGL();
    initializeOverGL();
}

void QQtOpenGLWindow::resizeGL ( int w, int h )
{
    resizeUnderGL ( w, h );
    resizeOverGL ( w, h );
}

void QQtOpenGLWindow::paintGL()
{
    paintUnderGL();
    paintOverGL();
}

void QQtOpenGLWindow::initializeUnderGL()
{

}

void QQtOpenGLWindow::resizeUnderGL ( int w, int h )
{

}

void QQtOpenGLWindow::paintUnderGL()
{

}

void QQtOpenGLWindow::initializeOverGL()
{

}

void QQtOpenGLWindow::resizeOverGL ( int w, int h )
{

}

void QQtOpenGLWindow::paintOverGL()
{

}
