#include "qqtpushbutton.h"
#include <QStylePainter>
#include <QMouseEvent>

QQtPushButton::QQtPushButton ( QWidget* parent ) :
    QPushButton ( parent )
{
    mWorkState = BTN_NORMAL;
}

QQtPushButton::~QQtPushButton()
{
}

const TBtnImageTable& QQtPushButton::imageTable() const
{
    return mImageTable;
}

TBtnImageTable& QQtPushButton::imageTable()
{
    return mImageTable;
}

void QQtPushButton::translateImage()
{
    int state = mWorkState;

    //qDebug() << isEnabled();

    if ( !isEnabled() )
        state = BTN_DISABLE;

    setImage ( mImageTable[state] );
}

void QQtPushButton::setImage ( const QImage& image )
{
    mImage = image;
    update();
}

int QQtPushButton::workState() const
{
    return mWorkState;
}

void QQtPushButton::setWorkState ( int index )
{
    mWorkState = ( EBtnStatus ) index;
    translateImage();
}


QImage QQtPushButton::stateImage ( int index )
{
    if ( index < BTN_NORMAL || index > BTN_MAX - 1 )
        return mImageTable[BTN_NORMAL];
    return mImageTable[index];
}

void QQtPushButton::setStateImage ( int index, const QImage& image )
{
    if ( index < BTN_NORMAL || index > BTN_MAX - 1 )
        return;
    mImageTable[index] = image;
    translateImage();
}

void QQtPushButton::setNormalImage ( const QImage& normal, const QImage& press )
{
    mImageTable[BTN_NORMAL] = normal;
    mImageTable[BTN_PRESS] = press;
    translateImage();
}

void QQtPushButton::setHoverImage ( const QImage& hover )
{
    mImageTable[BTN_HOVER] = hover;
    translateImage();
}

void QQtPushButton::setDisableImage ( const QImage& disable )
{
    mImageTable[BTN_DISABLE] = disable;
    translateImage();
}

void QQtPushButton::setEnabled ( bool stat )
{
    //qDebug() << stat;
    QPushButton::setEnabled ( stat );
    if ( stat )
        setWorkState ( BTN_NORMAL );
    else
        setWorkState ( BTN_DISABLE );
}

void QQtPushButton::setDisabled ( bool stat )
{
    QPushButton::setDisabled ( stat );
    if ( !stat )
        setWorkState ( BTN_NORMAL );
    else
        setWorkState ( BTN_DISABLE );
}

void QQtPushButton::mousePressEvent ( QMouseEvent* event )
{
    if ( event->button() == Qt::LeftButton )
    {
        mWorkState = BTN_PRESS;
    }
    QPushButton::mousePressEvent ( event );
    translateImage();
}

void QQtPushButton::mouseReleaseEvent ( QMouseEvent* event )
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
    QPushButton::mouseReleaseEvent ( event );
    translateImage();
}

void QQtPushButton::enterEvent ( QEvent* event )
{
    mWorkState = BTN_HOVER;
    QPushButton::enterEvent ( event );
    translateImage();
}

void QQtPushButton::leaveEvent ( QEvent* event )
{
    mWorkState = BTN_NORMAL;
    QPushButton::leaveEvent ( event );
    translateImage();
}


void QQtPushButton::paintEvent ( QPaintEvent* event )
{
    if ( mImage.isNull() )
        return QPushButton::paintEvent ( event );

    //qDebug() << isEnabled() << mWorkState;

    QStylePainter p ( this );
    p.drawItemPixmap ( rect(), Qt::AlignLeft | Qt::AlignTop,
                       /*不.copy() 切出图片的中间部分使用*/
                       QPixmap::fromImage ( mImage
                                            .scaled ( rect().width(), rect().height(), Qt::IgnoreAspectRatio )
                                          ) );

    QStyleOptionButton opt;
    initStyleOption ( &opt );
    p.drawItemText ( rect(), Qt::AlignCenter, opt.palette, isEnabled(), text() );
}
