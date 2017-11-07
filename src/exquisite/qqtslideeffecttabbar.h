#ifndef QQTSLIDEEFFECTTABBAR_H
#define QQTSLIDEEFFECTTABBAR_H

/*
 * DrAbel set (QQ:2657635903) 2017年11月05日18:00:16
 * 功能完整，但是绘图的实现还太简单。
 */

#include <QTabBar>
#include <QPainter>
#include <QTimer>
#include <qqtcore.h>

class QQtSlideEffectTabBar : public QTabBar
{
    Q_OBJECT
public:
    explicit QQtSlideEffectTabBar(QWidget* parent = nullptr);
    virtual ~QQtSlideEffectTabBar() {}
    /**
     * @brief setSlideSpeed
     * 滑动速度 1-100 default:10
     * @return
     */
    int getSlideSpeed() const { return slideSpeed; }
    void setSlideSpeed(int slideSpeed);
    /**
     * @brief getCornerRadius
     * Tab的圆角 1-70? default:6
     * @return
     */
    int getCornerRadius() const { return cornerRadius; }
    void setCornerRadius(int cornerRadius);
signals:

public slots:

protected:
    virtual void drawBackground(QPainter* painter);
    virtual void drawTabBar(QPainter* painter);
    virtual void drawTabBarIcon(QPainter* painter);
    virtual void drawTabBarText(QPainter* painter);

    bool verticalTabs();

private slots:
    void updateTabBarRect();
private:
    int slideSpeed;
    int cornerRadius;

    QRect m_barRect;
    QRect m_targetRect;
    QTimer* timer;

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent* event) override;

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent* event) override;

    // QWidget interface
protected:
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
};

#endif // QQTSLIDEEFFECTTABBAR_H
