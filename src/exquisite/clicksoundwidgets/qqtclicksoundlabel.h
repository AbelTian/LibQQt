#ifndef QQTCLICKSOUNDLABEL_H
#define QQTCLICKSOUNDLABEL_H

#include <qqtlabel.h>
#include <qqtclicksoundhelper.h>

#include <qqt-local.h>
#include <qqtcore.h>

/**
 * 这个是个basic类 提供click信号
 * 提供安装ClickHelper的能力
 * 提供MouseEvent响应
 *
 * 用户使用方法
 * new ClickHelper
 * installClickHelper
 */
class QQTSHARED_EXPORT QQtClickSoundLabel : public QQtLabel
{
    Q_OBJECT
public:
    explicit QQtClickSoundLabel ( QWidget* parent = 0 ) :
        QQtLabel ( parent ) {
        mClickHelper = 0;
        mClickHelper = new QQtClickSoundHelper ( this );
        installClickHelper ( mClickHelper );
    }
    virtual ~QQtClickSoundLabel() {}

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

#endif // QQTCLICKSOUNDLABEL_H
