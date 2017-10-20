#ifndef __QQTCUSTOMSPEEDMDTER_H__
#define __QQTCUSTOMSPEEDMDTER_H__

/**
 * T.D.R (QQ:2657635903) mod 2017年10月20日19:10:53
**/

#include <QWidget>
#include <qqt-local.h>

class QQTSHARED_EXPORT QQtCustomSpeedMeter: public QWidget
{
    Q_OBJECT
    Q_ENUMS(errorCode)
    Q_PROPERTY(double value READ value WRITE setValue)
    Q_PROPERTY(int minValue READ minValue WRITE setMinValue)
    Q_PROPERTY(int maxValue READ maxValue WRITE setMaxValue)
    Q_PROPERTY(double threshold READ threshold WRITE setThreshold)
    Q_PROPERTY(int precision READ precision WRITE setPrecision)
    Q_PROPERTY(QString units READ units WRITE setUnits)
    Q_PROPERTY(int scaleMajor READ scaleMajor WRITE setScaleMajor)
    Q_PROPERTY(int scaleMinor READ scaleMinor WRITE setScaleMinor)
    Q_PROPERTY(int startAngle READ startAngle WRITE setStartAngle)
    Q_PROPERTY(int endAngle READ endAngle WRITE setEndAngle)
    Q_PROPERTY(QColor crownColor READ crownColor WRITE setCrownColor)
    Q_PROPERTY(QColor foreground READ foreground WRITE setForeground)
    Q_PROPERTY(QColor background READ background WRITE setBackground)
    Q_PROPERTY(bool thresholdEnabled READ isThresholdEnabled WRITE setThresholdEnabled)
    Q_PROPERTY(bool numericIndicatorEnabled READ isNumericIndicatorEnabled WRITE setNumericIndicatorEnabled)
	
public: 
    enum ErrorCode {MaxValueError=1,MinValueError,ThresholdError,TargetError,PrecisionError,ColorError,UnitsEmpty,OutOfRange};

    explicit QQtCustomSpeedMeter(QWidget *parent = 0);
    double value() const {return m_value;}
    int minValue() const {return m_minValue;}
    int maxValue() const {return m_maxValue;}
    double threshold() const {return m_threshold;}
    int precision() const {return m_precision;}
	QString units()const {return m_units;}
	int scaleMajor() const {return m_scaleMajor;}
	int scaleMinor() const {return m_scaleMinor;}
	int startAngle() const {return m_startAngle;}
    int endAngle() const { return m_endAngle;}
	QColor crownColor() const {return m_crownColor;}
    QColor foreground() const {return m_foreground;}
    QColor background() const {return m_background;}
    bool isThresholdEnabled() const {return m_thresholdEnabled;}
	bool isNumericIndicatorEnabled() const {return m_numericIndicatorEnabled;}
		       	            
Q_SIGNALS:
    void errorSignal(int);
    void thresholdAlarm(bool);

public Q_SLOTS:
    void setValue(int);
	void setMinValue(int);
	void setMaxValue(int);	
	void setThreshold(double);
    void setPrecision(int);	
	void setUnits(QString);	
	void setScaleMajor(int);
	void setScaleMinor(int);
	void setStartAngle(int);
	void setEndAngle(int);
	void setCrownColor(QColor);
	void setForeground(QColor);
	void setBackground(QColor);
    void setThresholdEnabled(bool);
    void setNumericIndicatorEnabled(bool);

protected:
    void thresholdManager();
    void paintEvent(QPaintEvent *);
            
    void drawCrown(QPainter *painter);
    void drawBackground(QPainter *painter);
    void drawScale(QPainter *painter);
    void drawScaleNum(QPainter *painter);
    void drawUnits(QPainter *painter);
    void drawIndicator(QPainter *painter);
    void drawThresholdLine(QPainter *painter);
    void drawNumericValue(QPainter *painter);
  
private:
	double m_value;
    int m_maxValue, m_minValue;
    int m_precision;
	QString m_units;
	int m_scaleMajor;
	int m_scaleMinor;
	int m_startAngle,m_endAngle;
	double m_threshold;
	bool m_thresholdFlag;
	
	QColor m_crownColor;
	QColor m_foreground;
	QColor m_background;
	
	bool m_thresholdEnabled;
	bool m_numericIndicatorEnabled;
};

#endif
