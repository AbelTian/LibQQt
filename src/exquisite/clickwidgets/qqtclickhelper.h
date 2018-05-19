#ifndef QQTCLICKHELPER_H
#define QQTCLICKHELPER_H

#include <qqt-local.h>
#include <qqtcore.h>

#if 0
#define p2debug() p2line()
#else
#define p2debug() QNoDebug()
#endif

/**
 * QQtClickHelper
 * 这个Helper是给Widget响应按钮事件用的
 * 主要用于为QQtWidget系列添加按钮信号识别帮助
 *
 * 支持
 * click
 * longClick
 * 不支持DoubleClick, doubleClick会导致click延时
 *
 * 可以统计按键次数
 */
class QQTSHARED_EXPORT QQtClickHelper : public QObject
{
    Q_OBJECT

public:
    explicit QQtClickHelper ( QObject* parent = 0 );
    virtual ~QQtClickHelper();

    //发给业务层
    //发回界面层
    //这些信号不区分Widget,谁发过来都发出去,不论Widget
signals:
    void click();

signals:
    void clickWithPoint ( QPoint point );

signals:
    void clickWithPointF ( QPointF point );

#if 0
    //发给业务层
    //发回界面层
    //这里的信号都带着Widget指针,可以区分Widget
signals:
    void click ( QWidget* userWidget );
    void clickWithPoint ( QPoint point, QWidget* userWidget );
    void clickWithPointF ( QPointF point, QWidget* userWidget );
#endif

    //调用于userWidget相对应的Event里
    //允许重写
public:
    virtual void mousePressEvent ( QMouseEvent* event, QWidget* userWidget = 0 );
    virtual void mouseReleaseEvent ( QMouseEvent* event, QWidget* userWidget = 0 );
    virtual void mouseDoubleClickEvent ( QMouseEvent* event, QWidget* userWidget = 0 );

    //optional
public:
    inline const quint32 clickNum() const { return nClickNum; }
    inline const quint64 totalClickNum() const { return nTotalClickNum; }

    inline const quint32 clickNumWithCancel() const { return nClickNumWithCancel; }
    inline const quint64 totalClickNumWithCancel() const { return nTotalClickNumWithCancel; }

    /**
     * 以下用于内部
     */
public:
    typedef enum
    {
        QQtNullClick = 0,

        QQtClick,
        QQtLongClick,

        QQtDoubleClick,

        QQtMaxClick
    } QQtClickType;
    Q_ENUMS ( QQtClickType )

protected:
    //用于记录点击到了什么状态.
    QQtClickType mClickType;

    //用于记录按钮的位置
    QPoint mPoint;

    //click num
    virtual void checkClickNumWithCancel();
    virtual void checkClickNum ( QQtClickType type );

    quint32 nClickNum;
    quint64 nTotalClickNum;

    quint32 nClickNumWithCancel;
    quint64 nTotalClickNumWithCancel;
};

#endif // QQTCLICKHELPER_H
