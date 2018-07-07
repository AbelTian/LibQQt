#include <qqtosdframe.h>

QQtOSDFrame::QQtOSDFrame ( QWidget* parent ) : QQtWidget ( parent )
{
    setAttribute ( Qt::WA_TranslucentBackground, true );
}

QQtOSDFrame::~QQtOSDFrame() {}

void QQtOSDFrame::paintEvent ( QPaintEvent* event )
{
    //这个效果一般，如果用户特别需要，自己绘制。
#if 0
    QPainter p ( this );
    QPen pen = p.pen();
    pen.setWidth ( 3 );
    pen.setColor ( QColor ( 127, 188, 248 ) );
    p.setPen ( pen );
    p.drawLine ( QPoint ( 0, 0 ), QPoint ( 0, height() ) );
    p.drawLine ( QPoint ( 0, height() ), QPoint ( width(), height() ) );
    p.drawLine ( QPoint ( width(), height() ), QPoint ( width(), 0 ) );
#endif
    QQtWidget::paintEvent ( event );
}
