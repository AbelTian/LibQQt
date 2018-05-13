#include "qqtcustomspeedmeter.h"
#include <QPainter>
#include <qmath.h>

QQtCustomSpeedMeter::QQtCustomSpeedMeter(QWidget* parent): QWidget(parent)
{
    m_value = 0;
    m_minValue = 0;
    m_maxValue = 100;
    m_threshold = 90;
    m_precision = 0;
    m_units = "km/h";
    m_scaleMajor = 10;
    m_scaleMinor = 10;
    m_startAngle = 60;
    m_endAngle = 60;
    m_thresholdFlag = false;
    m_crownColor = Qt::blue;
    m_foreground = Qt::green;
    m_background = Qt::black;
    m_thresholdEnabled = true;
    m_numericIndicatorEnabled = true;

    setMinimumSize(QSize(80, 80));
    resize(100, 100);
}

void QQtCustomSpeedMeter::setValue(int value)
{
    if (value > m_maxValue)
    {
        m_value = m_maxValue;
        Q_EMIT errorSignal(OutOfRange);
    }
    else if (value < m_minValue)
    {
        m_value = m_minValue;
        Q_EMIT errorSignal(OutOfRange);
    }
    else
        m_value = value;

    if (m_thresholdEnabled)
        thresholdManager();

    update();

}

void QQtCustomSpeedMeter::setMinValue(int value)
{
    if (value > m_maxValue)
        Q_EMIT errorSignal(MinValueError);
    else
        m_minValue = value;

    update();
}

void QQtCustomSpeedMeter::setMaxValue(int value)
{
    if (value > m_minValue)
    {
        m_maxValue = value;

        if (m_maxValue < m_threshold)
            m_threshold = m_maxValue - 1;

        update();
    }
    else
        Q_EMIT errorSignal(MaxValueError);
}

void QQtCustomSpeedMeter::setThreshold(double value)
{
    if (value > m_minValue && value < m_maxValue)
    {
        m_threshold = value;
        update();
    }
    else
        Q_EMIT errorSignal(ThresholdError);
}

void QQtCustomSpeedMeter::setPrecision(int precision)
{
    if (precision > 3)
        Q_EMIT errorSignal(PrecisionError);
    else
        m_precision = precision;

    update();
}

void QQtCustomSpeedMeter::setUnits(QString units)
{
    m_units = units;
    update();
}

void QQtCustomSpeedMeter::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  /* 使用反锯齿(如果可用) */
    painter.translate(width() / 2, height() / 2);   /* 坐标变换为窗体中心 */
    int side = qMin(width(), height());
    painter.scale(side / 200.0, side / 200.0);      /* 比例缩放 */
    painter.setPen(Qt::NoPen);

    drawCrown(&painter);                            /* 画边框 */
    drawBackground(&painter);                       /* 画背景 */
    drawScaleNum(&painter);                         /* 画刻度值 */
    drawScale(&painter);                            /* 画刻度线 */
    drawUnits(&painter);                            /* 画单位 */

    if (m_thresholdEnabled)
        drawThresholdLine(&painter);                /* 画匝值线 */

    if (m_numericIndicatorEnabled)
        drawNumericValue(&painter);                 /* 画数字显示 */

    drawIndicator(&painter);                        /* 画指针 */
}

void QQtCustomSpeedMeter::drawCrown(QPainter* painter)
{
    painter->save();
    painter->setPen(QPen(m_crownColor, 3));
    painter->drawEllipse(-95, -95, 190, 190);
    painter->restore();
}

void QQtCustomSpeedMeter::drawBackground(QPainter* painter)
{
    painter->save();
    painter->setBrush(m_background);
    painter->drawEllipse(-92, -92, 184, 184);
    painter->restore();
}

void QQtCustomSpeedMeter::drawScaleNum(QPainter* painter)
{
    painter->save();
    painter->setPen(m_foreground);
    double startRad = (360 - m_startAngle - 90) * (3.14 / 180);
    double deltaRad = (360 - m_startAngle - m_endAngle) * (3.14 / 180) / m_scaleMajor;
    double sina, cosa;
    int x, y;
    QFontMetricsF fm(this->font());
    double w, h, tmpVal;
    QString str;

    for (int i = 0; i <= m_scaleMajor; i++)
    {
        sina = sin(startRad - i * deltaRad);
        cosa = cos(startRad - i * deltaRad);

        tmpVal = 1.0 * i * ((m_maxValue - m_minValue) / m_scaleMajor) + m_minValue;

        str = QString("%1").arg(tmpVal);
        w = fm.size(Qt::TextSingleLine, str).width();
        h = fm.size(Qt::TextSingleLine, str).height();
        x = 82 * cosa - w / 2;
        y = -82 * sina + h / 4;
        painter->drawText(x, y, str);
    }

    painter->restore();
}

void QQtCustomSpeedMeter::drawScale(QPainter* painter)
{
    painter->save();
    painter->rotate(m_startAngle);
    int steps = (m_scaleMajor * m_scaleMinor);
    double angleStep = (360.0 - m_startAngle - m_endAngle) / steps;
    painter->setPen(m_foreground);
    QPen pen = painter->pen();

    for (int i = 0; i <= steps; i++)
    {
        if (i % m_scaleMinor == 0)
        {
            pen.setWidth(1);
            painter->setPen(pen);
            painter->drawLine(0, 62, 0, 72);
        }
        else
        {
            pen.setWidth(0);
            painter->setPen(pen);
            painter->drawLine(0, 67, 0, 72);
        }

        painter->rotate(angleStep);
    }

    painter->restore();
}

void QQtCustomSpeedMeter::drawUnits(QPainter* painter)
{
    painter->save();
    painter->setPen(m_foreground);
    painter->setBrush(m_foreground);
    QString str(m_units);
    QFontMetricsF fm(this->font());
    double w = fm.size(Qt::TextSingleLine, str).width();
    painter->drawText(-w / 2, -30, str);
    painter->restore();
}

void QQtCustomSpeedMeter::drawThresholdLine(QPainter* painter)
{
    double thresholdAngle  = (360.0 - m_startAngle - m_endAngle) / (m_maxValue
                                                                    - m_minValue) * (m_maxValue - m_threshold - 1);
    painter->setPen(QPen(QColor(255, 0, 0, 80), 6));
    painter->drawArc(-70, -70, 140, 140, (m_endAngle - 90) * 16, thresholdAngle * 16);
}

void QQtCustomSpeedMeter::drawNumericValue(QPainter* painter)
{
    QColor color;

    if (!m_thresholdFlag)
        color = QColor(150, 150, 200);
    else
        color = Qt::red;

    painter->setPen(QPen(color, 3));
    painter->drawRect(-30, 30, 60, 14);

    QString str  =  QString("%1").arg(m_value, 0, 'f', m_precision);
    QFontMetricsF fm(font());
    double w = fm.size(Qt::TextSingleLine, str).width();
    painter->setPen(m_foreground);
    painter->drawText(-w / 2, 42, str);
}

void QQtCustomSpeedMeter::drawIndicator(QPainter* painter)
{
    painter->save();
    QPolygon pts;
    pts.setPoints(3, -2, 0, 2, 0, 0, 60); /* (-2,0)/(2,0)/(0,60) */

    painter->rotate(m_startAngle);
    double degRotate = (360.0 - m_startAngle - m_endAngle) / (m_maxValue - m_minValue) * (m_value - m_minValue);

    painter->rotate(degRotate);
    QRadialGradient haloGradient(0, 0, 60, 0, 0);
    haloGradient.setColorAt(0.0, QColor(255, 120, 120));
    haloGradient.setColorAt(1.0, QColor(200, 20, 20));
    painter->setPen(Qt::darkRed);
    painter->setBrush(haloGradient);
    painter->drawConvexPolygon(pts);
    painter->restore();

    // draw indicator hat
    QColor niceBlue(150, 150, 200);
    QConicalGradient coneGradient(0, 0, -90.0);
    coneGradient.setColorAt(0.0, Qt::darkGray);
    coneGradient.setColorAt(0.2, niceBlue);
    coneGradient.setColorAt(0.5, Qt::white);
    coneGradient.setColorAt(1.0, Qt::darkGray);
    painter->setPen(Qt::NoPen);
    painter->setBrush(coneGradient);
    painter->drawEllipse(-5, -5, 10, 10);
}

void QQtCustomSpeedMeter::setScaleMajor(int scale)
{
    m_scaleMajor = scale;
    update();
}

void QQtCustomSpeedMeter::setScaleMinor(int scale)
{
    m_scaleMinor = scale;
    update();
}

void QQtCustomSpeedMeter::setStartAngle(int value)
{
    m_startAngle = value;
    update();
}

void QQtCustomSpeedMeter::setEndAngle(int value)
{
    m_endAngle = value;
    update();
}

void QQtCustomSpeedMeter::setCrownColor(QColor newColor)
{
    m_crownColor = newColor;
    update();
}

void QQtCustomSpeedMeter::setForeground(QColor newForeColor)
{
    m_foreground = newForeColor;
    update();
}

void QQtCustomSpeedMeter::setBackground(QColor newBackColor)
{
    m_background = newBackColor;
    update();
}

void QQtCustomSpeedMeter::thresholdManager()
{
    if (m_value > m_threshold && !m_thresholdFlag)
    {
        m_thresholdFlag = true;
        Q_EMIT thresholdAlarm(m_thresholdFlag);
    }
    else if (m_value < m_threshold && m_thresholdFlag)
    {
        m_thresholdFlag = false;
        Q_EMIT thresholdAlarm(m_thresholdFlag);
    }
}

void QQtCustomSpeedMeter::setThresholdEnabled(bool enable)
{
    m_thresholdEnabled = enable;
    update();
}

void QQtCustomSpeedMeter::setNumericIndicatorEnabled(bool enable)
{
    m_numericIndicatorEnabled = enable;
    update();
}
