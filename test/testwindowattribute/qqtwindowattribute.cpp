#include <qqtwindowattribute.h>

#include <QWidget>
#include <qqtcore.h>
#include <qqtwidgets.h>

void setFrameless ( QWidget* widget, bool open )
{
    Q_ASSERT ( widget );
    pline() << widget->windowFlags();
    if ( open )
        widget->setWindowFlags ( Qt::FramelessWindowHint | widget->windowFlags() );
    else
        widget->setWindowFlag ( Qt::FramelessWindowHint, false );
    pline() << widget->windowFlags();
}

void setMainWindow ( QWidget* widget, bool open )
{
    Q_ASSERT ( widget );
    pline() << widget->windowFlags();
    if ( open )
    {
        widget->setWindowFlags ( Qt::Window | widget->windowFlags() );
        widget->setWindowFlag ( Qt::SubWindow, false );
    }
    else
    {
        //独立的子窗口是不存在的。
        widget->setWindowFlag ( Qt::Widget, true );
        //怎么了，不能单独使用。
        //widget->setWindowFlags ( Qt::SubWindow | widget->windowFlags() );
    }
    pline() << widget->windowFlags();
}

void setFullScreen ( QWidget* widget, bool open, QRect normalGeometry )
{
    Q_ASSERT ( widget );
    pline() << widget->windowFlags();
    if ( open )
    {
        //确保不是子窗口
        widget->setWindowFlags ( Qt::Window | widget->windowFlags() );
        widget->setWindowFlags ( Qt::FramelessWindowHint | widget->windowFlags() );
        widget->showFullScreen();
    }
    else
    {
        //确保不是子窗口
        widget->setWindowFlags ( Qt::Window | widget->windowFlags() );
        //取消frameless
        widget->setWindowFlag ( Qt::FramelessWindowHint, false );
        widget->showNormal();
        widget->setGeometry ( normalGeometry );
        moveCenter ( widget );
    }
    pline() << widget->windowFlags();
}
