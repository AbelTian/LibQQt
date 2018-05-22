#ifndef QQTCLICKWIDGET_H
#define QQTCLICKWIDGET_H

#include <qqtvirtualclickwidget.h>
#include <qqtclickhelper.h>

#include <qqt-local.h>
#include <qqtcore.h>

/**
 * 内置ClickHelper
 *
 * 添加了click支持的QQtWidget
 * 这个Widget表示了如何使用QQtWidgetClickHelper和它的子类
 *
 * 注意QQtClickWidget不建议继承,
 * 如果用户添加了新的clickHelper,那么从QQtWidget继承,仿照这几个ClickWidget新写一个Widget
 * xxxClickHelper和xxxClickWidget是配对出现的.
*/
class QQTSHARED_EXPORT QQtClickWidget : public QQtVirtualClickWidget
{
    Q_OBJECT
public:
    explicit QQtClickWidget ( QWidget* parent = 0 ) :
        QQtVirtualClickWidget ( parent ) {
        mClickHelper = new QQtClickHelper ( this );
        mDefaultClickHelper = mClickHelper;
        installClickHelper ( mClickHelper );
    }
    virtual ~QQtClickWidget() {}

    /**
     * 提供给App用信号
     * 界面层内部直接处理
     */
signals:
    void click();

signals:
    void clickWithPoint ( QPoint point );

    /**
     * 子类重写这两个函数,实现丰富的click能力
     */
    // QQtWidget interface
protected:
    virtual void connectClickHelper() override {
        if ( !mClickHelper )
            return;

        connect ( mClickHelper, SIGNAL ( click() ), this, SIGNAL ( click() ) );
        connect ( mClickHelper, SIGNAL ( clickWithPoint ( QPoint ) ), this, SIGNAL ( clickWithPoint ( QPoint ) ) );
    }

    virtual void unConnectClickHelper() override {
        if ( !mClickHelper )
            return;

        disconnect ( mClickHelper, SIGNAL ( click() ), this, SIGNAL ( click() ) );
        disconnect ( mClickHelper, SIGNAL ( clickWithPoint ( QPoint ) ), this, SIGNAL ( clickWithPoint ( QPoint ) ) );
    }
};

#endif // QQTCLICKWIDGET_H
