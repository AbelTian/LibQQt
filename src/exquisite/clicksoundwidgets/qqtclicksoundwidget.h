#ifndef QQTCLICKSOUNDWIDGET_H
#define QQTCLICKSOUNDWIDGET_H

#include <qqtvirtualclickwidget.h>
#include <qqtclicksoundhelper.h>

#include <qqt-local.h>
#include <qqtcore.h>

/**
 * 内置ClickHelper
 *
 * 添加了clickSound支持的QQtWidget
 * 这个Widget表示了如何使用QQtClickSoundHelper和它的子类
 *
*/
class QQTSHARED_EXPORT QQtClickSoundWidget : public QQtVirtualClickWidget
{
    Q_OBJECT
public:
    explicit QQtClickSoundWidget ( QWidget* parent = 0 ) :
        QQtVirtualClickWidget ( parent ) {
        mClickHelper = new QQtClickSoundHelper ( this );
        mDefaultClickHelper = mClickHelper;
        installClickHelper ( mClickHelper );
    }
    virtual ~QQtClickSoundWidget() {}

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
    virtual void connectClickHelper() {
        if ( !mClickHelper )
            return;

        connect ( mClickHelper, SIGNAL ( click() ), this, SIGNAL ( click() ) );
        connect ( mClickHelper, SIGNAL ( clickWithPoint ( QPoint ) ), this, SIGNAL ( clickWithPoint ( QPoint ) ) );
    }

    virtual void unConnectClickHelper() {
        if ( !mClickHelper )
            return;

        disconnect ( mClickHelper, SIGNAL ( click() ), this, SIGNAL ( click() ) );
        disconnect ( mClickHelper, SIGNAL ( clickWithPoint ( QPoint ) ), this, SIGNAL ( clickWithPoint ( QPoint ) ) );
    }
};

#endif // QQTCLICKSOUNDWIDGET_H
