#ifndef QQTDOUBLECLICKLABEL_H
#define QQTDOUBLECLICKLABEL_H

#include <qqtvirtualclicklabel.h>
#include <qqtdoubleclickhelper.h>

#include <qqt-local.h>
#include <qqtcore.h>

/**
 * 这个是个虚类
 * 提供安装ClickHelper的能力
 */
class QQTSHARED_EXPORT QQtDoubleClickLabel : public QQtVirtualClickLabel
{
public:
    explicit QQtDoubleClickLabel ( QWidget* parent = 0 ) :
        QQtVirtualClickLabel ( parent ) {
        mClickHelper = new QQtDoubleClickHelper ( this );
        mDefaultClickHelper = mClickHelper;
        installClickHelper ( mClickHelper );
    }
    virtual ~QQtDoubleClickLabel() {}

    /**
     * 提供给App用信号
     * 界面层内部直接处理
     */
signals:
    void click();
    void longClick();
    void doubleClick();

signals:
    void clickWithPoint ( QPoint point );
    void longClickWithPoint ( QPoint point );
    void doubleClickWithPoint ( QPoint point );

    /**
     * 子类重写这两个函数,实现丰富的click能力
     */
    // QQtWidget interface
protected:
    virtual void connectClickHelper() {
        if ( !mClickHelper )
            return;

        connect ( mClickHelper, SIGNAL ( click() ), this, SIGNAL ( click() ) );
        connect ( mClickHelper, SIGNAL ( longClick() ), this, SIGNAL ( longClick() ) );
        connect ( mClickHelper, SIGNAL ( doubleClick() ), this, SIGNAL ( doubleClick() ) );
        connect ( mClickHelper, SIGNAL ( clickWithPoint ( QPoint ) ), this, SIGNAL ( clickWithPoint ( QPoint ) ) );
        connect ( mClickHelper, SIGNAL ( longClickWithPoint ( QPoint ) ), this, SIGNAL ( longClickWithPoint ( QPoint ) ) );
        connect ( mClickHelper, SIGNAL ( doubleClickWithPoint ( QPoint ) ), this, SIGNAL ( doubleClickWithPoint ( QPoint ) ) );
    }

    virtual void unConnectClickHelper() {
        if ( !mClickHelper )
            return;

        disconnect ( mClickHelper, SIGNAL ( click() ), this, SIGNAL ( click() ) );
        disconnect ( mClickHelper, SIGNAL ( longClick() ), this, SIGNAL ( longClick() ) );
        disconnect ( mClickHelper, SIGNAL ( doubleClick() ), this, SIGNAL ( doubleClick() ) );
        disconnect ( mClickHelper, SIGNAL ( clickWithPoint ( QPoint ) ), this, SIGNAL ( clickWithPoint ( QPoint ) ) );
        disconnect ( mClickHelper, SIGNAL ( longClickWithPoint ( QPoint ) ), this, SIGNAL ( longClickWithPoint ( QPoint ) ) );
        disconnect ( mClickHelper, SIGNAL ( doubleClickWithPoint ( QPoint ) ), this,
                     SIGNAL ( doubleClickWithPoint ( QPoint ) ) );
    }

};

#endif // QQTDOUBLECLICKLABEL_H
