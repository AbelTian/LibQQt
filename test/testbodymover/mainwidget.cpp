#include <mainwidget.h>

#include <qqtbodymover.h>

MainWidget::MainWidget ( QWidget* parent ) : QWidget ( parent )
{
    //用户设置 - UI中
    //setMouseTracking ( true );
    //这里可以不设置，外边还有个mainwindow的边框，
    //设置了以后，会有一块边缘空白不响应。
    setContentsMargins ( 10, 10, 10, 10 );
    QQtBodyMover* helper = new QQtBodyMover ( this );
    this->installEventFilter ( helper );
}

MainWidget::~MainWidget() {}
