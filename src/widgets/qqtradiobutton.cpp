#include "qqtradiobutton.h"
#include <QStylePainter>

QQtRadioButton::QQtRadioButton ( QWidget* parent ) :
    QRadioButton ( parent )
{
    mWorkState = BTN_NORMAL;
}

QQtRadioButton::~QQtRadioButton()
{
}

const TBtnImageTable& QQtRadioButton::imageTable() const
{
    return mImageTable;
}

TBtnImageTable& QQtRadioButton::imageTable()
{
    return mImageTable;
}

void QQtRadioButton::translateImage()
{
    int state = mWorkState;

    //qDebug() << isEnabled();

    if ( !isEnabled() )
        state = BTN_DISABLE;

    setImage ( mImageTable[state] );
}

void QQtRadioButton::setImage ( const QImage& image )
{
    mImage = image;
    update();
}

int QQtRadioButton::workState() const
{
    return mWorkState;
}

void QQtRadioButton::setWorkState ( int index )
{
    mWorkState = ( EBtnStatus ) index;
    translateImage();
}


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
    translateImage();
}

void QQtRadioButton::setNormalImage ( const QImage& normal, const QImage& press )
{
    mImageTable[BTN_NORMAL] = normal;
    mImageTable[BTN_PRESS] = press;
    translateImage();
}

void QQtRadioButton::setHoverImage ( const QImage& hover )
{
    mImageTable[BTN_HOVER] = hover;
    translateImage();
}

void QQtRadioButton::setDisableImage ( const QImage& disable )
{
    mImageTable[BTN_DISABLE] = disable;
    translateImage();
}

void QQtRadioButton::setEnabled ( bool stat )
{
    //qDebug() << stat;
    QRadioButton::setEnabled ( stat );
    if ( stat )
        setWorkState ( BTN_NORMAL );
    else
        setWorkState ( BTN_DISABLE );
}

void QQtRadioButton::setDisabled ( bool stat )
{
    QRadioButton::setDisabled ( stat );
    if ( !stat )
        setWorkState ( BTN_NORMAL );
    else
        setWorkState ( BTN_DISABLE );
}

void QQtRadioButton::mousePressEvent ( QMouseEvent* event )
{
    if ( event->button() == Qt::LeftButton )
    {
        mWorkState = BTN_PRESS;
    }
    QRadioButton::mousePressEvent ( event );
    translateImage();
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
    translateImage();
}

void QQtRadioButton::enterEvent ( QEvent* event )
{
    mWorkState = BTN_HOVER;
    QRadioButton::enterEvent ( event );
    translateImage();
}

void QQtRadioButton::leaveEvent ( QEvent* event )
{
    mWorkState = BTN_NORMAL;
    QRadioButton::leaveEvent ( event );
    translateImage();
}


void QQtRadioButton::paintEvent ( QPaintEvent* event )
{
    if ( mImage.isNull() )
        return QRadioButton::paintEvent ( event );

    //qDebug() << isEnabled() << mWorkState;

    QStylePainter p ( this );
    p.drawItemPixmap ( rect(), Qt::AlignCenter, QIcon ( QPixmap::fromImage ( mImage ) ).pixmap ( rect().size(),
                       QIcon::Normal, QIcon::On ) );

    QStyleOptionButton opt;
    initStyleOption ( &opt );
    p.drawItemText ( rect(), Qt::AlignCenter, opt.palette, isEnabled(), text() );
}


bool QQtRadioButton::hitButton ( const QPoint& pos ) const
{
    Q_UNUSED ( pos )
    return true;
}
