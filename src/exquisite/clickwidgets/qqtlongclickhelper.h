#ifndef QQTLONGCLICKHELPER_H
#define QQTLONGCLICKHELPER_H

#include <qqtclickhelper.h>

#include <qqt-local.h>
#include <qqtcore.h>

/**
 * QQtLongClickHelper
 * 这个Helper是给Widget响应按钮事件用的
 * 主要用于为QQtWidget系列添加按钮信号识别帮助
 *
 * 支持
 * click
 * longClick
 * 不支持DoubleClick
 *
 * 可以统计按键次数
 */
class QQTSHARED_EXPORT QQtLongClickHelper : public QQtClickHelper
{
    Q_OBJECT

public:
    explicit QQtLongClickHelper ( QObject* parent = 0 );
    virtual ~QQtLongClickHelper();

    //发给业务层
    //发回界面层
    //这些信号不区分Widget,谁发过来都发出去,不论Widget
signals:
    void longClick();

signals:
    void longClickWithPoint ( QPoint point );

signals:
    void longClickWithPointF ( QPointF point );

#if 0
    //发给业务层
    //发回界面层
    //这里的信号都带着Widget指针,可以区分Widget
signals:
    void longClick ( QWidget* userWidget );
    void longClickWithPoint ( QPoint point, QWidget* userWidget );
    void longClickWithPointF ( QPointF point, QWidget* userWidget );
#endif

    //调用于userWidget相对应的Event里
    //允许重写
public:
    virtual void mousePressEvent ( QMouseEvent* event, QWidget* userWidget = 0 ) override;
    virtual void mouseReleaseEvent ( QMouseEvent* event, QWidget* userWidget = 0 ) override;
    virtual void mouseDoubleClickEvent ( QMouseEvent* event, QWidget* userWidget = 0 ) override;

    //optional
public:
    //设置longClick超时 default:1200ms
    void setLongClickInterval ( int millSecond = longClickInterval );
    int getLongClickInterval() const;

    inline const quint32 longClickNum() const { return nLongClickNum; }
    inline const quint32 longClickNumWithCancel() const { return nLongClickNumWithCancel; }


    /**
     * 以下用于内部
     */
protected:
    //这个语法比较难,只有整型有特权.
    static const int longClickInterval = 1200;

    int mLongClickInterval;

    //click 检测使用
    QTime now_press;//press relase
    QTime now_release;//release

    //click num
    virtual void checkClickNum ( QQtClickType type ) override;
    virtual void checkClickNumWithCancel() override;

    quint32 nLongClickNum;
    quint32 nLongClickNumWithCancel;
};

#endif // QQTLONGCLICKHELPER_H
