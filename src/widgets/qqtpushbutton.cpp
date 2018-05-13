#include "qqtpushbutton.h"
#include <QStylePainter>
#include <QMouseEvent>

QQtPushButton::QQtPushButton ( QWidget* parent ) :
    QPushButton ( parent )
{
    state = BTN_NORMAL;
    ring = false;
    m_lcTimer = new QTimer ( this );
    m_lcTimer->setSingleShot ( true );
    m_lcTimer->setInterval ( 2200 );
    connect ( m_lcTimer, SIGNAL ( timeout() ),
              this, SLOT ( slot_timeout() ) );
}

QQtPushButton::~QQtPushButton()
{
}

void QQtPushButton::paintEvent ( QPaintEvent* e )
{
    Q_UNUSED ( e )
    QStylePainter p ( this );

    bool enabled = isEnabled();

    //pline() << this->objectName() << e->type() << state << m_pixmap[state];

#if 0
    /*
     * 不会报告ｌｉｂｐｎｇｗａｒｎｉｎｇ
     */
    QIcon::Mode iconFlag = QIcon::Normal;

    if ( BTN_PRESS == state )
        iconFlag = QIcon::Selected;

    if ( !enabled )
        iconFlag = QIcon::Disabled;

    p.drawItemPixmap ( rect(), Qt::AlignCenter, QIcon ( m_pixmap[state] ).pixmap ( rect().size(), iconFlag, QIcon::On ) );
#else
    /*
     * 以下方法会导致图片失真 可以控制大小 可以控制图片状态 ｓｃａｌｅｄ函数打印ｌｉｂｐｎｇｗａｒｎｉｎｇ
     */
    QImage image ( m_pixmap[state] );
    p.drawItemPixmap ( rect(), Qt::AlignCenter, QPixmap::fromImage ( image.scaled ( rect().size(),
                                                                                    Qt::IgnoreAspectRatio ) ) );
#endif

    QStyleOptionButton opt;
    initStyleOption ( &opt );
    p.drawItemText ( rect(), Qt::AlignCenter, opt.palette, enabled, text() );
}

void QQtPushButton::mousePressEvent ( QMouseEvent* e )
{
    if ( e->button() == Qt::LeftButton )
    {
        state = BTN_PRESS;

        if ( ring )
            QApplication::beep();

        //pline() << state;
        m_lcTimer->start();
    }

    QPushButton::mousePressEvent ( e );
}

void QQtPushButton::mouseReleaseEvent ( QMouseEvent* e )
{
    if ( e->button() == Qt::LeftButton )
    {
#ifdef __EMBEDDED_LINUX__
        state = BTN_NORMAL;
        //pline() << state;
        update();
#else

        if ( rect().contains ( e->pos() ) )
            state = BTN_HOVER;
        else
            state = BTN_NORMAL;

#endif

        if ( m_lcTimer->isActive() )
        {
            m_lcTimer->stop();
            /*在这里说明，用户点了一下抬手了*/

            //emit click();
        }
    }

    /*QPushButton的点击信号可能是在这个函数当中发出的*/
    /*这个函数，用户在收到longClick之后，还会收到click的*/
    QPushButton::mouseReleaseEvent ( e );
}

void QQtPushButton::enterEvent ( QEvent* e )
{
    state = BTN_HOVER;
    QPushButton::enterEvent ( e );
}

void QQtPushButton::leaveEvent ( QEvent* e )
{
    state = BTN_NORMAL;
    QPushButton::leaveEvent ( e );
}

void QQtPushButton::changeEvent ( QEvent* e )
{
    QPushButton::changeEvent ( e );
}

void QQtPushButton::enabledChange ( bool enabled )
{
    state = isEnabled() ? BTN_NORMAL : BTN_DISABLE;
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    QPushButton::enabledChange ( enabled );
#else
    //TODO:
    Q_UNUSED ( enabled )
    //TODO:
#endif
}

void QQtPushButton::slot_timeout()
{
    /*在这里说明，用户点了长达2s*/
    emit longClick();
}
