#include "qqtwidgetclickhelper.h"
#include "qqtcore.h"

QQtWidgetClickHelper::QQtWidgetClickHelper ( QObject* parent ) :
    QObject ( parent )
{
    mDoubleClickInterval = 300;
    mLongClickInterval = 1200;

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

QQtWidgetClickHelper::~QQtWidgetClickHelper()
{
}

#if 1
#define pdebug() ptime()
#else
#define pdebug()
#endif

void QQtWidgetClickHelper::mousePressEvent ( QMouseEvent* event , QWidget* userWidget )
{
    pdebug();
    //保存位置 这个记录什么用?
    mPoint = event->pos();

    //初始化一些状态
    //mClickType = QQtNullClick;
    m_long_click_timer->start();
    m_click_timer->stop();
}

void QQtWidgetClickHelper::mouseReleaseEvent ( QMouseEvent* event, QWidget* userWidget )
{
    pdebug();

    //梳理状态
    m_long_click_timer->stop();
    m_click_timer->stop();

    if ( mClickType == QQtLongClick )
    {
        //修改状态
        mClickType = QQtNullClick;

        //如果手移开了,那么不发送.
        //条件是用户传入了这个Widget为真.
        if ( userWidget )
        {
            if ( !userWidget->rect().contains ( event->pos() ) )
            {
                pdebug() << "send long click canceled." ;
                return;
            }
        }

        //发送长信号
        pdebug() << "send long click " ;
        emit longClick();
        emit longClickWithPoint ( event->pos() );
        return;
    }
    else if ( mClickType == QQtDoubleClick )
    {
        //修改状态
        mClickType = QQtNullClick;

        //如果手移开了,那么不发送.
        //条件是用户传入了这个Widget为真.
        if ( userWidget )
        {
            if ( !userWidget->rect().contains ( event->pos() ) )
            {
                pdebug() << "send double click canceled." ;
                return;
            }
        }

        //发送长信号
        pdebug() << "send double click." ;
        emit doubleClick();
        emit doubleClickWithPoint ( event->pos() );
        return;
    }

    //启动click检测timer.
    m_click_timer->start();
    startClickTime = QTime::currentTime();

    //修改状态
    mClickType = QQtNullClick;

    //保存位置
    mPoint = event->pos();
    return;
}

void QQtWidgetClickHelper::mouseDoubleClickEvent ( QMouseEvent* event , QWidget* userWidget )
{
    ptime();
    //修改状态
    mClickType = QQtDoubleClick;

    //保存位置 这个保存没有意义?
    mPoint = event->pos();
}

void QQtWidgetClickHelper::slotClickTimeout()
{
    QTime nowTime = QTime::currentTime();
    int t0 = startClickTime.msecsTo ( nowTime );
    pdebug() << t0 << qApp->doubleClickInterval();
    if ( t0 > 300/*qApp->doubleClickInterval()*/ )
    {
        mClickType = QQtClick;
        pdebug() << "send click." ;
        emit click();
        emit clickWithPoint ( mPoint );
        m_click_timer->stop();
        mClickType = QQtNullClick;
        return;
    }
}

void QQtWidgetClickHelper::slotLongClickTimeout()
{
    //longclick超时,确认longclick.
    mClickType = QQtLongClick;
    m_long_click_timer->stop();
}

void QQtWidgetClickHelper::slotDoubleClickTimeout()
{

}

