#include "qqtradiobutton.h"
#include <QStylePainter>

QQtRadioButton::QQtRadioButton ( QWidget* parent ) :
    QRadioButton ( parent )
{
    mWorkState = BTN_NORMAL;
    //connect ( this, SIGNAL ( toggled ( bool ) ), this, SLOT ( setChecked ( bool ) ) );
}

QQtRadioButton::~QQtRadioButton()
{
}

/**
 * 把图片设置到内部变量
 */

QImage QQtRadioButton::stateImage ( int index )
{
    if ( index < BTN_NORMAL || index > BTN_MAX - 1 )
        return mImageTable[BTN_NORMAL];
    return mImageTable[index];
}

void QQtRadioButton::setStateImage ( int index, const QImage& image )
{
    if ( index < BTN_NORMAL || index > BTN_MAX - 1 )
        return;
    mImageTable[index] = image;
    //translateImage();
    update();
}

void QQtRadioButton::setNormalImage ( const QImage& normal, const QImage& press )
{
    mImageTable[BTN_NORMAL] = normal;
    mImageTable[BTN_PRESS] = press;
    //translateImage();
    update();
}

void QQtRadioButton::setHoverImage ( const QImage& hover )
{
    mImageTable[BTN_HOVER] = hover;
    //translateImage();
    update();
}

void QQtRadioButton::setDisableImage ( const QImage& disable )
{
    mImageTable[BTN_DISABLE] = disable;
    //translateImage();
    update();
}

void QQtRadioButton::setEnabled ( bool stat )
{
    //qDebug() << stat;
    QRadioButton::setEnabled ( stat );
    if ( stat )
        setWorkState ( BTN_NORMAL );
    else
        setWorkState ( BTN_DISABLE );
    update();
}

void QQtRadioButton::setDisabled ( bool stat )
{
    QRadioButton::setDisabled ( stat );
    if ( !stat )
        setWorkState ( BTN_NORMAL );
    else
        setWorkState ( BTN_DISABLE );
    update();
}

bool QQtRadioButton::isHover()
{
    QRect r0 = rect();
    QRect gr0 = QRect ( mapToGlobal ( r0.topLeft() ), mapToGlobal ( r0.bottomRight() ) );
    if ( gr0.contains ( QCursor::pos() ) )
        return true;
    return false;
}

const TBtnImageTable& QQtRadioButton::imageTable() const
{
    return mImageTable;
}

TBtnImageTable& QQtRadioButton::imageTable()
{
    return mImageTable;
}

void QQtRadioButton::setChecked ( bool ischecked )
{
    QRadioButton::setChecked ( ischecked );
    translateImage();
}

int QQtRadioButton::workState() const
{
    return mWorkState;
}

void QQtRadioButton::setWorkState ( int index )
{
    mWorkState = ( EBtnStatus ) index;
    //translateImage();
    //update();
}

/**
 * 事件驱动图片显示
 */


void QQtRadioButton::mousePressEvent ( QMouseEvent* event )
{
    if ( event->button() == Qt::LeftButton )
    {
        mWorkState = BTN_PRESS;
    }
    QRadioButton::mousePressEvent ( event );
    //translateImage();
    update();
}

void QQtRadioButton::mouseReleaseEvent ( QMouseEvent* event )
{
    if ( event->button() == Qt::LeftButton )
    {
#ifdef __EMBEDDED_LINUX__
        mWorkState = BTN_NORMAL;
#else
        if ( rect().contains ( event->pos() ) )
            mWorkState = BTN_HOVER;
        else
            mWorkState = BTN_NORMAL;
#endif
    }
    QRadioButton::mouseReleaseEvent ( event );
    //translateImage();
    update();
}

void QQtRadioButton::enterEvent ( QEvent* event )
{
    mWorkState = BTN_HOVER;
    QRadioButton::enterEvent ( event );
    //translateImage();
    update();
}

void QQtRadioButton::leaveEvent ( QEvent* event )
{
    mWorkState = BTN_NORMAL;
    QRadioButton::leaveEvent ( event );
    //translateImage();
    update();
}

void QQtRadioButton::translateImage()
{
    int state = mWorkState;

    if ( isCheckable() )
        if ( isChecked() )
            state = BTN_CHECK;
        else
            state = BTN_UNCHECK;

    //qDebug() << isEnabled();

    if ( !isEnabled() )
        state = BTN_DISABLE;

    setImage ( mImageTable[state] );
}

void QQtRadioButton::setImage ( const QImage& image )
{
    mImage = image;
    //update();
}

void QQtRadioButton::paintEvent ( QPaintEvent* event )
{
    //把imageTable()[stat]设置到mImage。
    translateImage();

    if ( mImage.isNull() )
        return QRadioButton::paintEvent ( event );

    //qDebug() << isEnabled() << mWorkState;

    QStylePainter p ( this );
#if 0
    p.drawItemPixmap ( rect(), Qt::AlignCenter, QIcon ( QPixmap::fromImage ( mImage ) ).pixmap ( rect().size(),
                       QIcon::Normal, QIcon::On ) );
#else
    p.drawItemPixmap ( rect(), Qt::AlignLeft | Qt::AlignTop,
                       /*不.copy() 切出图片的中间部分使用*/
                       QPixmap::fromImage ( mImage
                                            .scaled ( rect().width(), rect().height(), Qt::IgnoreAspectRatio )
                                          ) );
#endif

    QStyleOptionButton opt;
    initStyleOption ( &opt );
    p.drawItemText ( rect(), Qt::AlignCenter, opt.palette, isEnabled(), text() );
}


bool QQtRadioButton::hitButton ( const QPoint& pos ) const
{
    Q_UNUSED ( pos )
    return true;
}
