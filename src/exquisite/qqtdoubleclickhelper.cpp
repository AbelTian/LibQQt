#include "qqtdoubleclickhelper.h"

QQtDoubleClickHelper::QQtDoubleClickHelper ( QObject* parent ) :
    QQtClickHelper ( parent )
{
    mDoubleClickInterval = doubleClickInterval;

    nDoubleClickNum = 0;

    t1_doubleclick = QTime::currentTime();
    t2_doubleclick = t2_doubleclick;

    t2_release_initial = QTime::currentTime();
    t2_release_preview = t2_release_initial;

    mMouseEvent = new QQtMouseEvent;

    mClickType = QQtNullClick;

    m_click_timer = new QTimer ( this );
    m_click_timer->setSingleShot ( false );
    //击发延迟20ms
    m_click_timer->setInterval ( 20 );
    connect ( m_click_timer, SIGNAL ( timeout() ), this, SLOT ( slotClickTimeout() ) );

    m_long_click_timer = new QTimer ( this );
    m_long_click_timer->setSingleShot ( false );
    m_long_click_timer->setInterval ( mLongClickInterval );
    connect ( m_long_click_timer, SIGNAL ( timeout() ), this, SLOT ( slotLongClickTimeout() ) );

    m_double_click_timer = new QTimer ( this );
    m_double_click_timer->setSingleShot ( false );
    //人比较累了,用的时延就会比较长.
    m_double_click_timer->setInterval ( 100 );
    connect ( m_double_click_timer, SIGNAL ( timeout() ), this, SLOT ( slotDoubleClickTimeout() ) );

}

QQtDoubleClickHelper::~QQtDoubleClickHelper()
{
}


void QQtDoubleClickHelper::mousePressEvent ( QMouseEvent* event , QWidget* userWidget )
{
    p2debug() << "press" << event->pos() << userWidget;
    //保存位置 这个记录什么用?
    mPoint = event->pos();

    //初始化一些状态
    //mClickType = QQtNullClick;
    m_long_click_timer->start();
    m_click_timer->stop();

    //复用一下t1_press t2_release 这里的实现和父类关系不太大
    t1_press = QTime::currentTime();
}

void QQtDoubleClickHelper::mouseReleaseEvent ( QMouseEvent* event, QWidget* userWidget )
{
    p2debug() << "release" << event->pos() << userWidget;

    //添加longClick检测, 更新longclick检测时间
    t2_release_preview = t2_release;//记录上次的release
    t2_release = QTime::currentTime();
    //在release-press>longclick暨click时钟判定为longclick后 加一次判断修复误判 防止用户不发press,引起click一直longclick.
//    if ( t1_press.msecsTo ( t2_release ) >= mLongClickInterval
//         && t2_doubleclick.msecsTo ( t2_release ) >= 0
//         && t2_doubleclick.msecsTo ( t2_release ) < mLongClickInterval )
//    {
//        //单击发生
//        mClickType = QQtClick;
//    }

    //doubleClick检测不依赖press,所以只要发release就会有doubleClick发生.
    //检测方式: 两次release的间隔小于doubleClickInterval那么触发doubleClick.
    //这一次 current click
    t1_doubleclick = QTime::currentTime();
    //这里有小技巧: 这里没有加 && mClickType != QQtClick
    //难道不会和click时钟混淆吗?不会,因为click时钟那边用的startTime和nowTime两个变量, t2比startTime还早,t1比nowTime还晚,t1-t2绝对比nowTime-startTime还长.
    //如果是click,绝对不会混淆成doubleClick.
    //正好mDoubleClickInterval ms代表双击 不代表单击.
    if ( t2_doubleclick.msecsTo ( t1_doubleclick ) >= 0
         && t2_doubleclick.msecsTo ( t1_doubleclick ) < mDoubleClickInterval )
    {
        //双击发生
        mClickType = QQtDoubleClick;
    }
    //上一次 prev click
    t2_doubleclick = QTime::currentTime();

    //梳理状态
    m_long_click_timer->stop();
    m_click_timer->stop();

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
    else if ( mClickType == QQtDoubleClick )
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
                p2debug() << "send double click canceled." ;
                return;
            }
        }

        //发送双击信号
        p2debug() << "send double click." ;
        emit doubleClick();
        emit doubleClickWithPoint ( event->pos() );

        emit doubleClickWithPointF ( event->localPos() );
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

    //枷锁? 不,每一次双击肯定会冲掉单击检测.双击来了,单击检测取消.双击来了,不必要单击了,那不是单击.
    //双击来了,单击检测会被自动取消,发射双击信号以后,这一次单击\双击检测完成.

    //同样的,单击来了,单击发生,单击\双击监测完成.开始新的检测.

    //保存数据.
    mUserWidget = userWidget;
    *mMouseEvent = *event;
    startClickTime = QTime::currentTime();
    //启动click检测timer.
    m_click_timer->start();

    //修改状态
    mClickType = QQtNullClick;

    //保存位置
    mPoint = event->pos();
    return;
}

void QQtDoubleClickHelper::mouseDoubleClickEvent ( QMouseEvent* event , QWidget* userWidget )
{
    p2debug() << event->pos() << userWidget;
    //这里关闭状态修改,会和内部的检测冲突,分不清是单击还是双击.
    //修改状态
    //mClickType = QQtDoubleClick;

    //保存位置 这个保存没有意义?
    mPoint = event->pos();
}

void QQtDoubleClickHelper::slotClickTimeout()
{
    QTime nowTime = QTime::currentTime();
    int t0 = startClickTime.msecsTo ( nowTime );
    p2debug() << t0 << mDoubleClickInterval << qApp->doubleClickInterval();
    if ( t0 >= mDoubleClickInterval/*qApp->doubleClickInterval()*/ )
    {
        //先判断是否为长击
        //注意:必须和点击一样在超时的时候检测,否则和双击检测冲突,分不清是长击还是双击.导致长击必发.
        //注意:必须press击发.
        //不发press 发生误判 认为总是long click
        if ( t1_press.msecsTo ( t2_release ) >= 0
             && t1_press.msecsTo ( t2_release ) >= mLongClickInterval )
        {
            //长击发生
            mClickType = QQtLongClick;

            //有误判, 未发press的时候, 这个一直都是longclick,其实还有click
            //press比前一次release小的时候 其实是click
            if ( t2_release_preview.msecsTo ( t2_release ) >= 0
                 && t2_release_preview.msecsTo ( t1_press ) <= 0 )
            {
                mClickType = QQtClick;
            }

            //initial press
            if ( t2_release_preview.msecsTo ( t2_release ) >= 0
                 && t2_release_preview == t2_release_initial )
            {
                mClickType = QQtClick;
            }

            //经过以上两部fix,不发press过来,longclick绝不会发生.
            mouseReleaseEvent ( mMouseEvent, mUserWidget );
            return;
        }

        mClickType = QQtClick;
        mouseReleaseEvent ( mMouseEvent, mUserWidget );
        return;
    }
}

void QQtDoubleClickHelper::slotLongClickTimeout()
{
    //longclick超时,确认longclick.
    //不再使用此处检测,而是改在click时钟检测.
    //mClickType = QQtLongClick;
    m_long_click_timer->stop();
}

void QQtDoubleClickHelper::slotDoubleClickTimeout()
{

}

void QQtDoubleClickHelper::checkClickNum()
{
    QQtClickHelper::checkClickNum();
    switch ( mClickType )
    {
        case QQtDoubleClick:
        {
            nDoubleClickNum++;
            if ( nDoubleClickNum >= 0xFFFFFFFF )
            {
                p2debug() << "out......";
                nDoubleClickNum = 0;
            }
        }
        break;
        default:
            break;
    }

    nTotalClickNum = nClickNum + nLongClickNum + nDoubleClickNum;
    if ( nTotalClickNum >= 0xFFFFFFFFFFFFFFFF )
    {
        p2debug() << "out......";
        nTotalClickNum = 0;
    }
}
