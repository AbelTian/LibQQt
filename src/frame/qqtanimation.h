#ifndef QQTANIMATION_H
#define QQTANIMATION_H


#include <QPauseAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QPropertyAnimation>
#include "qqtcore.h"
#include <qqt-local.h>

/**
 * @brief The QQtAnimation class
 * Qt提供了并行、串行动画组
 * Qt提供了属性动画。
 * LibQQt建议使用并行动画组。
 */
class QQTSHARED_EXPORT QQtAnimation : public QParallelAnimationGroup
{
    Q_OBJECT
public:
    explicit QQtAnimation ( QObject* parent = nullptr );

signals:

public slots:
};

#endif // QQTANIMATION_H
