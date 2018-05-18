#include "qqtclickhelper.h"

QQtClickHelper::QQtClickHelper ( QObject* parent )
{
    mLongClickInterval = longClickInterval;

    t1_press = QTime::currentTime();
    t2_release = t1_press;

    nClickNum = 0;
    nLongClickNum = 0;
    nTotalClickNum = 0;

    mClickType = QQtNullClick;
}

QQtClickHelper::~QQtClickHelper()
{

}

void QQtClickHelper::mousePressEvent ( QMouseEvent* event, QWidget* userWidget )
{
    p2debug() << "press" << event->pos() << userWidget;
    mPoint = event->pos();
    mClickType = QQtClick;
    t1_press = QTime::currentTime();
}

void QQtClickHelper::mouseReleaseEvent ( QMouseEvent* event, QWidget* userWidget )
{
    p2debug() << "release" << event->pos() << userWidget;
    //这一次 current click
    QTime t2_release_preview = t2_release;
    t2_release = QTime::currentTime();
    //这里加了个判断,其实肯定>=0
    if ( t1_press.msecsTo ( t2_release ) >= 0 && t1_press.msecsTo ( t2_release ) <= mLongClickInterval )
    {
        //单击发生
        mClickType = QQtClick;
    }
    else if ( t1_press.msecsTo ( t2_release ) >= 0 && t1_press.msecsTo ( t2_release ) > mLongClickInterval )
    {
        //长击发生
        mClickType = QQtLongClick;

        //这次点击,
        //上次的release竟然比press晚,说明press没发生,置位click
        //第一次click, 上一次release=press也在这里被置位click
        if ( t2_release_preview.msecsTo ( t2_release ) >= 0
             && t2_release_preview.msecsTo ( t1_press ) <= 0 )
        {
            mClickType = QQtClick;
        }

    }

    if ( mClickType == QQtLongClick )
    {
        //计算点击数目
        checkClickNum();

        //修改状态
        mClickType = QQtNullClick;

        //如果手移开了,那么不发送.
        //条件是用户传入了这个Widget为真.
        if ( userWidget )
        {
            p2debug() << userWidget <<  userWidget->rect() << event->pos() << userWidget->rect().contains ( event->pos() );
            if ( !userWidget->rect().contains ( event->pos() ) )
            {
                p2debug() << "send long click canceled." ;
                return;
            }
        }

        //发送长信号
        p2debug() << "send long click " ;
        emit longClick();
        emit longClickWithPoint ( event->pos() );

        emit longClickWithPointF ( event->localPos() );
        return;
    }
    else if ( mClickType == QQtClick )
    {
        //计算点击数目
        checkClickNum();

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

        //发送单击信号
        p2debug() << "send click." ;
        emit click();
        emit clickWithPoint ( event->pos() );

        emit clickWithPointF ( event->localPos() );
        return;
    }

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

void QQtClickHelper::setLongClickInterval ( int millSecond )
{
    mLongClickInterval = millSecond;
}

int QQtClickHelper::getLongClickInterval() const
{
    return mLongClickInterval;
}

quint32 QQtClickHelper::clickNum() const { return nClickNum; }

quint32 QQtClickHelper::longClickNum() const { return nLongClickNum; }

quint64 QQtClickHelper::totalClickNum() const { return nTotalClickNum; }

void QQtClickHelper::checkClickNum()
{
    switch ( mClickType )
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
        case QQtLongClick:
        {
            nLongClickNum++;
            if ( nLongClickNum >= 0xFFFFFFFF )
            {
                p2debug() << "out......";
                nLongClickNum = 0;
            }
        }
        break;
        default:
            break;
    }

    nTotalClickNum = nClickNum + nLongClickNum;
    if ( nTotalClickNum >= 0xFFFFFFFFFFFFFFFF )
    {
        p2debug() << "out......";
        nTotalClickNum = 0;
    }
}
