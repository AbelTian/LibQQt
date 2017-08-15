#ifndef QQTANIMATION_H
#define QQTANIMATION_H


#include <QPauseAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QSequentialIterable>
#include <QPropertyAnimation>

class QQTAnimation : public QParallelAnimationGroup
{
    Q_OBJECT
public:
    explicit QQTAnimation(QObject *parent = nullptr);

signals:

public slots:
};

#endif // QQTANIMATION_H
