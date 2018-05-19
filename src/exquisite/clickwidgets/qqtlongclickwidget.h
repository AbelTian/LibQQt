#ifndef QQTLONGCLICKWIDGET_H
#define QQTLONGCLICKWIDGET_H

#include <qqtwidget.h>
#include <qqtlongclickhelper.h>

#include <qqt-local.h>
#include <qqtcore.h>

/**
 * 提供安装ClickHelper的能力
 * 为确定功能的子类Widget服务
 */
class QQTSHARED_EXPORT QQtLongClickWidget : public QQtWidget
{
    Q_OBJECT

public:
    explicit QQtLongClickWidget ( QWidget* parent = 0 ) :
        QQtWidget ( parent ) {
        mClickHelper = 0;
        mClickHelper = new QQtLongClickHelper ( this );
        installClickHelper ( mClickHelper );
    }
    virtual ~QQtLongClickWidget() {}

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

    /**
     * 用户需要这个进行设置ClickHelper,这个label才产生click能力.
     */
public:
    inline void installClickHelper ( QQtClickHelper* helper ) {
        unConnectClickHelper();
        mClickHelper = helper;
        if ( !mClickHelper )
            return;
        connectClickHelper();
    }
    inline const QQtClickHelper* clickHelper() const {
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

private:
    QQtClickHelper* mClickHelper;

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

#endif // QQTLONGCLICKWIDGET_H
