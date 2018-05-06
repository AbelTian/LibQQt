#include "qqtosdform.h"
#include "ui_qqtosdform.h"
#include <QPainter>
#include <QBitmap>

QQtOsdForm::QQtOsdForm ( QWidget* parent ) :
    QWidget ( parent ),
    ui ( new Ui::QQtOsdForm )
{
    ui->setupUi ( this );
    //setStyleSheet ( "QQtOsdForm{ background-color: rgb(222, 222, 222, 0);}" );
    //setWindowFlag ( Qt::FramelessWindowHint, true );
    setWindowFlag ( Qt::WindowStaysOnTopHint, true );
    setWindowFlag ( Qt::Tool, true );
    setAttribute ( Qt::WA_TranslucentBackground, true );

    QPalette pal = palette();
    pal.setColor ( QPalette::Background, QColor ( 255, 255, 255, 255 ) );
    //setPalette ( pal );

}

QQtOsdForm::~QQtOsdForm()
{
    delete ui;
}


void QQtOsdForm::paintEvent ( QPaintEvent* event )
{
    return QWidget::paintEvent ( event );

    // Use a bitmap as a mask. A bitmap only has two kind of colors: white(value is 0)
    // or black(other values). When we use it to set mask, we can see the window at the position
    // where the color value is 0, and other place will be transparent.
    QBitmap bitMap ( width(), height() ); // A bit map has the same size with current widget
    QPainter painter ( &bitMap );
    painter.setPen ( QColor ( 255, 255, 255 ) ); // Any color that is not QRgb(0,0,0) is right
    painter.drawRect ( 0, 0, width(), height() );
    setMask ( bitMap );
}
