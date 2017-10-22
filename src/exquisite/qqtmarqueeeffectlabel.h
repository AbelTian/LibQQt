#ifndef QQTMARQUEEEFFECTLABEL_H
#define QQTMARQUEEEFFECTLABEL_H

/**
 * T.D.R (QQ:2657635903) 2017年10月22日17:24:27
 * MOD
**/

/**
 * 作者: daodaoliang
 * 时间: 2016年8月11日
 * 邮箱: daodaoliang@yeah.net
 */

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QUrl>
#include <QResizeEvent>
#include <QtConcurrent/QtConcurrentRun>
#include <QDesktopServices>
#include "qqt-local.h"

/**
 * @brief The QQtMarqueeEffectLabel class 跑马灯组件
 */
class QQTSHARED_EXPORT QQtMarqueeEffectLabel : public QLabel
{
    Q_OBJECT
    Q_ENUMS(Direction)

public:
    /**
     * @brief The Direction enum 文字的浮动方向
     */
    enum Direction
    {
        // 从右向左
        RightToLeft = 0,
        // 从下到上
        BottomToTop = 1
    };
public:
    QQtMarqueeEffectLabel(QWidget* parent = 0, Qt::WindowFlags f = 0);
    QQtMarqueeEffectLabel(const QString& text, QWidget* parent = 0, Qt::WindowFlags f = 0);
    virtual ~QQtMarqueeEffectLabel();
    int interval() const;
    bool isActive() const;
    Direction direction() const;
    void setAlignment(Qt::Alignment align);

signals:
    void intervalChanged(int mInterval);
    void activeChanged(bool active);
    void directionChanged(Direction direction);

public slots:
    void reset();
    void setActive(bool active);
    void setInterval(int msec);
    void start();
    void stop();
    void setDirection(Direction param_direciton);

protected:
    virtual void enterEvent(QEvent* event);
    virtual void leaveEvent(QEvent* event);
    virtual void resizeEvent(QResizeEvent* event);
    virtual void timerEvent(QTimerEvent* event);
    virtual void paintEvent(QPaintEvent* event);

private:
    int marqueeMargin;
    int timerId;
    int mInterval;
    bool active;
    bool mouseIn;
    Direction mDirection;
};
#endif // QQTMARQUEEEFFECTLABEL_H
