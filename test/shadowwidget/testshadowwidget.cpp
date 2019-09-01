#include <testshadowwidget.h>

#include <QPainter>

TestShadowWidget::TestShadowWidget ( QWidget* parent ) : QWidget ( parent )
{
    setWindowFlags ( Qt::FramelessWindowHint ); //设置为无外部边框
    setAttribute ( Qt::WA_TranslucentBackground ); //设置窗口为透明
    setGeometry ( 400, 500, 800, 600 );
    QLabel* m_pback = new QLabel ( this );
    m_pback->setGeometry ( 0, 0, this->width() - 10, this->height() - 10 );
    m_pback->setObjectName ( "MainWidget" ); //此处设置ObjectName是为了加载qss效果
    QGraphicsDropShadowEffect* Shadow = new QGraphicsDropShadowEffect();
    Shadow->setBlurRadius ( 8.0 );
    Shadow->setColor ( QColor ( 63, 63, 63, 180 ) );
    Shadow->setOffset ( 8.0 );
    m_pback->setGraphicsEffect ( Shadow );
}

TestShadowWidget::~TestShadowWidget() {}


void TestShadowWidget::paintEvent ( QPaintEvent* event )
{
    QPainter p ( this );

    QPen pen ( QColor ( 55, 33, 125 ) );
    p.setPen ( pen );
    QBrush br ( Qt::red );
    p.setBrush ( br );
    QRect r0 = rect();
    p.drawRect ( r0 );
}
