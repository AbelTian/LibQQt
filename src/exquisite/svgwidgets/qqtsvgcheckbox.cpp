#include "qqtsvgcheckbox.h"

QQtSvgCheckBox::QQtSvgCheckBox ( QWidget* parent ) : QQtCheckBox ( parent )
{

}

const TBtnIconTable& QQtSvgCheckBox::iconTable() const
{
    return mIconTable;
}

TBtnIconTable& QQtSvgCheckBox::iconTable()
{
    return mIconTable;
}

QString QQtSvgCheckBox::stateImage ( int index )
{
    if ( index < BTN_NORMAL || index > BTN_MAX - 1 )
        return mIconTable[BTN_NORMAL];
    return mIconTable[index];
}

void QQtSvgCheckBox::setStateImage ( int index, const QString& image )
{
    if ( index < BTN_NORMAL || index > BTN_MAX - 1 )
        return;
    mIconTable[index] = image;
    //translateImage();
    update();
}

void QQtSvgCheckBox::setNormalImage ( const QString& normal, const QString& press )
{
    mIconTable[BTN_NORMAL] = normal;
    mIconTable[BTN_PRESS] = press;
    //translateImage();
    update();
}

void QQtSvgCheckBox::setHoverImage ( const QString& hover )
{
    mIconTable[BTN_HOVER] = hover;
    //translateImage();
    update();
}

void QQtSvgCheckBox::setDisableImage ( const QString& disable )
{
    mIconTable[BTN_DISABLE] = disable;
    //translateImage();
    update();
}


void QQtSvgCheckBox::renderToVariable()
{
    TBtnIconTable& pic = iconTable();

    for ( int i = 0; i < BTN_MAX; i++ )
        r[i].load ( pic[i] );
}


void QQtSvgCheckBox::paintEvent ( QPaintEvent* event )
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
