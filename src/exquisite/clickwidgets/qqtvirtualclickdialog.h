#ifndef QQTVIRTUALCLICKDIALOG_H
#define QQTVIRTUALCLICKDIALOG_H

#include <qqtdialog.h>
#include <qqtclickhelper.h>

#include <qqt-local.h>
#include <qqtcore.h>

/**
 * 内置ClickHelper空指针
 *
 * QQtVirtualClickDialog
 * 添加允许Click的功能
 * 子类实现具体click信号
 *
*/
class QQTSHARED_EXPORT QQtVirtualClickDialog : public QQtDialog
{
    Q_OBJECT
public:
    explicit QQtVirtualClickDialog ( QWidget* parent = 0 ) :
        QQtDialog ( parent ) {
        mClickHelper = 0;
        mDefaultClickHelper = 0;
        installEventFilter ( this );
    }
    virtual ~QQtVirtualClickDialog() {}

    /**
     * 提供给App用信号
     * 界面层内部直接处理
     */
signals:

signals:

    /**
     * 用户可选使用
     * 子类必然使用
     */
public:
    inline void installClickHelper ( QQtVirtualClickHelper* helper ) {
        unConnectClickHelper();
        mClickHelper = helper;
        if ( !mClickHelper )
            mClickHelper = mDefaultClickHelper;
        if ( !mClickHelper )
            return;
        connectClickHelper();
    }
    inline QQtVirtualClickHelper* clickHelper() const {
        return mClickHelper;
    }

    /**
     * 子类重写这两个函数,实现丰富的click能力
     */
    // QQtDialog interface
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
    /**
     * 如果默认的没有设置
     * 那么会出现空指针.
     * 在构造函数里初始化clickHelper的时候初始化DefaultClickHelper
     */
    QQtVirtualClickHelper* mClickHelper;
    QQtVirtualClickHelper* mDefaultClickHelper;

    /**
     * 子类不必重写MouseEvent函数,
     * 这里实现对clickHelper的响应能力
     */
    // QWidget interface
protected:
    virtual void mousePressEvent ( QMouseEvent* event ) {
        //if ( mClickHelper )
        //    mClickHelper->mousePressEvent ( event, this );
        return QQtDialog::mousePressEvent ( event );
    }

    virtual void mouseReleaseEvent ( QMouseEvent* event ) {
        //if ( mClickHelper )
        //    mClickHelper->mouseReleaseEvent ( event, this );
        return QQtDialog::mouseReleaseEvent ( event );
    }

    virtual void mouseDoubleClickEvent ( QMouseEvent* event ) {
        //if ( mClickHelper )
        //    mClickHelper->mouseDoubleClickEvent ( event, this );
        return QQtDialog::mouseDoubleClickEvent ( event );
    }

    // QObject interface
public:
    virtual bool eventFilter ( QObject* watched, QEvent* event ) override {
        //过滤掉不是自己的
        if ( watched != this )
            return QQtDialog::eventFilter ( watched, event );

        //修复 paint bug
        /*fix the parent handled bug terminally*/
        if ( event->type() == QEvent::Paint )
            return QQtDialog::eventFilter ( watched, event );

        //+ fix bug

        //处理press
        if ( event->type() == QEvent::MouseButtonPress ) {
            QMouseEvent* e = ( QMouseEvent* ) event;
            //pline() << hex << e->button();
            if ( e->button() == Qt::LeftButton ) {
                if ( mClickHelper )
                    mClickHelper->mousePressEvent ( e, this );
                event->accept();
                return true;
            }
        }

        //处理release
        if ( event->type() == QEvent::MouseButtonRelease ) {
            QMouseEvent* e = ( QMouseEvent* ) event;
            //pline() << hex << e->button();
            if ( e->button() == Qt::LeftButton ) {
                if ( mClickHelper )
                    mClickHelper->mouseReleaseEvent ( e, this );
                event->accept();
                return true;
            }
        }

        //处理doubleclick
        if ( event->type() == QEvent::MouseButtonDblClick ) {
            QMouseEvent* e = ( QMouseEvent* ) event;
            //pline() << hex << e->button();
            if ( e->button() == Qt::NoButton ) {
                if ( mClickHelper )
                    mClickHelper->mouseDoubleClickEvent ( e, this );
                event->accept();
                return true;
            }
        }

        return QQtDialog::eventFilter ( watched, event );;
    }
};

#endif // QQTVIRTUALCLICKDIALOG_H
