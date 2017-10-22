#ifndef QQTFLIPEFFECTSTACKEDWIDGET_H
#define QQTFLIPEFFECTSTACKEDWIDGET_H
/**
 * T.D.R (QQ:2657635903) 2017年10月22日15:31:26
 * MOD
**/

/**
 * 作者: daodaoliang
 * 时间: 2016年8月10日
 * 邮箱: daodaoliang@yeah.net
 */

#include <QObject>
#include <QVariant>
#include <QWidget>
#include <QLabel>
#include <QPropertyAnimation>
#include <QStackedWidget>
#include <QPainter>
#include <QTransform>
#include <QParallelAnimationGroup>
#include "qqt-local.h"

/**
 * @brief The QQtFlipEffectStackedWidget class 反转的stacked
 */
class QQTSHARED_EXPORT QQtFlipEffectStackedWidget : public QStackedWidget
{
    Q_OBJECT
    Q_PROPERTY(float rotateVal READ rotateVal WRITE setRotateVal)
public:
    /**
     * @brief NBaseRotatingStackedWidget 构造函数
     * @param parent
     */
    explicit QQtFlipEffectStackedWidget(QWidget* parent = 0);

    /**
     * @brief paintEvent 绘制事件
     */
    void paintEvent(QPaintEvent* event);

public slots:
    /**
     * @brief nextPage 下一页
     */
    void nextPage();

public:

    /**
     * @brief rotate index 跳转到索引页
     */
    void rotate(int index);

    /**
     * @brief rotateVal 旋转值
     * @return
     */
    float rotateVal();

    /**
     * @brief setRotateVal 设置旋转值
     * @param fl 值
     */
    void setRotateVal(float fl);

private slots:
    /**
     * @brief valChanged 旋转值改变了
     */
    void valChanged(QVariant);

    /**
     * @brief animDone 动画结束
     */
    void animDone();

private:
    /**
     * @brief iRotateVal 旋转值
     */
    float iRotateVal;

    /**
     * @brief isAnimating 旋转动画中
     */
    bool isAnimating;

    /**
     * @brief nextIndex 下一个索引页
     */
    int nextIndex;
};

#endif // QQTFLIPEFFECTSTACKEDWIDGET_H
