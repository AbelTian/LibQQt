#include "qqtsvgradiobutton.h"

QQtSvgRadioButton::QQtSvgRadioButton ( QWidget* parent ) : QQtRadioButton ( parent )
{

}

const TBtnIconTable& QQtSvgRadioButton::iconTable() const
{
    return mIconTable;
}

TBtnIconTable& QQtSvgRadioButton::iconTable()
{
    return mIconTable;
}

QString QQtSvgRadioButton::stateImage ( int index )
{
    if ( index < BTN_NORMAL || index > BTN_MAX - 1 )
        return mIconTable[BTN_NORMAL];
    return mIconTable[index];
}

void QQtSvgRadioButton::setStateImage ( int index, const QString& image )
{
    if ( index < BTN_NORMAL || index > BTN_MAX - 1 )
        return;
    mIconTable[index] = image;
    //translateImage();
    update();
}

void QQtSvgRadioButton::setNormalImage ( const QString& normal, const QString& press )
{
    mIconTable[BTN_NORMAL] = normal;
    mIconTable[BTN_PRESS] = press;
    //translateImage();
    update();
}

void QQtSvgRadioButton::setHoverImage ( const QString& hover )
{
    mIconTable[BTN_HOVER] = hover;
    //translateImage();
    update();
}

void QQtSvgRadioButton::setDisableImage ( const QString& disable )
{
    mIconTable[BTN_DISABLE] = disable;
    //translateImage();
    update();
}


void QQtSvgRadioButton::renderToVariable()
{
    TBtnIconTable& pic = iconTable();

    for ( int i = 0; i < BTN_MAX; i++ )
        r[i].load ( pic[i] );
}


void QQtSvgRadioButton::paintEvent ( QPaintEvent* event )
{
    Q_UNUSED ( event )

    QStylePainter p ( this );
    int  bs = isChecked() ? BTN_PRESS : BTN_NORMAL;
    if ( r[bs].isValid() )
        r[bs].render ( &p );

    bool enabled = isEnabled();
    QStyleOptionButton opt;
    initStyleOption ( &opt );
    p.drawItemText ( rect(), Qt::AlignCenter, opt.palette, enabled, text() );
}
