#ifndef QQTVIRTUALCLICKLABEL_H
#define QQTVIRTUALCLICKLABEL_H

#include <qqtlabel.h>
#include <qqtclickhelper.h>

#include <qqt-local.h>
#include <qqtcore.h>

/**
 * 这个是个Virtual Click Class
 * 提供安装ClickHelper的能力
 * 提供MouseEvent响应
 *
 * 用户使用方法
 * new ClickHelper
 * installClickHelper
 */
class QQTSHARED_EXPORT QQtVirtualClickLabel : public QQtLabel
{
    Q_OBJECT
public:
    explicit QQtVirtualClickLabel ( QWidget* parent = 0 ) :
        QQtLabel ( parent ) {
        mClickHelper = 0;
        mDefaultClickHelper = 0;
    }
    virtual ~QQtVirtualClickLabel() {}

    /**
     * 提供给App用信号
     * 界面层内部直接处理
     */
signals:

signals:

    /**
     * 用户可选使用
     */
public:
    inline void installClickHelper ( QQtClickHelper* helper ) {
        unConnectClickHelper();
        mClickHelper = helper;
        if ( !mClickHelper )
            mClickHelper = mDefaultClickHelper;
        if ( !mClickHelper )
            return;
        connectClickHelper();
    }
    inline QQtClickHelper* clickHelper() const {
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
    }

    virtual void unConnectClickHelper() {
        if ( !mClickHelper )
            return;
    }

protected:
    QQtClickHelper* mClickHelper;
    QQtClickHelper* mDefaultClickHelper;

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

#endif // QQTVIRTUALCLICKLABEL_H
