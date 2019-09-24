#include <mainwidget.h>
#if 0
#include <qqtframemouselocker.h>

MainWidget::MainWidget ( QWidget* parent ) : QWidget ( parent )
{
    //用户设置 - UI中
    //setMouseTracking ( true );
    QQtFrameMouseLocker* helper = new QQtFrameMouseLocker ( this );
    this->installEventFilter ( helper );
}

MainWidget::~MainWidget() {}
#endif

#include <qqtmouselocker.h>

MainWidget::MainWidget ( QWidget* parent ) : QWidget ( parent )
{
    //用户设置 - UI中
    //setMouseTracking ( true );
    //QQtMouseLocker* helper = new QQtMouseLocker ( this );
    //this->installEventFilter ( helper );
    //helper->lockWindow ( this );
}

MainWidget::~MainWidget() {}
