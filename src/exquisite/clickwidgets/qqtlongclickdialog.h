#ifndef QQTLONGCLICKDIALOG_H
#define QQTLONGCLICKDIALOG_H

#include <qqtvirtualclickdialog.h>
#include <qqtlongclickhelper.h>

#include <qqt-local.h>
#include <qqtcore.h>

/**
 * 提供安装ClickHelper的能力
 * 为确定功能的子类Dialog服务
 */
class QQTSHARED_EXPORT QQtLongClickDialog : public QQtVirtualClickDialog
{
    Q_OBJECT

public:
    explicit QQtLongClickDialog ( QWidget* parent = 0 ) :
        QQtVirtualClickDialog ( parent ) {
        mClickHelper = new QQtLongClickHelper ( this );
        mDefaultClickHelper = mClickHelper;
        installClickHelper ( mClickHelper );
    }
    virtual ~QQtLongClickDialog() {}

    /**
     * 提供给App用信号
     * 界面层内部直接处理
     */
signals:
    void click();
    void longClick();

signals:
    void clickWithPoint ( QPoint point );
    void longClickWithPoint ( QPoint point );

    // QQtVirtualClickDialog interface
protected:
    virtual void connectClickHelper() {
        if ( !mClickHelper )
            return;

        connect ( mClickHelper, SIGNAL ( click() ), this, SIGNAL ( click() ) );
        connect ( mClickHelper, SIGNAL ( longClick() ), this, SIGNAL ( longClick() ) );
        connect ( mClickHelper, SIGNAL ( clickWithPoint ( QPoint ) ), this, SIGNAL ( clickWithPoint ( QPoint ) ) );
        connect ( mClickHelper, SIGNAL ( longClickWithPoint ( QPoint ) ), this, SIGNAL ( longClickWithPoint ( QPoint ) ) );
    }

    virtual void unConnectClickHelper() {
        if ( !mClickHelper )
            return;

        disconnect ( mClickHelper, SIGNAL ( click() ), this, SIGNAL ( click() ) );
        disconnect ( mClickHelper, SIGNAL ( longClick() ), this, SIGNAL ( longClick() ) );
        disconnect ( mClickHelper, SIGNAL ( clickWithPoint ( QPoint ) ), this, SIGNAL ( clickWithPoint ( QPoint ) ) );
        disconnect ( mClickHelper, SIGNAL ( longClickWithPoint ( QPoint ) ), this, SIGNAL ( longClickWithPoint ( QPoint ) ) );
    }
};

#endif // QQTLONGCLICKDIALOG_H
