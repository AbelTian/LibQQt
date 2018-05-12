#ifndef QQTFADEWIDGET_H
#define QQTFADEWIDGET_H

/**
 * T.D.R (QQ:2657635903) mod 2017年10月22日17:36:59
**/

/**
 * 作者: daodaoliang
 * 时间: 2016年8月10日
 * 邮箱: daodaoliang@yeah.net
 */

#include <QObject>
#include <QWidget>
#include <QWidget>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include "qqt-local.h"

/**
 * @brief The QQtFadeWidget class 淡入淡出效果的widget
 */
class QQTSHARED_EXPORT QQtFadeWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY ( qreal opacity READ getopacity WRITE setopacity NOTIFY opacityChanged )

public:
    /**
     * @brief QQtFadeWidget 构造函数
     * @param parent
     */
    explicit QQtFadeWidget ( QWidget* parent = 0 );

signals:
    /**
     * @brief opacityChanged 透明度改变的信号
     * @param param_opacity 当前透明度
     */
    void opacityChanged ( qreal param_opacity );

public:
    /**
     * @brief beginFadeShow 开启淡入淡出的效果
     * @param param_seconds param_seconds秒内完成效果动画
     */
    void beginFadeShow ( quint32 param_seconds );

    /**
     * @brief setopacity 设置透明度
     * @param param_opacity 透明度
     */
    void setopacity ( qreal param_opacity );

    /**
     * @brief getopacity 获取当前透明度
     * @return
     */
    qreal getopacity();

private:
    /**
     * @brief opacity_ 当前透明度
     */
    qreal opacity_;

    /**
     * @brief show_animation_ 显示动画
     */
    QPropertyAnimation* show_animation_;
};

#endif // QQTFADEWIDGET_H
