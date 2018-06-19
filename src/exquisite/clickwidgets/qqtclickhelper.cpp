#include "qqtclickhelper.h"

QQtClickHelper::QQtClickHelper ( QObject* parent ) : QQtVirtualClickHelper ( parent )
{
    nClickNumWithCancel = 0;
    nClickNum = 0;
}

QQtClickHelper::~QQtClickHelper()
{

}

void QQtClickHelper::mousePressEvent ( QMouseEvent* event, QWidget* userWidget )
{
    p2debug() << "press" << event->pos() << userWidget;
    mPoint = event->pos();
    mClickType = QQtClick;
}

void QQtClickHelper::mouseReleaseEvent ( QMouseEvent* event, QWidget* userWidget )
{
    p2debug() << "release" << event->pos() << userWidget;

    mClickType = QQtClick;
    //计算点击数目
    checkClickNumWithCancel();

    //修改状态
    mClickType = QQtNullClick;

    //如果手移开了,那么不发送.
    //条件是用户传入了这个Widget为真.
    if ( userWidget )
    {
        p2debug() << userWidget <<  userWidget->rect() << event->pos() << userWidget->rect().contains ( event->pos() );
        if ( !userWidget->rect().contains ( event->pos() ) )
        {
            p2debug() << "send click canceled." ;
            return;
        }
    }

    checkClickNum ( QQtClick );

    //发送单击信号
    p2debug() << "send click." ;
    emit click();
    emit clickWithPoint ( event->pos() );
    emit clickWithPointF ( event->localPos() );

#if 0
    emit click ( userWidget );
    emit clickWithPoint ( event->pos(), userWidget );
    emit clickWithPointF ( event->localPos(), userWidget );
#endif

    //修改状态
    mClickType = QQtNullClick;

    //保存位置
    mPoint = event->pos();
    return;

}

void QQtClickHelper::mouseDoubleClickEvent ( QMouseEvent* event, QWidget* userWidget )
{
    p2debug() << "double click" << event->pos() << userWidget;
    mPoint = event->pos();
}

void QQtClickHelper::checkClickNumWithCancel()
{
    QQtVirtualClickHelper::checkClickNumWithCancel();
    switch ( mClickType )
    {
        case QQtClick:
        {
            nClickNumWithCancel++;
            if ( nClickNumWithCancel >= 0xFFFFFFFF )
            {
                p2debug() << "out......";
                nClickNumWithCancel = 0;
            }
        }
        break;
        default:
            break;
    }

    nTotalClickNumWithCancel = nClickNumWithCancel;
    if ( nTotalClickNumWithCancel >= 0xFFFFFFFFFFFFFFFF )
    {
        p2debug() << "out......";
        nTotalClickNumWithCancel = 0;
    }
}

void QQtClickHelper::checkClickNum ( QQtClickHelper::QQtClickType type )
{
    QQtVirtualClickHelper::checkClickNum ( type );
    switch ( type )
    {
        case QQtClick:
        {
            nClickNum++;
            if ( nClickNum >= 0xFFFFFFFF )
            {
                p2debug() << "out......";
                nClickNum = 0;
            }
        }
        break;
        default:
            break;
    }

    nTotalClickNum = nClickNum;
    if ( nTotalClickNum >= 0xFFFFFFFFFFFFFFFF )
    {
        p2debug() << "out......";
        nTotalClickNum = 0;
    }
}
