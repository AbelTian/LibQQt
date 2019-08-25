#include <mainwidget.h>

#include <qqtbodymover.h>

MainWidget::MainWidget ( QWidget* parent ) : QWidget ( parent )
{
    //用户设置 - UI中
    //setMouseTracking ( true );
    QQtBodyMover* helper = new QQtBodyMover ( this );
    this->installEventFilter ( helper );
}

MainWidget::~MainWidget() {}
