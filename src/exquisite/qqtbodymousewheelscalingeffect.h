#ifndef QQTBODYMOUSEWHEELSCALINGEFFECT_H
#define QQTBODYMOUSEWHEELSCALINGEFFECT_H

#include <QObject>

#include <qqt-local.h>

class QQTSHARED_EXPORT QQtBodyMouseWheelScalingEffect : public QObject
{
    Q_OBJECT
public:
    QQtBodyMouseWheelScalingEffect ( QObject* parent = 0 );
    virtual ~QQtBodyMouseWheelScalingEffect();

    // QObject interface
public:
    virtual bool eventFilter ( QObject* watched, QEvent* event ) override;
};

#endif //QQTBODYMOUSEWHEELSCALINGEFFECT_H
