#ifndef QQTLONGCLICKLABEL_H
#define QQTLONGCLICKLABEL_H

#include <qqtlabel.h>
#include <qqtlongclickhelper.h>

#include <qqt-local.h>
#include <qqtcore.h>

/**
 * 这个是个虚类
 * 提供安装ClickHelper的能力
 * 为确定功能的子类Label服务
 */
class QQTSHARED_EXPORT QQtLongClickLabel : public QQtLabel
{
    Q_OBJECT
public:
    explicit QQtLongClickLabel ( QWidget* parent = 0 ) :
        QQtLabel ( parent ) {
        mClickHelper = 0;
        mClickHelper = new QQtLongClickHelper ( this );
        installClickHelper ( mClickHelper );
    }
    virtual ~QQtLongClickLabel() {}

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
     * 用户可选使用
     */
public:
    inline void installClickHelper ( QQtLongClickHelper* helper ) {
        unConnectClickHelper();
        mClickHelper = helper;
        if ( !mClickHelper )
            return;
        connectClickHelper();
    }
    inline QQtLongClickHelper* clickHelper() const {
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
    QQtLongClickHelper* mClickHelper;

    /**
     * 子类不必重写MouseEvent函数,
     * 这里实现对clickHelper的响应能力
     */
    // QWidget interface
protected:
    virtual void mousePressEvent ( QMouseEvent* event ) {
        if ( mClickHelper )
            mClickHelper->mousePressEvent ( event, this );
        return QQtLabel::mousePressEvent ( event );
    }

    virtual void mouseReleaseEvent ( QMouseEvent* event ) {
        if ( mClickHelper )
            mClickHelper->mouseReleaseEvent ( event, this );
        return QQtLabel::mouseReleaseEvent ( event );
    }

    virtual void mouseDoubleClickEvent ( QMouseEvent* event ) {
        if ( mClickHelper )
            mClickHelper->mouseDoubleClickEvent ( event, this );
        return QQtLabel::mouseDoubleClickEvent ( event );
    }

};

#endif // QQTLONGCLICKLABEL_H
