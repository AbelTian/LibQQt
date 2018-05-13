#ifndef QQTCUSTOMPROGRESSBAR_H
#define QQTCUSTOMPROGRESSBAR_H

/**
 * T.D.R (QQ:2657635903) mod 2017年10月20日19:10:53
 * add draw wave
 * mod text style
 * T.D.R (QQ:2657635903) mod 2017年10月24日20:22:23
 * T.D.R (QQ:2657635903) mod 2017年10月25日10:55:28
 * add design style
 * T.D.R (QQ:2657635903) mod 2017年11月06日18:24:09
 * add text style
**/

/**
 * 百分比进度条控件 作者:feiyangqingyun(QQ:517216493) 2017-1-6
 * 1:可设置范围值,支持负数值
 * 2:可设置起始点度数
 * 3:可设置顺时针逆时针
 * 4:可设置进度条宽度
 * 5:可设置是否显示百分比
 * 6:可设置是否同时显示剩余进度条
 * 7:可设置是否显示进度前面的小圆
 * 8:可设置当前进度颜色、剩余进度颜色、文字颜色、中间圆颜色
 * 9:提供三种样式风格选择 圆弧风格 水池风格 水波纹风格
 */

#include <QWidget>
#include <qqt-local.h>

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT QQtCustomProgressBar : public QWidget
#else
class QQTSHARED_EXPORT QQtCustomProgressBar : public QWidget
#endif

{
    Q_OBJECT
    Q_ENUMS ( WaveDirection )
    Q_ENUMS ( BackgroundType )
    Q_ENUMS ( PercentStyle )
    Q_ENUMS ( DesignStyle )
    Q_ENUMS ( TextStyle )

    Q_PROPERTY ( int minValue READ getMinValue WRITE setMinValue )
    Q_PROPERTY ( int maxValue READ getMaxValue WRITE setMaxValue )
    Q_PROPERTY ( int value READ getValue WRITE setValue )

    Q_PROPERTY ( int nullPosition READ getNullPosition WRITE setNullPosition )
    Q_PROPERTY ( int lineWidth READ getLineWidth WRITE setLineWidth )
    Q_PROPERTY ( int cornerRadius READ getCornerRaduis WRITE setCornerRadius )

    Q_PROPERTY ( bool showPercent READ getShowPercent WRITE setShowPercent )
    Q_PROPERTY ( bool showFree READ getShowFree WRITE setShowFree )
    Q_PROPERTY ( bool showSmallCircle READ getShowSmallCircle WRITE setShowSmallCircle )
    Q_PROPERTY ( bool clockWise READ getClockWise WRITE setClockWise )

    Q_PROPERTY ( QColor usedColor READ getUsedColor WRITE setUsedColor )
    Q_PROPERTY ( QColor freeColor READ getFreeColor WRITE setFreeColor )
    Q_PROPERTY ( QColor backgroundColor READ getBackgroundColor WRITE setBackgroundColor )
    Q_PROPERTY ( QColor textColor READ getTextColor WRITE setTextColor )
    Q_PROPERTY ( QFont textFont READ getTextFont WRITE setTextFont )
    Q_PROPERTY ( QColor percentColor READ getPercentTextColor WRITE setPercentTextColor )
    Q_PROPERTY ( QFont percentFont READ getPercentTextFont WRITE setPercentTextFont )
    Q_PROPERTY ( QString percentSuffix READ getPercentSuffix WRITE setPercentSuffix )
    Q_PROPERTY ( QString text READ getText WRITE setText )

    Q_PROPERTY ( int waveDensity READ getWaveDensity WRITE setWaveDensity )
    Q_PROPERTY ( int waveHeight READ getWaveHeight WRITE setWaveHeight )
    Q_PROPERTY ( int waveSpeed READ getWaveSpeed WRITE setWaveSpeed )

public:
    enum WaveDirection
    {
        WaveDirection_Left = 0,           /**/
        WaveDirection_Right = 1,           /**/
        WaveDirection_Left_Right = 2,           /**/
        WaveDirection_Right_Left = 3,           /**/
    };

    enum BackgroundType
    {
        BackgroundType_Color = 0,           /*使用颜色*/
        BackgroundType_Image = 1,           /*使用图片*/
    };

    enum DesignStyle
    {
        //circle image is ok
        DesignStyle_Circle = 0, /*圆形*/
        //ellipse image
        DesignStyle_Ellipse = 1, /*椭圆圆形*/
        //(rounded) rect image
        DesignStyle_Rectangle = 2, /*(圆角)矩形*/
        //(rounded) rect image
        DesignStyle_Square = 3, /*正方形*/
    };

    enum PercentStyle
    {
        PercentStyle_Arc = 0,           /*圆弧风格*/
        PercentStyle_Polo = 1,          /*水池风格*/
        PercentStyle_Arc_Polo = 2,      /*圆弧水池风格*/
        PercentStyle_Wave = 3,          /*水波纹风格*/
    };

    enum TextStyle
    {
        TextStyle_None = 0,           /*不显示*/
        TextStyle_Middle_Percent = 1,           /*只在中央显示百分比*/
        TextStyle_Percent = 2,           /*只显示百分比*/
        TextStyle_Text = 3,      /*只显示文字*/
        TextStyle_Percent_Text = 4,          /*显示百分比和文字*/
    };

    explicit QQtCustomProgressBar ( QWidget* parent = 0 );
    virtual ~QQtCustomProgressBar();

public:
    int getMinValue()               const;
    int getMaxValue()               const;
    int getValue()                  const;

    int getNullPosition()           const;
    int getLineWidth()              const;
    int getCornerRaduis() const { return cornerRadius; }

    bool getShowPercent()           const;
    bool getShowFree()              const;
    bool getShowSmallCircle()       const;
    bool getClockWise()             const;

    QColor getUsedColor()           const;
    QColor getFreeColor()           const;
    QColor getBackgroundColor()         const;
    QColor getTextColor()           const;
    QFont getTextFont()           const { return textFont; }
    QColor getPercentTextColor()           const { return percentColor; }
    QFont getPercentTextFont()           const { return percentFont; }
    QString getPercentSuffix()           const;
    QString getText()           const { return text; }

    TextStyle getTextStyle()  const { return textStyle; }
    DesignStyle getDesingStyle()  const { return designStyle; }
    PercentStyle getPercentStyle()  const;
    BackgroundType   getBackgroundType()    const;
    WaveDirection getWaveDirection() const { return waveDirection; }

    int getWaveDensity() const { return waveDensity; }
    int getWaveHeight() const { return waveHeight; }
    int getWaveSpeed() const { return waveSpeed; }

    virtual QSize sizeHint()        const;
    virtual QSize minimumSizeHint() const;

Q_SIGNALS:
    void valueChanged ( int value );
public Q_SLOTS:
    /*设置范围值*/
    void setRange ( int minValue, int maxValue );

    /*设置最大最小值*/
    void setMinValue ( int minValue );
    void setMaxValue ( int maxValue );

    /*设置目标值*/
    void setValue ( int value );

    /*设置最小值位置*/
    void setNullPosition ( int nullPosition );
    /*设置线条宽度*/
    void setLineWidth ( int lineWidth );

    /*设置是否显示百分比*/
    void setShowPercent ( bool showPercent );
    /*设置百分比后缀*/
    /*can't use default parameter*/
    void setPercentSuffix ( QString suffix );
    /*设置是否显示剩余进度*/
    void setShowFree ( bool showFree );
    /*设置是否显示小圆*/
    void setShowSmallCircle ( bool showSmallCircle );
    /*设置进度旋转方向*/
    void setClockWise ( bool clockWise );

    /*设置已使用百分比颜色*/
    void setUsedColor ( const QColor& usedColor );
    /*设置未使用百分比颜色*/
    void setFreeColor ( const QColor& freeColor );
    /*设置圆颜色*/
    void setBackgroundColor ( const QColor& backgroundColor );
    /*设置圆背景图*/
    void setBackgroundImage ( const QString& backgroundImage );
    /*设置文本*/
    void setText ( const QString& text );
    /*设置文本颜色*/
    void setTextColor ( const QColor& textColor );
    /*设置字体*/
    void setTextFont ( QFont font );
    /*设置百分比文本颜色*/
    void setPercentTextColor ( const QColor& percentColor );
    /*设置百分比文字字体*/
    void setPercentTextFont ( QFont percentFont );
    /*设置圆角半径*/
    void setCornerRadius ( int cornerRadius );

    void setTextStyle ( TextStyle textStyle );
    void setDesignStyle ( DesignStyle designStyle );
    /*设置进度样式风格*/
    void setPercentStyle ( PercentStyle percentStyle );
    void setBackgroundType ( BackgroundType backgroundType );
    /*设置运动方向*/
    void setWaveDirection ( WaveDirection direction );

    /*设置水波密度 1-10*/
    void setWaveDensity ( int value );
    /*设置浪高 1-10*/
    void setWaveHeight ( int value );
    /*设置运动速度 1-10*/
    void setWaveSpeed ( int speed );

signals:
    void click();
    void doubleClick();
public slots:

protected:
    void paintEvent ( QPaintEvent* );
    void drawBackground ( QPainter* painter, int radius );
    void drawArc ( QPainter* painter, int radius );
    void drawPolo ( QPainter* painter, int radius );
    void drawWave ( QPainter* painter, int radius );
    void drawText ( QPainter* painter, int radius );
    void drawPercentText ( QPainter* painter, int radius );

private:
    int maxValue;                   /*最小值*/
    int minValue;                   /*最大值*/
    int value;                      /*目标值*/

    int nullPosition;               /*起始角度*/
    int lineWidth;                  /*线条宽度*/

    bool showPercent;               /*是否显示百分比*/
    QString text; /*文字*/
    QString percentSuffix; /*百分比后缀*/
    bool showFree;                  /*是否显示未使用进度*/
    bool showSmallCircle;           /*是否显示小圆*/
    bool clockWise;                 /*顺时针*/

    QColor usedColor;               /*已使用百分比颜色*/
    QColor freeColor;               /*未使用百分比颜色*/
    QColor backgroundColor;             /*圆颜色*/
    QString backgroundImage;            /*圆图片*/
    QColor textColor;               /*文字颜色*/
    QFont  textFont;                /*文字字体*/
    QColor percentColor;               /*百分比文字颜色*/
    QFont  percentFont;                /*百分比文字字体*/

    TextStyle textStyle; /*文字风格*/
    DesignStyle designStyle;        /*面板样式风格*/
    PercentStyle percentStyle;      /*进度样式风格*/
    BackgroundType   backgroundType;        /*圆的样式类型*/
    WaveDirection waveDirection;

    int waveDensity;
    int waveHeight;
    int waveSpeed;

    //0 - 20 default:10
    int cornerRadius;

    QTimer* timer;

    // QWidget interface
protected:
    virtual void mouseReleaseEvent ( QMouseEvent* event ) override;
    virtual void mouseDoubleClickEvent ( QMouseEvent* event ) override;
};

#endif //QQTCUSTOMPROGRESSBAR_H
