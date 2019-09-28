#include <testshadowwidget2.h>

#include <QPainter>

#include <QtMath>

#include <qqtbodymover.h>

#include <qqtcore.h>

TestShadowWidget2::TestShadowWidget2 ( QWidget* parent ) : QWidget ( parent )
{
    setWindowFlag ( Qt::FramelessWindowHint );
    setAttribute ( Qt::WA_TranslucentBackground );

    QQtBodyMover* mover = new QQtBodyMover ( this );
    installEventFilter ( mover );
}

TestShadowWidget2::~TestShadowWidget2() {}


void TestShadowWidget2::paintEvent ( QPaintEvent* event )
{

    //return QWidget::paintEvent ( event );
#if 0
    QWidget* wgt = this;

    QPainter painter ( wgt );
    QColor color ( 217, 229, 246, 55 );
    for ( int i = 0; i < 10; i++ )
    {
        QPainterPath path;
        path.setFillRule ( Qt::OddEvenFill );
        path.addRoundRect ( 10 - i, 10 - i,
                            wgt->width() - ( 10 - i ) * 2,
                            wgt->height() - ( 10 - i ) * 2,
                            4 );
        color.setAlpha ( 255 - qSqrt ( i ) * 70 );
        painter.setPen ( color );
        painter.drawPath ( path );

    }
#endif

#if 0
    QPainterPath path;
    path.setFillRule ( Qt::WindingFill );
    path.addRect ( 10, 10, this->width() - 20, this->height() - 20 );

    QPainter painter ( this );
    painter.setRenderHint ( QPainter::Antialiasing, true );
    painter.fillPath ( path, QBrush ( Qt::white ) );

    QColor color ( 0, 0, 0, 50 );
    for ( int i = 0; i < 10; i++ )
    {
        QPainterPath path;
        path.setFillRule ( Qt::WindingFill );
        path.addRect ( 10 - i, 10 - i, this->width() - ( 10 - i ) * 2, this->height() - ( 10 - i ) * 2 );
        color.setAlpha ( 150 - qSqrt ( i ) * 50 );
        painter.setPen ( color );
        painter.drawPath ( path );
    }
#endif


#if 1
    //颜色样式解决了，

    //还要解决位置，从margin开始到10.
    //如何让margin区域透明呢？setMask？

    //不能从margin开始，应该从frameGeometry开始。
    //注意下painter的平移。painterpath是必须从0开始画。painter需要平移一定的距离。translate
    //难点。
    //高级绘图、视频播放、3D、动画

    QPainter painter ( this );

    //QPainterPath path;
    //path.setFillRule ( Qt::WindingFill );
    //path.addRoundRect ( 10, 10, this->width() - 20, this->height() - 20, 3 );
    //painter.setRenderHint ( QPainter::Antialiasing, true );
    //pline() << painter.background().color();
    //painter.fillPath ( path, painter.background().color() );

    //50这里没用
    QColor color ( 0, 0, 0, 50 );
    //40代表了横跨幅
    int j = 40;
    for ( int i = 0; i < j; i++ )
    {
        QPainterPath path;
        path.setFillRule ( Qt::WindingFill );
        //10就是margin。xxx
        //画的圈子越来越大
        path.addRoundRect ( j - i, j - i, this->width() - ( j - i ) * 2, this->height() - ( j - i ) * 2, 3 );
        //颜色越来越浅。 初始数字越小，效果越好，越精细。
        qreal alpha = 10 - ( qreal ) i * 1 / ( j / 30 ); //150 - qSqrt ( i ) * 50 ;
        //无论如何不能过滤，都是细线。
        //if ( ( ( int ) ( alpha / 10 ) % 2  ) == 1 )
        //    continue;
        if ( alpha >= 0 )
        {
            color.setAlpha ( alpha );
            pline() << alpha;
            painter.setPen ( color );
            painter.drawPath ( path );
        }
    }

    //pline() << painter.compositionMode();
    //painter.setCompositionMode ( QPainter::CompositionMode_Clear );
    //painter.fillPath ( path, QBrush ( Qt::white ) );

    QPainterPath p0;
    p0.addRoundRect ( 40, 40, 80, 80, 3 );
    p0.addRoundRect ( 50, 50, 50, 50, 3 );
    //painter.save();
    QPainter::CompositionMode m0 = painter.compositionMode();
    painter.setCompositionMode ( QPainter::CompositionMode_Clear );
    painter.fillPath ( p0, QBrush ( Qt::transparent ) );
    painter.setCompositionMode ( m0 );
    //painter.restore();

#endif

}
