#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "qqtrecteffectprogressbar.h"
#include "qpainter.h"
#include "qdebug.h"
#include "qmath.h"
#include "qtimer.h"

QQtRectEffectProgressBar::QQtRectEffectProgressBar(QWidget* parent) : QWidget(parent)
{
    minValue = 0;
    maxValue = 100;
    value = 0;

    nullPosition = 0;
    lineWidth = 10;

    showPercent = true;
    showFree = false;
    showSmallCircle = false;
    clockWise = true;

    usedColor = QColor(100, 184, 255);
    freeColor = QColor(100, 100, 100);
    backgroundColor = QColor(70, 70, 70);
    textColor = QColor(250, 250, 250);
    textFont = font();

    percentStyle = PercentStyle_Polo;
    backgroundType = BackgroundType_Color;

    percentSuffix = "%";

    waveDensity = 2;
    waveHeight = 2;
    waveSpeed = 6;
    waveDirection = WaveDirection_Left;

    timer = new QTimer(this);
    timer->setSingleShot(false);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
}

QQtRectEffectProgressBar::~QQtRectEffectProgressBar()
{
}

void QQtRectEffectProgressBar::paintEvent(QPaintEvent*)
{
    int width = this->width();
    int height = this->height();
    /*显示实长*/
    int side = qMin(width, height);

    /*绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放*/
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    /*平移坐标系*/
    painter.translate(width / 2, height / 2);
    /*更改刻度 设置的是放大的倍数 */
    /*有利于在绘制的时候，统一绘制数据*/
    /*矢量放大，不失真*/
    painter.scale(side / 200.0, side / 200.0);

    /*绘制中心圆*/
    /*
     * 实际显示到屏幕的大小（显示实长）为
     * QPainter绘制区域大小（绘制用数据） * 倍率
     * 200 * ( side / 200.0 )
     */
    drawBackground(&painter, 99);

    /*根据样式绘制进度*/
    if (percentStyle == PercentStyle_Polo)
    {
        drawPolo(&painter, 99 - lineWidth);
    }
    else if (percentStyle == PercentStyle_Wave)
    {
        drawWave(&painter, 99);
    }

    /*绘制当前值*/
    drawText(&painter, 100);
}

void QQtRectEffectProgressBar::drawBackground(QPainter* painter, int radius)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(backgroundColor);

    if (backgroundType == BackgroundType_Color)
    {
        painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    }
    else
    {
        QPixmap pix;
        pix = QPixmap(backgroundImage);

        /*自动等比例平滑缩放居中显示*/
        int targetWidth = pix.width();
        int targetHeight = pix.height();
        pix = pix.scaled(targetWidth, targetHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        painter->drawPixmap(-radius, -radius, radius * 2, radius * 2, pix);
    }

    painter->restore();
}

void QQtRectEffectProgressBar::drawPolo(QPainter* painter, int radius)
{
    /*计算当前值所占百分比对应高度*/
    double poloHeight = (double)radius / (maxValue - minValue) * (value - minValue) ;

    /*大圆路径*/
    QPainterPath bigPath;
    bigPath.addEllipse(-radius, -radius, radius * 2, radius * 2);

    /*底部水池灌水所占的矩形区域路径*/
    QPainterPath smallPath;
    smallPath.addRect(-radius, radius - poloHeight * 2, radius * 2, poloHeight * 2);

    /*将两个路径重合相交部分提取,就是水池注水所占面积*/
    QPainterPath path;
    path = bigPath.intersected(smallPath);

    painter->save();

    painter->setPen(usedColor);
    painter->setBrush(usedColor);
    painter->drawPath(path);

    painter->restore();
}

void QQtRectEffectProgressBar::drawWave(QPainter* painter, int radius)
{
    /*大路径*/
    QPainterPath bigPath;
    bigPath.addEllipse(-radius, -radius, radius * 2, radius * 2);

    /*正弦曲线公式 y = A * sin(ωx + φ) + k*/
    /*A表示振幅,可以理解为水波的高度,值越大高度越高(越浪 ^_^),取值高度的百分比*/
    double A = waveHeight;

    /*w表示周期,可以理解为水波的密度,值越大密度越大(浪越密集 ^_^),取值 密度*M_PI/宽度*/
    double w = waveDensity * M_PI / 100;

    /*计算当前值所占百分比*/
    /*k表示y轴偏移,可以理解为进度,取值高度的进度百分比*/
    double k = radius * 2 * ((double)(value - minValue) / (maxValue - minValue));

    static double offset = 0;
    /*>=1, wave will lost leisurely */
    offset += 0.6;
    if (offset > 180)
    {
        offset = 0;
    }
    int offset1 = offset;
    int offset2 = offset;
    if (WaveDirection_Right == waveDirection)
    {
        offset1 *= -1;
        offset2 *= -1;
    }
    else if (WaveDirection_Left_Right == waveDirection)
    {
        offset2 *= -1;
    }
    else if (WaveDirection_Right_Left == waveDirection)
    {
        offset1 *= -1;
    }


    /*第一条波浪路径集合*/
    QPainterPath waterPath1;
    /*移动到左上角起始点*/
    waterPath1.moveTo(-radius, k);
    for (int x = -radius; x <= radius; x++)
    {
        /*第一条波浪Y轴*/
        double waterY1 = (double)(A * sin(w * x + offset1)) + radius - k;
        /*如果当前值为最小值则Y轴为高度*/
        if (this->value == minValue)
        {
            waterY1 = radius;
        }
        /*如果当前值为最大值则Y轴为0*/
        if (this->value == maxValue)
        {
            waterY1 = -radius;
        }
        waterPath1.lineTo(x, waterY1);
    }

    /*移动到右下角结束点,整体形成一个闭合路径*/
    waterPath1.lineTo(radius, radius);
    waterPath1.lineTo(-radius, radius);
    waterPath1.lineTo(-radius, k);

    /*第二条波浪路径集合*/
    QPainterPath waterPath2;
    waterPath2.moveTo(-radius, k);
    for (int x = -radius; x <= radius; x++)
    {
        /*第二条波浪Y轴*/
        double waterY2 = (double)(A * sin(w * x + offset2 + 180)) + radius - k;
        /*如果当前值为最小值则Y轴为高度*/
        if (this->value == minValue)
        {
            waterY2 = radius;
        }
        /*如果当前值为最大值则Y轴为0*/
        if (this->value == maxValue)
        {
            waterY2 = -radius;
        }
        waterPath2.lineTo(x, waterY2);
    }
    waterPath2.lineTo(radius, radius);
    waterPath2.lineTo(-radius, radius);
    waterPath2.lineTo(-radius, k);

    painter->save();

    /*新路径,用大路径减去波浪区域的路径,形成遮罩效果*/
    /*第一条波浪挖去后的路径*/
    QPainterPath path1;
    path1 = bigPath.intersected(waterPath1);
    QColor waterColor1 = usedColor;
    waterColor1.setAlpha(100);
    painter->setPen(waterColor1);
    painter->setBrush(waterColor1);
    painter->drawPath(path1);

    /*第二条波浪挖去后的路径*/
    QPainterPath path2;
    path2 = bigPath.intersected(waterPath2);
    QColor waterColor2 = usedColor;
    waterColor2.setAlpha(180);
    painter->setPen(waterColor2);
    painter->setBrush(waterColor2);
    painter->drawPath(path2);

    painter->restore();
}

void QQtRectEffectProgressBar::drawText(QPainter* painter, int radius)
{
    QString strValue = QString("%1").arg(value);

    if (showPercent)
    {
        strValue = QString("%1%2").arg((double)value / (maxValue - minValue) * 100)
                   .arg(percentSuffix);
    }

    painter->save();

    painter->setPen(textColor);
    painter->setFont(textFont);

    QFontMetricsF fm(textFont);
    QSizeF textSize = fm.size(Qt::TextSingleLine, strValue);
    //QRectF textRect(-radius, -radius, radius * 2, radius * 2);
    QRectF textRect(-textSize.width() / 2, 40, textSize.width(), textSize.height());
    //painter->drawText(-w / 2, 42, strValue);
    painter->drawText(textRect, Qt::AlignCenter, strValue);

    painter->restore();
}

int QQtRectEffectProgressBar::getMinValue() const
{
    return this->minValue;
}

int QQtRectEffectProgressBar::getMaxValue() const
{
    return this->maxValue;
}

int QQtRectEffectProgressBar::getValue() const
{
    return this->value;
}

int QQtRectEffectProgressBar::getNullPosition() const
{
    return this->nullPosition;
}

int QQtRectEffectProgressBar::getLineWidth() const
{
    return this->lineWidth;
}

bool QQtRectEffectProgressBar::getShowPercent() const
{
    return this->showPercent;
}

bool QQtRectEffectProgressBar::getShowFree() const
{
    return this->showFree;
}

bool QQtRectEffectProgressBar::getShowSmallCircle() const
{
    return this->showSmallCircle;
}

bool QQtRectEffectProgressBar::getClockWise() const
{
    return this->clockWise;
}

QColor QQtRectEffectProgressBar::getUsedColor() const
{
    return this->usedColor;
}

QColor QQtRectEffectProgressBar::getFreeColor() const
{
    return this->freeColor;
}

QColor QQtRectEffectProgressBar::getBackgroundColor() const
{
    return this->backgroundColor;
}

QColor QQtRectEffectProgressBar::getTextColor() const
{
    return this->textColor;
}

QString QQtRectEffectProgressBar::getPercentSuffix() const
{
    return this->percentSuffix;
}

QQtRectEffectProgressBar::PercentStyle QQtRectEffectProgressBar::getPercentStyle() const
{
    return this->percentStyle;
}

QQtRectEffectProgressBar::BackgroundType QQtRectEffectProgressBar::getBackgroundType() const
{
    return this->backgroundType;
}

QSize QQtRectEffectProgressBar::sizeHint() const
{
    return QSize(200, 200);
}

QSize QQtRectEffectProgressBar::minimumSizeHint() const
{
    return QSize(10, 10);
}

void QQtRectEffectProgressBar::setRange(int minValue, int maxValue)
{
    /*如果最小值大于或者等于最大值则不设置*/
    if (minValue >= maxValue)
    {
        return;
    }

    this->minValue = minValue;
    this->maxValue = maxValue;

    /*如果目标值不在范围值内,则重新设置目标值*/
    if (value < minValue || value > maxValue)
    {
        setValue(value);
    }

    update();
}

void QQtRectEffectProgressBar::setMinValue(int minValue)
{
    setRange(minValue, maxValue);
}

void QQtRectEffectProgressBar::setMaxValue(int maxValue)
{
    setRange(minValue, maxValue);
}

void QQtRectEffectProgressBar::setValue(int value)
{
    /*值小于最小值或者值大于最大值或者值和当前值一致则无需处理*/
    if (value < minValue || value > maxValue || value == this->value)
    {
        return;
    }

    this->value = value;
    update();
    emit valueChanged(value);
}

void QQtRectEffectProgressBar::setNullPosition(int nullPosition)
{
    if (this->nullPosition != nullPosition)
    {
        this->nullPosition = nullPosition;
        update();
    }
}

void QQtRectEffectProgressBar::setLineWidth(int lineWidth)
{
    if (this->lineWidth != lineWidth)
    {
        this->lineWidth = lineWidth;
        update();
    }
}

void QQtRectEffectProgressBar::setShowPercent(bool showPercent)
{
    if (this->showPercent != showPercent)
    {
        this->showPercent = showPercent;
        update();
    }
}

void QQtRectEffectProgressBar::setPercentSuffix(QString percentSuffix)
{
    if (this->percentSuffix != percentSuffix)
    {
        this->percentSuffix = percentSuffix;
        update();
    }
}

void QQtRectEffectProgressBar::setShowFree(bool showFree)
{
    if (this->showFree != showFree)
    {
        this->showFree = showFree;
        update();
    }
}

void QQtRectEffectProgressBar::setShowSmallCircle(bool showSmallCircle)
{
    if (this->showSmallCircle != showSmallCircle)
    {
        this->showSmallCircle = showSmallCircle;
        update();
    }
}

void QQtRectEffectProgressBar::setClockWise(bool clockWise)
{
    if (this->clockWise != clockWise)
    {
        this->clockWise = clockWise;
        update();
    }
}

void QQtRectEffectProgressBar::setUsedColor(const QColor& usedColor)
{
    if (this->usedColor != usedColor)
    {
        this->usedColor = usedColor;
        update();
    }
}

void QQtRectEffectProgressBar::setFreeColor(const QColor& freeColor)
{
    if (this->freeColor != freeColor)
    {
        this->freeColor = freeColor;
        update();
    }
}

void QQtRectEffectProgressBar::setBackgroundColor(const QColor& backgroundColor)
{
    if (this->backgroundColor != backgroundColor)
    {
        this->backgroundColor = backgroundColor;
        update();
    }
}

void QQtRectEffectProgressBar::setBackgroundImage(const QString& backgroundImage)
{
    if (this->backgroundImage != backgroundImage)
    {
        this->backgroundImage = backgroundImage;
        update();
    }
}

void QQtRectEffectProgressBar::setTextColor(const QColor& textColor)
{
    if (this->textColor != textColor)
    {
        this->textColor = textColor;
        update();
    }
}

void QQtRectEffectProgressBar::setTextFont(QFont font)
{
    if (this->textFont != font)
    {
        this->textFont = font;
        update();
    }
}

#define TIMER_FIELD 600

void QQtRectEffectProgressBar::setPercentStyle(QQtRectEffectProgressBar::PercentStyle percentStyle)
{
    if (this->percentStyle != percentStyle)
    {
        this->percentStyle = percentStyle;
        if (percentStyle == PercentStyle_Wave)
            timer->start(TIMER_FIELD / waveSpeed);
        else
            timer->stop();
        update();
    }
}

void QQtRectEffectProgressBar::setBackgroundType(QQtRectEffectProgressBar::BackgroundType backgroundType)
{
    if (this->backgroundType != backgroundType)
    {
        this->backgroundType = backgroundType;
        update();
    }
}

void QQtRectEffectProgressBar::setWaveDensity(int value)
{
    if (value < 1)
        value = 1;
    if (this->waveDensity != value)
    {
        this->waveDensity = value;
        update();
    }
}

void QQtRectEffectProgressBar::setWaveHeight(int value)
{
    if (value < 1)
        value = 1;
    if (this->waveHeight != value)
    {
        this->waveHeight = value;
        update();
    }
}

void QQtRectEffectProgressBar::setWaveDirection(WaveDirection direction)
{
    if (this->waveDirection != direction)
    {
        this->waveDirection = direction;
        update();
    }
}

void QQtRectEffectProgressBar::setWaveSpeed(int speed)
{
    if (speed < 1)
        speed = 1;
    if (this->waveSpeed != speed)
    {
        this->waveSpeed = speed;
        timer->start(TIMER_FIELD / waveSpeed);
        update();
    }
}
