#ifndef QQTWIDGETCLICKHELPER_H
#define QQTWIDGETCLICKHELPER_H

#include <qqt-local.h>
#include <qqtcore.h>

#include <QTimer>
#include <QMouseEvent>

/**
 * QQtWidgetClickHelper
 * 这个Helper是给Widget响应按钮事件用的
 * 主要用于为QQtWidget系列添加按钮信号识别帮助
 *
 * 原理
 * release开始检测.
 * 发现doubleClick只发送doubleClick.包括Qt的和内部的检测都管用.
 * 发现longClick只发送longClick.
 * 发现click只发送click.
 * 以最新click为准
 *
 * DoubleClick间隔默认掌握在Qt手中,也有间隔检测.
 * 延迟比较常规
 */
class QQTSHARED_EXPORT QQtWidgetClickHelper : public QObject
{
    Q_OBJECT

public:
    typedef enum
    {
        QQtNullClick = 0,

        QQtClick,
        QQtDoubleClick,
        QQtLongClick,

        QQtMaxClick
    } QQtClickType;
    Q_ENUMS ( QQtClickType )

public:
    explicit QQtWidgetClickHelper ( QObject* parent = 0 );
    virtual ~QQtWidgetClickHelper();

    //调用于userWidget相对应的Event里
    //允许重写
public:
    virtual void mousePressEvent ( QMouseEvent* event, QWidget* userWidget = 0 );
    virtual void mouseReleaseEvent ( QMouseEvent* event, QWidget* userWidget = 0 );
    virtual void mouseDoubleClickEvent ( QMouseEvent* event, QWidget* userWidget = 0 );

signals:
    void click();
    void doubleClick();
    void longClick();

signals:
    void clickWithPoint ( QPoint point );
    void doubleClickWithPoint ( QPoint point );
    void longClickWithPoint ( QPoint point );

    //optional
public:
    //设置双击检测时延 default:200ms
    //不会影响系统默认时延
    void setDoubleClickInterval ( int millSecond = 300 );

    //设置longClick超时 default:1200ms
    void setLongClickInterval ( int millSecond = 1200 );

    /**
     * 以下用于内部
     */
public slots:
    void slotClickTimeout();
    void slotLongClickTimeout();
    void slotDoubleClickTimeout();

private:
    QQtClickType mClickType;

    //clickTimer
    QTimer* m_click_timer;
    //longClickTimer
    QTimer* m_long_click_timer;
    //doubleClickTimer
    QTimer* m_double_click_timer;

    //用于记录按钮的位置
    QPoint mPoint;

    //双击200ms. 这个比较符合双击舒适度.Qt内部的Timer慢一些,可能是计算了比较完整的时间.
    //在这个范围内的都 才 是双击
    int mDoubleClickInterval;
    int mLongClickInterval;

    //click 检测使用
    QTime startClickTime;
};

#endif // QQTWIDGETCLICKHELPER_H
