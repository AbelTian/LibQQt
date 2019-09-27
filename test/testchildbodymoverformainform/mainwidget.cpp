#include <mainwidget.h>

#include <qqtcore.h>

#include <qqtbodyresizer.h>
#include <qqtchildbodymover.h>
#include <qqtdoubleclickhelper.h>

QQtDoubleClickHelper* helper3;

MainWidget::MainWidget ( QWidget* parent ) : QWidget ( parent )
{
    //用户设置 - UI中
    setMouseTracking ( true );//必要

    setContentsMargins ( 10, 10, 10, 10 );

    setWindowFlags ( windowFlags() | ( Qt::FramelessWindowHint ) );

    QQtBodyResizer* helper = new QQtBodyResizer ( this );
    this->installEventFilter ( helper );

    //顺便测试一下bodyMover
    QQtChildBodyMover* helper2 = new QQtChildBodyMover ( this );
    this->installEventFilter ( helper2 );

    //顺便测试一下mouseClicker
    helper3 = new QQtDoubleClickHelper ( this );
    this->installEventFilter ( helper3 );
    //this->removeEventFilter(helper3);
    connect ( helper3, SIGNAL ( clickWithPoint ( QPoint ) ), this, SLOT ( clickWithPoint ( QPoint ) ) );
    connect ( helper3, SIGNAL ( longClickWithPoint ( QPoint ) ), this, SLOT ( longClickWithPoint ( QPoint ) ) );
    connect ( helper3, SIGNAL ( doubleClickWithPoint ( QPoint ) ), this, SLOT ( doubleClickWithPoint ( QPoint ) ) );
}

MainWidget::~MainWidget() {}

void MainWidget::clickWithPoint ( QPoint point )
{
    pline() << "click" << point << helper3->clickNum() << helper3->clickNumWithCancel();
}

void MainWidget::longClickWithPoint ( QPoint point )
{
    pline() << "long click" << point << helper3->longClickNum() << helper3->longClickNumWithCancel();
}

void MainWidget::doubleClickWithPoint ( QPoint point )
{
    pline() << "double click" << point << helper3->doubleClickNum() << helper3->doubleClickNumWithCancel();
}
