#include "qqtvirtualclickhelper.h"

QQtVirtualClickHelper::QQtVirtualClickHelper ( QObject* parent ) : QObject ( parent )
{
    nTotalClickNumWithCancel = 0;
    nTotalClickNum = 0;
    mClickType = QQtNullClick;
}

QQtVirtualClickHelper::~QQtVirtualClickHelper()
{

}

void QQtVirtualClickHelper::mousePressEvent ( QMouseEvent* event, QWidget* userWidget )
{
    p2debug() << "press" << event->pos() << userWidget;
}

void QQtVirtualClickHelper::mouseReleaseEvent ( QMouseEvent* event, QWidget* userWidget )
{
    p2debug() << "release" << event->pos() << userWidget;
}

void QQtVirtualClickHelper::mouseDoubleClickEvent ( QMouseEvent* event, QWidget* userWidget )
{
    p2debug() << "double click" << event->pos() << userWidget;
}

void QQtVirtualClickHelper::checkClickNumWithCancel()
{
    switch ( mClickType )
    {
        default:
            break;
    }

    nTotalClickNumWithCancel = 0;
    if ( nTotalClickNumWithCancel >= 0xFFFFFFFFFFFFFFFF )
    {
        p2debug() << "out......";
        nTotalClickNumWithCancel = 0;
    }
}

void QQtVirtualClickHelper::checkClickNum ( QQtVirtualClickHelper::QQtClickType type )
{
    switch ( type )
    {
        default:
            break;
    }

    nTotalClickNum = 0;
    if ( nTotalClickNum >= 0xFFFFFFFFFFFFFFFF )
    {
        p2debug() << "out......";
        nTotalClickNum = 0;
    }
}
