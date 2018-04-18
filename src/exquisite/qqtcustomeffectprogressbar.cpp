#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "qqtcustomeffectprogressbar.h"
#include "qpainter.h"
#include "qdebug.h"
#include "qmath.h"
#include "qtimer.h"

QQtCustomEffectProgressBar::QQtCustomEffectProgressBar ( QWidget* parent ) : QWidget ( parent )
{
    minValue = 0;
    maxValue = 100;
    value = 0;
    text = "";

    nullPosition = 0;
    lineWidth = 10;
    cornerRadius = 10;

    showPercent = true;
    showFree = false;
    showSmallCircle = false;
    clockWise = true;

    usedColor = QColor ( 100, 184, 255 );
    freeColor = QColor ( 100, 100, 100 );
    backgroundColor = QColor ( 70, 70, 70 );
    textColor = QColor ( 250, 250, 250 );
    textFont = font();
    percentColor = QColor ( 250, 250, 250 );
    percentFont = font();

    textStyle = TextStyle_Percent;
    designStyle = DesignStyle_Circle;
    percentStyle = PercentStyle_Arc;
    backgroundType = BackgroundType_Color;

    percentSuffix = "%";

    waveDensity = 2;
    waveHeight = 2;
    waveSpeed = 6;
    waveDirection = WaveDirection_Left;

    timer = new QTimer ( this );
    timer->setSingleShot ( false );
    connect ( timer, SIGNAL ( timeout() ), this, SLOT ( update() ) );
}

QQtCustomEffectProgressBar::~QQtCustomEffectProgressBar()
{
}

void QQtCustomEffectProgressBar::paintEvent ( QPaintEvent* )
{
    int width = this->width();
    int height = this->height();
    /*显示实长*/
    int side = qMin ( width, height );

    /*绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放*/
    QPainter painter ( this );
    painter.setRenderHints ( QPainter::Antialiasing | QPainter::TextAntialiasing );
    /*平移坐标系*/
    //-width/2 width/2
    //-height/2 height/2
    painter.translate ( width / 2, height / 2 );

    /*更改刻度 设置的是缩放的倍数 */
    /*有利于在绘制的时候，统一绘制数据*/
    /*矢量放大，不失真*/
    //-100, 100
    //-100, 100
    if ( designStyle == DesignStyle_Circle
         || designStyle == DesignStyle_Square )
        painter.scale ( side / 200.0, side / 200.0 );
    else if ( designStyle == DesignStyle_Ellipse
              || designStyle == DesignStyle_Rectangle )
        painter.scale ( width / 200.0, height / 200.0 );

    /*绘制中心圆*/
    /*
     * 实际显示到屏幕的大小（显示实长）为
     * QPainter绘制区域大小（绘制用数据） * 倍率
     * 200 * ( side / 200.0 )
     */
    drawBackground ( &painter, 99 );

    /*根据样式绘制进度*/
    if ( percentStyle == PercentStyle_Arc )
    {
        drawArc ( &painter, 99 - lineWidth / 2 );
    }
    else if ( percentStyle == PercentStyle_Polo )
    {
        drawPolo ( &painter, 99 );
    }
    else if ( percentStyle == PercentStyle_Arc_Polo )
    {
        drawArc ( &painter, 99 - lineWidth / 2 );
        drawPolo ( &painter, 99 - lineWidth * 2 );
    }
    else if ( percentStyle == PercentStyle_Wave )
    {
        drawWave ( &painter, 99 );
    }

    /*绘制当前值*/
    drawText ( &painter, 100 );
    drawPercentText ( &painter, 100 );
}

void QQtCustomEffectProgressBar::drawBackground ( QPainter* painter, int radius )
{
    if ( percentStyle == PercentStyle_Arc )
    {
        radius = radius - lineWidth;
    }
    else if ( percentStyle == PercentStyle_Arc_Polo )
    {
        radius = radius - lineWidth * 2;
    }

    painter->save();
    painter->setPen ( Qt::NoPen );
    painter->setBrush ( backgroundColor );

    if ( backgroundType == BackgroundType_Color )
    {
        if ( designStyle == DesignStyle_Circle
             || designStyle == DesignStyle_Ellipse )
            painter->drawEllipse ( -radius, -radius, radius * 2, radius * 2 );
        else if ( designStyle == DesignStyle_Rectangle
                  || designStyle == DesignStyle_Square )
            painter->drawRoundRect ( -radius, -radius, radius * 2, radius * 2,
                                     cornerRadius, cornerRadius );
    }
    else
    {
        QPixmap pix;
        pix = QPixmap ( backgroundImage );

        /*自动等比例平滑缩放居中显示*/
        int targetWidth = pix.width();
        int targetHeight = pix.height();
        pix = pix.scaled ( targetWidth, targetHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation );

        painter->drawPixmap ( -radius, -radius, radius * 2, radius * 2, pix );
    }

    painter->restore();
}

void QQtCustomEffectProgressBar::drawArc ( QPainter* painter, int radius )
{
    painter->save();
    painter->setBrush ( Qt::NoBrush );

    QPen pen = painter->pen();
    pen.setWidthF ( lineWidth );

    /*这里可以更改画笔样式更换线条风格*/
    pen.setCapStyle ( Qt::RoundCap );

    double arcLength = 360.0 / ( maxValue - minValue ) * ( value - minValue );
    QRect rect ( -radius, -radius, radius * 2, radius * 2 );

    /*逆时针为顺时针分负数*/
    if ( !clockWise )
    {
        arcLength = -arcLength;
    }

    /*绘制剩余进度圆弧*/
    if ( showFree )
    {
        pen.setColor ( freeColor );
        painter->setPen ( pen );
        painter->drawArc ( rect, ( nullPosition - arcLength ) * 16, - ( 360 - arcLength ) * 16 );
    }

    /*绘制当前进度圆弧*/
    pen.setColor ( usedColor );
    painter->setPen ( pen );
    painter->drawArc ( rect, nullPosition * 16, -arcLength * 16 );

    /*绘制进度圆弧前面的小圆*/
    if ( showSmallCircle )
    {
        int offset = radius - lineWidth + 1;
        radius = lineWidth / 2 - 1;
        painter->rotate ( -nullPosition - 90 );

        QRect circleRect ( -radius, radius + offset, radius * 2, radius * 2 );
        painter->rotate ( arcLength );
        painter->drawEllipse ( circleRect );
    }

    painter->restore();
}

void QQtCustomEffectProgressBar::drawPolo ( QPainter* painter, int radius )
{
    /*计算当前值所占百分比对应高度*/
    double poloHeight = ( double ) radius / ( maxValue - minValue ) * ( value - minValue ) ;

    /*大圆路径*/
    QPainterPath bigPath;

    if ( designStyle == DesignStyle_Circle
         || designStyle == DesignStyle_Ellipse )
        bigPath.addEllipse ( -radius, -radius, radius * 2, radius * 2 );
    else if ( designStyle == DesignStyle_Rectangle
              || designStyle == DesignStyle_Square )
        bigPath.addRoundedRect ( -radius, -radius, radius * 2, radius * 2,
                                 cornerRadius, cornerRadius );

    /*底部水池灌水所占的矩形区域路径*/
    QPainterPath smallPath;
    smallPath.addRect ( -radius, radius - poloHeight * 2, radius * 2, poloHeight * 2 );

    /*将两个路径重合相交部分提取,就是水池注水所占面积*/
    QPainterPath path;
    path = bigPath.intersected ( smallPath );

    painter->save();

    painter->setPen ( usedColor );
    painter->setBrush ( usedColor );
    painter->drawPath ( path );

    painter->restore();
}

void QQtCustomEffectProgressBar::drawWave ( QPainter* painter, int radius )
{
    /*大路径*/
    QPainterPath bigPath;

    if ( designStyle == DesignStyle_Circle
         || designStyle == DesignStyle_Ellipse )
        bigPath.addEllipse ( -radius, -radius, radius * 2, radius * 2 );
    else if ( designStyle == DesignStyle_Rectangle
              || designStyle == DesignStyle_Square )
        /*
         * addRoundRect bug:
         * 30% 左右 图形闪烁 经过分析为QPainterPath计算公共区域时在圆角上出了错误。
        */
        bigPath.addRoundedRect ( -radius, -radius, radius * 2, radius * 2,
                                 cornerRadius, cornerRadius );

    /*正弦曲线公式 y = A * sin(ωx + φ) + k*/
    /*A表示振幅,可以理解为水波的高度,值越大高度越高(越浪 ^_^),取值高度的百分比*/
    double A = waveHeight;

    /*w表示周期,可以理解为水波的密度,值越大密度越大(浪越密集 ^_^),取值 密度*M_PI/宽度*/
    double w = waveDensity * M_PI / 100;

    /*计算当前值所占百分比*/
    /*k表示y轴偏移,可以理解为进度,取值高度的进度百分比*/
    double k = radius * 2 * ( ( double ) ( value - minValue ) / ( maxValue - minValue ) );

    static double offset = 0;
    /*>=1, wave will lost leisurely */
    offset += 0.6;

    if ( offset > 180 )
    {
        offset = 0;
    }

    int offset1 = offset;
    int offset2 = offset;

    if ( WaveDirection_Right == waveDirection )
    {
        offset1 *= -1;
        offset2 *= -1;
    }
    else if ( WaveDirection_Left_Right == waveDirection )
    {
        offset2 *= -1;
    }
    else if ( WaveDirection_Right_Left == waveDirection )
    {
        offset1 *= -1;
    }


    /*第一条波浪路径集合*/
    QPainterPath waterPath1;
    /*移动到左上角起始点*/
    waterPath1.moveTo ( -radius, k );

    for ( int x = -radius; x <= radius; x++ )
    {
        /*第一条波浪Y轴*/
        double waterY1 = ( double ) ( A * sin ( w * x + offset1 ) ) + radius - k;

        /*如果当前值为最小值则Y轴为高度*/
        if ( this->value == minValue )
        {
            waterY1 = radius;
        }

        /*如果当前值为最大值则Y轴为0*/
        if ( this->value == maxValue )
        {
            waterY1 = -radius;
        }

        waterPath1.lineTo ( x, waterY1 );
    }

    /*移动到右下角结束点,整体形成一个闭合路径*/
    waterPath1.lineTo ( radius, radius );
    waterPath1.lineTo ( -radius, radius );
    waterPath1.lineTo ( -radius, k );

    /*第二条波浪路径集合*/
    QPainterPath waterPath2;
    waterPath2.moveTo ( -radius, k );

    for ( int x = -radius; x <= radius; x++ )
    {
        /*第二条波浪Y轴*/
        double waterY2 = ( double ) ( A * sin ( w * x + offset2 + 180 ) ) + radius - k;

        /*如果当前值为最小值则Y轴为高度*/
        if ( this->value == minValue )
        {
            waterY2 = radius;
        }

        /*如果当前值为最大值则Y轴为0*/
        if ( this->value == maxValue )
        {
            waterY2 = -radius;
        }

        waterPath2.lineTo ( x, waterY2 );
    }

    waterPath2.lineTo ( radius, radius );
    waterPath2.lineTo ( -radius, radius );
    waterPath2.lineTo ( -radius, k );



    painter->save();
    /*新路径,用大路径减去波浪区域的路径,形成遮罩效果*/
    /*第一条波浪挖去后的路径*/
    QPainterPath path1;
    path1 = bigPath.intersected ( waterPath1 );
    QColor path1Color = usedColor;
    path1Color.setAlpha ( 100 );
    painter->setPen ( path1Color );
    painter->setBrush ( path1Color );
    painter->drawPath ( path1 );

    /*第二条波浪挖去后的路径*/
    QPainterPath path2;
    path2 = bigPath.intersected ( waterPath2 );
    QColor path2Color = usedColor;
    path2Color.setAlpha ( 180 );
    painter->setPen ( path2Color );
    painter->setBrush ( path2Color );
    painter->drawPath ( path2 );

    painter->restore();
}

void QQtCustomEffectProgressBar::drawText ( QPainter* painter, int radius )
{
    QString strText = QString ( "%1" ).arg ( text );


    if ( textStyle == TextStyle_None )
        return;


    else if ( textStyle == TextStyle_Text
              || textStyle == TextStyle_Percent_Text )
    {
        painter->save();
        painter->setPen ( textColor );
        painter->setFont ( textFont );

        QFontMetricsF fm ( textFont );
        QSizeF textSize = fm.size ( Qt::TextSingleLine, strText );
        QRectF textRect ( -textSize.width() / 2, -textSize.height() / 2, textSize.width(), textSize.height() );
        painter->drawText ( textRect, Qt::AlignCenter, strText );

        painter->restore();
    }

}

void QQtCustomEffectProgressBar::drawPercentText ( QPainter* painter, int radius )
{
    QString strValue = QString ( "%1" ).arg ( value - minValue );

    if ( showPercent )
    {
        strValue = QString ( "%1%2" ).arg ( ( double ) ( value - minValue ) / ( maxValue - minValue ) * 100 )
                   .arg ( percentSuffix );
    }

    if ( textStyle == TextStyle_None )
        return;

    else if ( textStyle == TextStyle_Middle_Percent )
    {
        painter->save();
        painter->setPen ( percentColor );
        painter->setFont ( percentFont );

        QFontMetricsF fm ( percentFont );
        QSizeF textSize = fm.size ( Qt::TextSingleLine, strValue );
        QRectF textRect ( -textSize.width() / 2, -textSize.height() / 2, textSize.width(), textSize.height() );
        painter->drawText ( textRect, Qt::AlignCenter, strValue );

        painter->restore();
    }
    else if ( textStyle == TextStyle_Percent
              || textStyle == TextStyle_Percent_Text )
    {
        painter->save();
        painter->setPen ( percentColor );
        painter->setFont ( percentFont );

        QFontMetricsF fm ( percentFont );
        QSizeF textSize = fm.size ( Qt::TextSingleLine, strValue );
        QRectF textRect ( -textSize.width() / 2, 40, textSize.width(), textSize.height() );
        painter->drawText ( textRect, Qt::AlignCenter, strValue );

        painter->restore();
    }
}

int QQtCustomEffectProgressBar::getMinValue() const
{
    return this->minValue;
}

int QQtCustomEffectProgressBar::getMaxValue() const
{
    return this->maxValue;
}

int QQtCustomEffectProgressBar::getValue() const
{
    return this->value;
}

int QQtCustomEffectProgressBar::getNullPosition() const
{
    return this->nullPosition;
}

int QQtCustomEffectProgressBar::getLineWidth() const
{
    return this->lineWidth;
}

bool QQtCustomEffectProgressBar::getShowPercent() const
{
    return this->showPercent;
}

bool QQtCustomEffectProgressBar::getShowFree() const
{
    return this->showFree;
}

bool QQtCustomEffectProgressBar::getShowSmallCircle() const
{
    return this->showSmallCircle;
}

bool QQtCustomEffectProgressBar::getClockWise() const
{
    return this->clockWise;
}

QColor QQtCustomEffectProgressBar::getUsedColor() const
{
    return this->usedColor;
}

QColor QQtCustomEffectProgressBar::getFreeColor() const
{
    return this->freeColor;
}

QColor QQtCustomEffectProgressBar::getBackgroundColor() const
{
    return this->backgroundColor;
}

QColor QQtCustomEffectProgressBar::getTextColor() const
{
    return this->textColor;
}

QString QQtCustomEffectProgressBar::getPercentSuffix() const
{
    return this->percentSuffix;
}

QQtCustomEffectProgressBar::PercentStyle QQtCustomEffectProgressBar::getPercentStyle() const
{
    return this->percentStyle;
}

QQtCustomEffectProgressBar::BackgroundType QQtCustomEffectProgressBar::getBackgroundType() const
{
    return this->backgroundType;
}

QSize QQtCustomEffectProgressBar::sizeHint() const
{
    return QSize ( 200, 200 );
}

QSize QQtCustomEffectProgressBar::minimumSizeHint() const
{
    return QSize ( 10, 10 );
}

void QQtCustomEffectProgressBar::setRange ( int minValue, int maxValue )
{
    /*如果最小值大于或者等于最大值则不设置*/
    if ( minValue >= maxValue )
    {
        return;
    }

    this->minValue = minValue;
    this->maxValue = maxValue;

    /*如果目标值不在范围值内,则重新设置目标值*/
    if ( value < minValue || value > maxValue )
    {
        setValue ( value );
    }

    update();
}

void QQtCustomEffectProgressBar::setMinValue ( int minValue )
{
    setRange ( minValue, maxValue );
}

void QQtCustomEffectProgressBar::setMaxValue ( int maxValue )
{
    setRange ( minValue, maxValue );
}

void QQtCustomEffectProgressBar::setValue ( int value )
{
    /*值小于最小值或者值大于最大值或者值和当前值一致则无需处理*/
    if ( value < minValue || value > maxValue || value == this->value )
    {
        return;
    }

    this->value = value;
    update();
    emit valueChanged ( value );
}

void QQtCustomEffectProgressBar::setNullPosition ( int nullPosition )
{
    if ( this->nullPosition != nullPosition )
    {
        this->nullPosition = nullPosition;
        update();
    }
}

void QQtCustomEffectProgressBar::setLineWidth ( int lineWidth )
{
    if ( this->lineWidth != lineWidth )
    {
        this->lineWidth = lineWidth;
        update();
    }
}

void QQtCustomEffectProgressBar::setShowPercent ( bool showPercent )
{
    if ( this->showPercent != showPercent )
    {
        this->showPercent = showPercent;
        update();
    }
}

void QQtCustomEffectProgressBar::setPercentSuffix ( QString percentSuffix )
{
    if ( this->percentSuffix != percentSuffix )
    {
        this->percentSuffix = percentSuffix;
        update();
    }
}

void QQtCustomEffectProgressBar::setShowFree ( bool showFree )
{
    if ( this->showFree != showFree )
    {
        this->showFree = showFree;
        update();
    }
}

void QQtCustomEffectProgressBar::setShowSmallCircle ( bool showSmallCircle )
{
    if ( this->showSmallCircle != showSmallCircle )
    {
        this->showSmallCircle = showSmallCircle;
        update();
    }
}

void QQtCustomEffectProgressBar::setClockWise ( bool clockWise )
{
    if ( this->clockWise != clockWise )
    {
        this->clockWise = clockWise;
        update();
    }
}

void QQtCustomEffectProgressBar::setUsedColor ( const QColor& usedColor )
{
    if ( this->usedColor != usedColor )
    {
        this->usedColor = usedColor;
        update();
    }
}

void QQtCustomEffectProgressBar::setFreeColor ( const QColor& freeColor )
{
    if ( this->freeColor != freeColor )
    {
        this->freeColor = freeColor;
        update();
    }
}

void QQtCustomEffectProgressBar::setBackgroundColor ( const QColor& backgroundColor )
{
    if ( this->backgroundColor != backgroundColor )
    {
        this->backgroundColor = backgroundColor;
        update();
    }
}

void QQtCustomEffectProgressBar::setBackgroundImage ( const QString& backgroundImage )
{
    if ( this->backgroundImage != backgroundImage )
    {
        this->backgroundImage = backgroundImage;
        update();
    }
}

void QQtCustomEffectProgressBar::setText ( const QString& text )
{
    if ( this->text != text )
    {
        this->text = text;
        update();
    }
}

void QQtCustomEffectProgressBar::setTextColor ( const QColor& textColor )
{
    if ( this->textColor != textColor )
    {
        this->textColor = textColor;
        update();
    }
}

void QQtCustomEffectProgressBar::setTextFont ( QFont font )
{
    if ( this->textFont != font )
    {
        this->textFont = font;
        update();
    }
}

void QQtCustomEffectProgressBar::setPercentTextColor ( const QColor& percentColor )
{
    if ( this->percentColor != percentColor )
    {
        this->percentColor = percentColor;
        update();
    }
}

void QQtCustomEffectProgressBar::setPercentTextFont ( QFont percentFont )
{
    if ( this->percentFont != percentFont )
    {
        this->percentFont = percentFont;
        update();
    }
}

void QQtCustomEffectProgressBar::setCornerRadius ( int cornerRadius )
{
    if ( this->cornerRadius != cornerRadius )
    {
        this->cornerRadius = cornerRadius;
        update();
    }
}

void QQtCustomEffectProgressBar::setTextStyle ( QQtCustomEffectProgressBar::TextStyle textStyle )
{
    if ( this->textStyle != textStyle )
    {
        this->textStyle = textStyle;
        update();
    }
}

void QQtCustomEffectProgressBar::setDesignStyle ( QQtCustomEffectProgressBar::DesignStyle designStyle )
{
    if ( this->designStyle != designStyle )
    {
        this->designStyle = designStyle;
        update();
    }
}

#define TIMER_FIELD 600

void QQtCustomEffectProgressBar::setPercentStyle ( QQtCustomEffectProgressBar::PercentStyle percentStyle )
{
    if ( this->percentStyle != percentStyle )
    {
        this->percentStyle = percentStyle;

        if ( percentStyle == PercentStyle_Wave )
            timer->start ( TIMER_FIELD / waveSpeed );
        else
            timer->stop();

        update();
    }
}

void QQtCustomEffectProgressBar::setBackgroundType ( QQtCustomEffectProgressBar::BackgroundType backgroundType )
{
    if ( this->backgroundType != backgroundType )
    {
        this->backgroundType = backgroundType;
        update();
    }
}

void QQtCustomEffectProgressBar::setWaveDensity ( int value )
{
    if ( value < 1 )
        value = 1;

    if ( this->waveDensity != value )
    {
        this->waveDensity = value;
        update();
    }
}

void QQtCustomEffectProgressBar::setWaveHeight ( int value )
{
    if ( value < 1 )
        value = 1;

    if ( this->waveHeight != value )
    {
        this->waveHeight = value;
        update();
    }
}

void QQtCustomEffectProgressBar::setWaveDirection ( WaveDirection direction )
{
    if ( this->waveDirection != direction )
    {
        this->waveDirection = direction;
        update();
    }
}

void QQtCustomEffectProgressBar::setWaveSpeed ( int speed )
{
    if ( speed < 1 )
        speed = 1;

    if ( this->waveSpeed != speed )
    {
        this->waveSpeed = speed;
        timer->start ( TIMER_FIELD / waveSpeed );
        update();
    }
}


void QQtCustomEffectProgressBar::mouseReleaseEvent ( QMouseEvent* event )
{
    emit click();
    return QWidget::mouseReleaseEvent ( event );
}

void QQtCustomEffectProgressBar::mouseDoubleClickEvent ( QMouseEvent* event )
{
    emit doubleClick();
    return QWidget::mouseDoubleClickEvent ( event );
}
