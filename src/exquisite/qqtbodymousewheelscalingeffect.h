#ifndef QQTBODYMOUSEWHEELSCALINGEFFECT_H
#define QQTBODYMOUSEWHEELSCALINGEFFECT_H

#include <QObject>
#include <QWheelEvent>
#include <QWidget>
#include <qqt-local.h>

/**
 * @brief The QQtBodyMouseWheelScalingEffect class
 * 用鼠标滚轮放大缩小控件
 */
class QQTSHARED_EXPORT QQtBodyMouseWheelScalingEffect : public QObject
{
    Q_OBJECT
public:
    QQtBodyMouseWheelScalingEffect ( QObject* parent = 0 );
    virtual ~QQtBodyMouseWheelScalingEffect();

protected:
    virtual void wheelEvent ( QWheelEvent* event, QWidget* target = 0 );

    // QObject interface
public:
    virtual bool eventFilter ( QObject* watched, QEvent* event ) override;
};

#endif //QQTBODYMOUSEWHEELSCALINGEFFECT_H
