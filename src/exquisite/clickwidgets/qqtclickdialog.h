#ifndef QQTCLICKDIALOG_H
#define QQTCLICKDIALOG_H

#include <qqtvirtualclickdialog.h>
#include <qqtclickhelper.h>

#include <qqt-local.h>
#include <qqtcore.h>

/**
 * 内置ClickHelper
 *
 * 添加了click支持的QQtDialog
 * 这个Dialog表示了如何使用QQtClickHelper和它的子类
 *
 * 注意QQtClickDialog不建议继承,
 * 如果用户添加了新的clickHelper,那么从QQtDialog继承,仿照这几个ClickDialog新写一个Dialog
 * xxxClickHelper和xxxClickDialog是配对出现的.
*/
class QQTSHARED_EXPORT QQtClickDialog : public QQtVirtualClickDialog
{
    Q_OBJECT
public:
    explicit QQtClickDialog ( QWidget* parent = 0 ) :
        QQtVirtualClickDialog ( parent ) {
        mClickHelper = new QQtClickHelper ( this );
        mDefaultClickHelper = mClickHelper;
        installClickHelper ( mClickHelper );
    }
    virtual ~QQtClickDialog() {}

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
    // QQtDialog interface
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

#endif // QQTCLICKDIALOG_H
