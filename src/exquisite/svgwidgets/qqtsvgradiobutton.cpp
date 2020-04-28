#include "qqtsvgradiobutton.h"

QQtSvgRadioButton::QQtSvgRadioButton ( QWidget* parent ) : QQtRadioButton ( parent )
{

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
    renderToVariable();
    //update();
}

void QQtSvgRadioButton::setNormalImage ( const QString& normal, const QString& press )
{
    mIconTable[BTN_NORMAL] = normal;
    mIconTable[BTN_PRESS] = press;
    renderToVariable();
    //update();
}

void QQtSvgRadioButton::setHoverImage ( const QString& hover )
{
    mIconTable[BTN_HOVER] = hover;
    renderToVariable();
    //update();
}

void QQtSvgRadioButton::setDisableImage ( const QString& disable )
{
    mIconTable[BTN_DISABLE] = disable;
    renderToVariable();
    //update();
}

const TBtnIconTable& QQtSvgRadioButton::iconTable() const
{
    return mIconTable;
}

TBtnIconTable& QQtSvgRadioButton::iconTable()
{
    return mIconTable;
}

void QQtSvgRadioButton::renderToVariable()
{
    TBtnIconTable& pic = iconTable();

    for ( int i = 0; i < BTN_MAX; i++ )
        r[i].load ( pic[i] );

    translateImage();
}

void QQtSvgRadioButton::translateImage()
{
    update();
}


void QQtSvgRadioButton::paintEvent ( QPaintEvent* event )
{
    Q_UNUSED ( event )

    QStylePainter p ( this );
    int  bs = workState();

    if ( isCheckable() )
#ifdef __EMBEDDED_LINUX__
#else
        if ( !isHover() )
#endif
        if ( isChecked() )
            bs = BTN_CHECK;
        else
            bs = BTN_UNCHECK;

    if ( !isEnabled() )
        bs = BTN_DISABLE;

    if ( r[bs].isValid() )
        r[bs].render ( &p );

    bool enabled = isEnabled();
    QStyleOptionButton opt;
    initStyleOption ( &opt );
    p.drawItemText ( rect(), Qt::AlignCenter, opt.palette, enabled, text() );
}
