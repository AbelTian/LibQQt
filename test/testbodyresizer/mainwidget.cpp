#include <mainwidget.h>

#include <qqtbodyresizer.h>
#include <qqtbodymover.h>

MainWidget::MainWidget ( QWidget* parent ) : QWidget ( parent )
{
    //用户设置 - UI中
    setMouseTracking ( true );//必要

    setWindowFlags ( windowFlags() | ( Qt::FramelessWindowHint ) );

    //顺便测试一下bodyMover
    QQtBodyMover* helper2 = new QQtBodyMover ( this );
    this->installEventFilter ( helper2 );

    QQtBodyResizer* helper = new QQtBodyResizer ( this );
    this->installEventFilter ( helper );

}

MainWidget::~MainWidget() {}
