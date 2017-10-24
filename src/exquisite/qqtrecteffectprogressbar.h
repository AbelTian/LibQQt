#ifndef QQTRECTEFFECTPROGRESSBAR_H
#define QQTRECTEFFECTPROGRESSBAR_H

/**
 * T.D.R (QQ:2657635903) 2017年10月24日20:22:23
**/

#include <QObject>
#include <qqt-local.h>

class QQTSHARED_EXPORT QQtRectEffectProgressBar : public QWidget
{
    Q_OBJECT

    Q_ENUMS(WaveDirection)
    Q_ENUMS(BackgroundType)
    Q_ENUMS(PercentStyle)
    Q_PROPERTY(int minValue READ getMinValue WRITE setMinValue)
    Q_PROPERTY(int maxValue READ getMaxValue WRITE setMaxValue)
    Q_PROPERTY(int value READ getValue WRITE setValue)

    Q_PROPERTY(int nullPosition READ getNullPosition WRITE setNullPosition)
    Q_PROPERTY(int lineWidth READ getLineWidth WRITE setLineWidth)

    Q_PROPERTY(bool showPercent READ getShowPercent WRITE setShowPercent)
    Q_PROPERTY(bool showFree READ getShowFree WRITE setShowFree)
    Q_PROPERTY(bool showSmallCircle READ getShowSmallCircle WRITE setShowSmallCircle)
    Q_PROPERTY(bool clockWise READ getClockWise WRITE setClockWise)

    Q_PROPERTY(QColor usedColor READ getUsedColor WRITE setUsedColor)
    Q_PROPERTY(QColor freeColor READ getFreeColor WRITE setFreeColor)
    Q_PROPERTY(QColor circleColor READ getBackgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor)
    Q_PROPERTY(QString percentSuffix READ getPercentSuffix WRITE setPercentSuffix)

    Q_PROPERTY(int waveDensity READ getWaveDensity WRITE setWaveDensity)
    Q_PROPERTY(int waveHeight READ getWaveHeight WRITE setWaveHeight)
    Q_PROPERTY(int waveSpeed READ getWaveSpeed WRITE setWaveSpeed)

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

    enum PercentStyle
    {
        PercentStyle_Polo = 1,          /*水池风格*/
        PercentStyle_Wave = 3,          /*水波纹风格*/
    };

    explicit QQtRectEffectProgressBar(QObject* parent = nullptr);
    virtual ~QQtRectEffectProgressBar();

public:
    int getMinValue()               const;
    int getMaxValue()               const;
    int getValue()                  const;

    int getNullPosition()           const;
    int getLineWidth()              const;

    bool getShowPercent()           const;
    bool getShowFree()              const;
    bool getShowSmallCircle()       const;
    bool getClockWise()             const;

    QColor getUsedColor()           const;
    QColor getFreeColor()           const;
    QColor getBackgroundColor()         const;
    QColor getTextColor()           const;
    QString getPercentSuffix()           const;

    PercentStyle getPercentStyle()  const;
    BackgroundType   getBackgroundType()    const;
    WaveDirection getWaveDirection()const { return waveDirection; }

    int getWaveDensity()const { return waveDensity; }
    int getWaveHeight()const { return waveHeight; }
    int getWaveSpeed()const { return waveSpeed; }

    virtual QSize sizeHint()        const;
    virtual QSize minimumSizeHint() const;

Q_SIGNALS:
    void valueChanged(int value);

public Q_SLOTS:
    /*设置范围值*/
    void setRange(int minValue, int maxValue);

    /*设置最大最小值*/
    void setMinValue(int minValue);
    void setMaxValue(int maxValue);

    /*设置目标值*/
    void setValue(int value);

    /*设置最小值位置*/
    void setNullPosition(int nullPosition);
    /*设置线条宽度*/
    void setLineWidth(int lineWidth);

    /*设置是否显示百分比*/
    void setShowPercent(bool showPercent);
    /*设置百分比后缀*/
    /*can't use default parameter*/
    void setPercentSuffix(QString suffix);
    /*设置是否显示剩余进度*/
    void setShowFree(bool showFree);
    /*设置是否显示小圆*/
    void setShowSmallCircle(bool showSmallCircle);
    /*设置进度旋转方向*/
    void setClockWise(bool clockWise);

    /*设置已使用百分比颜色*/
    void setUsedColor(const QColor& usedColor);
    /*设置未使用百分比颜色*/
    void setFreeColor(const QColor& freeColor);
    /*设置圆颜色*/
    void setBackgroundColor(const QColor& backgroundColor);
    /*设置圆背景图*/
    void setBackgroundImage(const QString& backgroundImage);
    /*设置文本颜色*/
    void setTextColor(const QColor& textColor);
    /*设置字体*/
    void setTextFont(QFont font);

    /*设置进度样式风格*/
    void setPercentStyle(PercentStyle percentStyle);
    void setBackgroundType(BackgroundType backgroundType);
    /*设置运动方向*/
    void setWaveDirection(WaveDirection direction);

    /*设置水波密度 1-10*/
    void setWaveDensity(int value);
    /*设置浪高 1-10*/
    void setWaveHeight(int value);
    /*设置运动速度 1-10*/
    void setWaveSpeed(int speed);
signals:

public slots:

protected:
    void paintEvent(QPaintEvent*);
    void drawBackground(QPainter* painter, int radius);
    void drawPolo(QPainter* painter, int radius);
    void drawWave(QPainter* painter, int radius);
    void drawText(QPainter* painter, int radius);

private:
    int maxValue;                   /*最小值*/
    int minValue;                   /*最大值*/
    int value;                      /*目标值*/

    int nullPosition;               /*起始角度*/
    int lineWidth;                  /*线条宽度*/

    bool showPercent;               /*是否显示百分比*/
    QString percentSuffix; /*百分比后缀*/
    bool showFree;                  /*是否显示未使用进度*/
    bool showSmallCircle;           /*是否显示小圆*/
    bool clockWise;                 /*顺时针*/

    QColor usedColor;               /*已使用百分比颜色*/
    QColor freeColor;               /*未使用百分比颜色*/
    QColor circleColor;             /*圆颜色*/
    QString circleImage;            /*圆图片*/
    QColor textColor;               /*文字颜色*/
    QFont  textFont;                /*文字字体*/

    PercentStyle percentStyle;      /*进度样式风格*/
    BackgroundType   backgroundType;        /*圆的样式类型*/
    WaveDirection waveDirection;

    int waveDensity;
    int waveHeight;
    int waveSpeed;

    QTimer* timer;
};

#endif // QQTRECTEFFECTPROGRESSBAR_H
