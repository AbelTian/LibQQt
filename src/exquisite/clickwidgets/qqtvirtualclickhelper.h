#ifndef QQTVIRTUALCLICKHELPER_H
#define QQTVIRTUALCLICKHELPER_H

#include <qqt-local.h>
#include <qqtcore.h>

#if 0
#define p2debug() p2line()
#else
#define p2debug() QNoDebug()
#endif

/**
 * QQtVirtualClickHelper
 * 实现click的虚类
 *
 * 这个Helper是给Widget响应按钮事件用的
 * 主要用于为QQtWidget系列添加按钮信号识别帮助
 *
 * 支持widget->installEventFilter(thisClassInst);
 * 所有的子类ClickHelper也都支持的，用户可以为自己的Widget手动安装。
 * 可以安装多个eventFilter，互相不会冲突。
 * 同一个helper也可以为多个widget同时安装，互相不会冲突。
 *
 * 可以统计按键次数
 */
class QQTSHARED_EXPORT QQtVirtualClickHelper : public QObject
{
    Q_OBJECT

public:
    explicit QQtVirtualClickHelper ( QObject* parent = 0 );
    virtual ~QQtVirtualClickHelper();

    //发给业务层
    //发回界面层
    //这些信号不区分Widget,谁发过来都发出去,不论Widget
signals:

signals:

signals:

    //调用于userWidget相对应的Event里
    //重写
public:
    virtual void mousePressEvent ( QMouseEvent* event, QWidget* userWidget = 0 );
    virtual void mouseReleaseEvent ( QMouseEvent* event, QWidget* userWidget = 0 );
    virtual void mouseDoubleClickEvent ( QMouseEvent* event, QWidget* userWidget = 0 );

    //optional
public:
    inline const quint64 totalClickNum() const { return nTotalClickNum; }
    inline const quint64 totalClickNumWithCancel() const { return nTotalClickNumWithCancel; }

    /**
     * 以下用于内部
     */
public:
    //允许支持的点击类型 可添加
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

    //click num 要求重写
    virtual void checkClickNumWithCancel();
    virtual void checkClickNum ( QQtClickType type );

    quint64 nTotalClickNum;
    quint64 nTotalClickNumWithCancel;

    // QObject interface
public:
    virtual bool eventFilter ( QObject* watched, QEvent* event ) override;
};

#endif // QQTVIRTUALCLICKHELPER_H
