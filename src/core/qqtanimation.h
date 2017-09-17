#ifndef QQTANIMATION_H
#define QQTANIMATION_H


#include <QPauseAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QPropertyAnimation>
#include "qqtcore.h"
#include <qqt-local.h>

class QQTSHARED_EXPORT QQTAnimation : public QParallelAnimationGroup
{
    Q_OBJECT
public:
    explicit QQTAnimation(QObject *parent = nullptr);

signals:

public slots:
};

#endif // QQTANIMATION_H
