#ifndef QQTDOUBLECLICKSOUNDWIDGET_H
#define QQTDOUBLECLICKSOUNDWIDGET_H

#include <qqtvirtualclickwidget.h>
#include <qqtdoubleclicksoundhelper.h>

#include <qqt-local.h>
#include <qqtcore.h>

/**
 * 内置DoubleClickHelper
 *
 * 添加了doubleClick支持的QQtClickSoundSoundWidget
 * 这个Widget表示了如何使用QQtWidgetClickHelper和它的子类
*/
class QQTSHARED_EXPORT QQtDoubleClickSoundWidget : public QQtVirtualClickWidget
{
    Q_OBJECT
public:
    explicit QQtDoubleClickSoundWidget ( QWidget* parent = 0 ) :
        QQtVirtualClickWidget ( parent ) {
        mClickHelper = new QQtDoubleClickSoundHelper ( this );
        mDefaultClickHelper = mClickHelper;
        installClickHelper ( mClickHelper );
    }
    virtual ~QQtDoubleClickSoundWidget() {}

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

#endif // QQTDOUBLECLICKSOUNDWIDGET_H
