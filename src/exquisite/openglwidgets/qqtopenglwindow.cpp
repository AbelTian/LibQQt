#include "qqtopenglwindow.h"


QQtOpenGLWindow::QQtOpenGLWindow ( QWidget* parent ) : QOpenGLWindow ( )
{
    initializeOpenGLFunctions();
}

QQtOpenGLWindow::~QQtOpenGLWindow()
{

}

void QQtOpenGLWindow::initializeGL()
{
}

void QQtOpenGLWindow::resizeGL ( int w, int h )
{
}

void QQtOpenGLWindow::paintGL()
{
}

void QQtOpenGLWindow::paintUnderGL()
{
}

void QQtOpenGLWindow::paintOverGL()
{
}

void QQtOpenGLWindow::initializeOverlayGL() {}

void QQtOpenGLWindow::resizeOverlayGL ( int w, int h ) {}

void QQtOpenGLWindow::paintOverlayGL() {}
