#include "testwidget.h"
#include <QPainter>
#include <QBitmap>

TestWidget::TestWidget ( QWidget* parent ) : QWidget ( parent )
{
    //setAttribute ( Qt::WA_TranslucentBackground, true );
    //setAttribute ( Qt::WA_OpaquePaintEvent, true );
    //QPalette pal = palette();
    //pal.setColor ( QPalette::Background, QColor ( 255, 0, 0, 200 ) );
    //setPalette ( pal );
    //setStyleSheet ( "background:transparent" );

}
void TestWidget::paintEvent ( QPaintEvent* event )
{

    //return QWidget::paintEvent ( event );

    //QPainter painter ( this );
    //painter.fillRect ( this->rect(), QColor ( 0, 0, 255, 80 ) );

    //QPainter p ( this );
    //p.setCompositionMode ( QPainter::CompositionMode_Clear );
    //p.fillRect ( 10, 10, 300, 300, Qt::SolidPattern );
}


void TestWidget::resizeEvent ( QResizeEvent* event )
{
    // Use a bitmap as a mask. A bitmap only has two kind of colors: white(value is 0)
    // or black(other values). When we use it to set mask, we can see the window at the position
    // where the color value is 0, and other place will be transparent.
    QBitmap bitMap ( width(), height() ); // A bit map has the same size with current widget
    QPainter painter ( &bitMap );
    painter.setPen ( QColor ( 0, 0, 0 ) ); // Any color that is not QRgb(0,0,0) is right
    painter.drawRect ( 0, 0, width(), height() );
    setMask ( bitMap );
}
