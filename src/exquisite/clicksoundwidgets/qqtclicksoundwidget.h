#ifndef QQTCLICKSOUNDWIDGET_H
#define QQTCLICKSOUNDWIDGET_H

#include <qqtwidget.h>
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
class QQTSHARED_EXPORT QQtClickSoundWidget : public QQtWidget
{
    Q_OBJECT
public:
    explicit QQtClickSoundWidget ( QWidget* parent = 0 ) :
        QQtWidget ( parent ) {
        mClickHelper = 0;
        mClickHelper = new QQtClickSoundHelper ( this );
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
     * 用户可选使用
     */
public:
    inline void installClickHelper ( QQtClickSoundHelper* helper ) {
        unConnectClickHelper();
        mClickHelper = helper;
        if ( !mClickHelper )
            return;
        connectClickHelper();
    }
    inline QQtClickSoundHelper* clickHelper() const {
        return mClickHelper;
    }

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

private:
    QQtClickSoundHelper* mClickHelper;

    /**
     * 子类不必重写MouseEvent函数,
     * 这里实现对clickHelper的响应能力
     */
    // QWidget interface
protected:
    virtual void mousePressEvent ( QMouseEvent* event ) {
        if ( mClickHelper )
            mClickHelper->mousePressEvent ( event, this );
        return QQtWidget::mousePressEvent ( event );
    }

    virtual void mouseReleaseEvent ( QMouseEvent* event ) {
        if ( mClickHelper )
            mClickHelper->mouseReleaseEvent ( event, this );
        return QQtWidget::mouseReleaseEvent ( event );
    }

    virtual void mouseDoubleClickEvent ( QMouseEvent* event ) {
        if ( mClickHelper )
            mClickHelper->mouseDoubleClickEvent ( event, this );
        return QQtWidget::mouseDoubleClickEvent ( event );
    }
};

#endif // QQTCLICKSOUNDWIDGET_H
