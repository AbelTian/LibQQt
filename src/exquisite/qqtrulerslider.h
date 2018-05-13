#ifndef QQTRULERSLIDER_H
#define QQTRULERSLIDER_H

#include <QSlider>

/**
 * T.D.R (QQ:2657635903) MOD 2017年10月21日13:24:03
**/

/**
 * 作者:feiyangqingyun(QQ:517216493) 2016-10-28
 * 本控件来源于网络(原作者:kimtaikee(http://www.qtcn.org/bbs/read-htm-tid-33719-ds-1.html#tpc))
 * 1:增加设置精确度(小数点后几位)和间距
 * 2:增加设置背景色/滑块颜色/提示信息背景前景色
 * 3:增加鼠标滚轮支持
 * 4:增加设置长线条步长及短线条步长
 * 5:移除定时器实现显示和隐藏提示值
 * 6:增加设置范围值
 * 7:暂不支持负数刻度值
 */

class QQtRulerSlider : public QSlider
{
    Q_OBJECT
public:
    explicit QQtRulerSlider ( QWidget* parent = 0 );

protected:
    void resizeEvent ( QResizeEvent* );
    void wheelEvent ( QWheelEvent* );
    void mousePressEvent ( QMouseEvent* );
    void mouseReleaseEvent ( QMouseEvent* );
    void mouseMoveEvent ( QMouseEvent* );
    void paintEvent ( QPaintEvent* );
    void drawBg ( QPainter* painter );
    void drawRule ( QPainter* painter );
    void drawSlider ( QPainter* painter );
    void drawTip ( QPainter* painter );

private:
    double value; /*目标值*/
    double maxValue; /*最小值*/
    double minValue; /*最大值*/
    int precision; /*精确度,小数点后几位*/
    int longStep; /*长线条等分步长*/
    int shortStep; /*短线条等分步长*/
    int space; /*间距*/

    QColor bgColorStart; /*背景渐变开始颜色*/
    QColor bgColorEnd; /*背景渐变结束颜色*/
    QColor lineColor; /*线条颜色*/

    QColor sliderColorTop; /*滑块上部颜色*/
    QColor sliderColorBottom; /*滑块下部颜色*/

    QColor tipBgColor; /*当前值背景色*/
    QColor tipTextColor; /*当前值文字颜色*/

    bool pressed; /*是否鼠标按下*/
    double currentValue; /*当前值*/

    double longLineHeight; /*长刻度高度*/
    double shortLineHeight; /*短刻度高度*/
    double sliderTopHeight; /*滑块上部高度*/
    double sliderBottomHeight; /*滑块底部高度*/

    QPointF sliderLastPot; /*滑块最后的坐标*/
    QPointF sliderTopPot; /*滑块顶部坐标*/
    QPointF sliderLeftPot; /*滑块左边坐标*/
    QPointF sliderRightPot; /*滑块右边坐标*/

    QRectF sliderRect; /*滑块矩形区域*/
    QRectF tipRect; /*提示信息矩形区域*/
    QPointF lineLeftPot; /*主线左边坐标*/
    QPointF lineRightPot; /*主线右边坐标*/

private slots:
    void resetVariables();

public:
    double getValue() const {
        return value;
    }
    double getMinValue() const {
        return minValue;
    }
    double getMaxValue() const {
        return maxValue;
    }

    int getPrecision() const {
        return precision;
    }
    int getLongStep() const {
        return longStep;
    }
    int getShortStep() const {
        return shortStep;
    }
    int getSpace() const {
        return space;
    }

    QColor getBgColorStart() const {
        return bgColorStart;
    }
    QColor getBgColorEnd() const {
        return bgColorEnd;
    }
    QColor getLineColor() const {
        return lineColor;
    }

    QColor getSliderColorTop() const {
        return sliderColorTop;
    }
    QColor getSliderColorBottom() const {
        return sliderColorBottom;
    }

    QColor getTipBgColor() const {
        return tipBgColor;
    }
    QColor getTipTextColor() const {
        return tipTextColor;
    }
public slots:
    /*设置最大最小值-范围值*/
    void setRange ( double minValue, double maxValue );
    void setRange ( int minValue, int maxValue );

    /*设置目标值*/
    void setValue ( double value );
    void setValue ( int value );

    /*设置精确度*/
    void setPrecision ( int precision );
    /*设置线条等分步长*/
    void setStep ( int longStep, int shortStep );
    /*设置间距*/
    void setSpace ( int space );

    /*设置背景颜色*/
    void setBgColor ( QColor bgColorStart, QColor bgColorEnd );
    /*设置线条颜色*/
    void setLineColor ( QColor lineColor );
    /*设置滑块颜色*/
    void setSliderColor ( QColor sliderColorTop, QColor sliderColorBottom );
    /*设置提示信息背景*/
    void setTipBgColor ( QColor tipBgColor, QColor tipTextColor );

signals:
    void valueChanged ( double value );
};

#endif // QQTRULERSLIDER_H
