﻿#ifndef QQTRIPPLEPUSHBUTTON_H
#define QQTRIPPLEPUSHBUTTON_H

/*
 * T.D.R (QQ:2657635903) mod 2017年10月22日16:12:22
 */

/**
 * 作者: daodaoliang
 * 时间: 2016年9月29日
 * 邮箱: daodaoliang@yeah.net
 */

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QColor>
#include "qqt-local.h"

/**
 * @brief The QQtRipplePushButton class 点击波按钮
 */
class QQTSHARED_EXPORT QQtRipplePushButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY ( qreal waveRadius READ getWaveRadius WRITE setWaveRadius NOTIFY waveRadiusChanged )

public:
    /**
     * @brief NBaseClickWave 构造函数
     * @param parent
     */
    explicit QQtRipplePushButton ( QWidget* parent = 0 );

    /**
     * @brief getWaveRadius 获取圆周半径
     * @return
     */
    qreal getWaveRadius() const;

    /**
     * @brief setWaveRadius 设置圆周半径
     * @param value
     */
    void setWaveRadius ( const qreal& value );

    /**
     * @brief getClickColor 获取点击波颜色
     * @return
     */
    QColor getClickColor() const;

    /**
     * @brief setClickColor 设置点击波颜色
     * @param value
     */
    void setClickColor ( const QColor& value );

signals:
    /**
     * @brief waveRadiusChanged 点击波改变
     */
    void waveRadiusChanged ( qreal waveRadius );

protected:
    /**
     * @brief paintEvent 绘制事件
     * @param event
     */
    void paintEvent ( QPaintEvent* event );

    /**
     * @brief mousePressEvent 鼠标按压事件
     * @param event
     */
    void mousePressEvent ( QMouseEvent* event );

private:
    /**
     * @brief pointX 圆心x坐标
     */
    qreal pointX;

    /**
     * @brief pointY 圆心y坐标
     */
    qreal pointY;

    /**
     * @brief waveRadius 圆心半径
     */
    qreal waveRadius;

    /**
     * @brief clickColor 点击波的颜色
     */
    QColor clickColor;
};

#endif // QQTRIPPLEPUSHBUTTON_H
