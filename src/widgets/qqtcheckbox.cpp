#include "qqtcheckbox.h"
#include <QStylePainter>
#include "qqtwidgets.h"

QQtCheckBox::QQtCheckBox ( QWidget* parent ) :
    QCheckBox ( parent )
{
    mWorkState = BTN_NORMAL;
}

QQtCheckBox::~QQtCheckBox()
{
}

const TBtnImageTable& QQtCheckBox::imageTable() const
{
    return mImageTable;
}

TBtnImageTable& QQtCheckBox::imageTable()
{
    return mImageTable;
}

void QQtCheckBox::translateImage()
{
    int state = mWorkState;

    //qDebug() << isEnabled();

    if ( !isEnabled() )
        state = BTN_DISABLE;

    setImage ( mImageTable[state] );
}

void QQtCheckBox::setImage ( const QImage& image )
{
    mImage = image;
    //update();
}

int QQtCheckBox::workState() const
{
    return mWorkState;
}

void QQtCheckBox::setWorkState ( int index )
{
    mWorkState = ( EBtnStatus ) index;
    //translateImage();
    //update();
}


QImage QQtCheckBox::stateImage ( int index )
{
    if ( index < BTN_NORMAL || index > BTN_MAX - 1 )
        return mImageTable[BTN_NORMAL];
    return mImageTable[index];
}

void QQtCheckBox::setStateImage ( int index, const QImage& image )
{
    if ( index < BTN_NORMAL || index > BTN_MAX - 1 )
        return;
    mImageTable[index] = image;
    //translateImage();
    update();
}

void QQtCheckBox::setNormalImage ( const QImage& normal, const QImage& press )
{
    mImageTable[BTN_NORMAL] = normal;
    mImageTable[BTN_PRESS] = press;
    //translateImage();
    update();
}

void QQtCheckBox::setHoverImage ( const QImage& hover )
{
    mImageTable[BTN_HOVER] = hover;
    //translateImage();
    update();
}

void QQtCheckBox::setDisableImage ( const QImage& disable )
{
    mImageTable[BTN_DISABLE] = disable;
    //translateImage();
    update();
}

void QQtCheckBox::setEnabled ( bool stat )
{
    //qDebug() << stat;
    QCheckBox::setEnabled ( stat );
    if ( stat )
        setWorkState ( BTN_NORMAL );
    else
        setWorkState ( BTN_DISABLE );
    update();
}

void QQtCheckBox::setDisabled ( bool stat )
{
    QCheckBox::setDisabled ( stat );
    if ( !stat )
        setWorkState ( BTN_NORMAL );
    else
        setWorkState ( BTN_DISABLE );
    update();
}

void QQtCheckBox::mousePressEvent ( QMouseEvent* event )
{
    if ( event->button() == Qt::LeftButton )
    {
        mWorkState = BTN_PRESS;
    }
    QCheckBox::mousePressEvent ( event );
    //translateImage();
    update();
}

void QQtCheckBox::mouseReleaseEvent ( QMouseEvent* event )
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
    QCheckBox::mouseReleaseEvent ( event );
    //translateImage();
    update();
}

void QQtCheckBox::enterEvent ( QEvent* event )
{
    mWorkState = BTN_HOVER;
    QCheckBox::enterEvent ( event );
    //translateImage();
    update();
}

void QQtCheckBox::leaveEvent ( QEvent* event )
{
    mWorkState = BTN_NORMAL;
    QCheckBox::leaveEvent ( event );
    //translateImage();
    update();
}


void QQtCheckBox::paintEvent ( QPaintEvent* event )
{
    //把imageTable()[stat]设置到mImage。
    translateImage();

    if ( mImage.isNull() )
        return QCheckBox::paintEvent ( event );

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


bool QQtCheckBox::hitButton ( const QPoint& pos ) const
{
    Q_UNUSED ( pos )
    //TODO:
    return true;
}
