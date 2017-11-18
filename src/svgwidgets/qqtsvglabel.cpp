#include "qqtsvglabel.h"
#include <QStylePainter>
#include <QStyleOptionFrame>

QQtSvgLabel::QQtSvgLabel ( QWidget* parent ) : QQtLabel ( parent )
{

}

void QQtSvgLabel::setSvgFile ( QString& filename )
{
    mSvgRender.load ( filename );
}

void QQtSvgLabel::setSvgContent ( QByteArray& bytes )
{
    mSvgRender.load ( bytes );
}


void QQtSvgLabel::paintEvent ( QPaintEvent* event )
{
    Q_UNUSED ( event )

    QStylePainter p ( this );

    if ( mSvgRender.isValid() )
        mSvgRender.render ( &p );

    bool enabled = isEnabled();
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    p.drawItemText ( rect(), alignment(), palette(), enabled, text() );
#else
    QStyleOptionFrame opt;
    initStyleOption ( &opt );
    p.drawItemText ( rect(), alignment(), opt.palette, enabled, text() );
#endif
}
