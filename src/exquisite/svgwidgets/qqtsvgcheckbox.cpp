#include "qqtsvgcheckbox.h"

QQtSvgCheckBox::QQtSvgCheckBox ( QWidget* parent ) : QQtCheckBox ( parent )
{

}

void QQtSvgCheckBox::renderToVariable()
{
    TBtnImageTable& pic = imageTable();

    for ( int i = 0; i < BTN_MAX; i++ )
        r[i].load ( QByteArray ( ( const char* ) pic[i].bits(), pic[i].byteCount() ) );
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
