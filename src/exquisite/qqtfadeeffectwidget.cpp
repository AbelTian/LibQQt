#include "qqtfadeeffectwidget.h"

QQtFadeEffectWidget::QQtFadeEffectWidget(QWidget* parent) : QWidget(parent)
{
    //setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    show_animation_ = new QPropertyAnimation(this, "opacity");
}

void QQtFadeEffectWidget::beginFadeShow(quint32 param_seconds)
{
    show_animation_->setDuration(param_seconds * 1000);
    show_animation_->setStartValue(0);
    show();
    show_animation_->setEndValue(1);
    show_animation_->start();
}

void QQtFadeEffectWidget::setopacity(qreal param_opacity)
{
    opacity_ = param_opacity;
    this->setWindowOpacity(param_opacity);
    update();
    emit opacityChanged(param_opacity);
}

qreal QQtFadeEffectWidget::getopacity()
{
    return opacity_;
}
