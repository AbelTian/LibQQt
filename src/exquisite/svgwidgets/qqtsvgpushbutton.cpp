#include "qqtsvgpushbutton.h"

QQtSvgPushButton::QQtSvgPushButton ( QWidget* parent ) : QQtPushButton ( parent )
{

}

const TBtnIconTable& QQtSvgPushButton::iconTable() const
{
    return mIconTable;
}

TBtnIconTable& QQtSvgPushButton::iconTable()
{
    return mIconTable;
}

QString QQtSvgPushButton::stateImage ( int index )
{
    if ( index < BTN_NORMAL || index > BTN_MAX - 1 )
        return mIconTable[BTN_NORMAL];
    return mIconTable[index];
}

void QQtSvgPushButton::setStateImage ( int index, const QString& image )
{
    if ( index < BTN_NORMAL || index > BTN_MAX - 1 )
        return;
    mIconTable[index] = image;
    //translateImage();
    update();
}

void QQtSvgPushButton::setNormalImage ( const QString& normal, const QString& press )
{
    mIconTable[BTN_NORMAL] = normal;
    mIconTable[BTN_PRESS] = press;
    //translateImage();
    update();
}

void QQtSvgPushButton::setHoverImage ( const QString& hover )
{
    mIconTable[BTN_HOVER] = hover;
    //translateImage();
    update();
}

void QQtSvgPushButton::setDisableImage ( const QString& disable )
{
    mIconTable[BTN_DISABLE] = disable;
    //translateImage();
    update();
}


void QQtSvgPushButton::renderToVariable()
{
    TBtnIconTable& pic = iconTable();

    for ( int i = 0; i < BTN_MAX; i++ )
        r[i].load ( pic[i] );
}



void QQtSvgPushButton::paintEvent ( QPaintEvent* event )
{
    Q_UNUSED ( event )

    QStylePainter p ( this );
    int bs = workState();
    if ( r[bs].isValid() )
        r[bs].render ( &p );

    bool enabled = isEnabled();

    QStyleOptionButton opt;
    initStyleOption ( &opt );
    p.drawItemText ( rect(), Qt::AlignCenter, opt.palette, enabled, text() );
}
