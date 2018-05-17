#ifndef QQTCANCLICKLABEL_H
#define QQTCANCLICKLABEL_H

#include <qqtlabel.h>
#include <qqtclickhelper.h>

#include <qqt-local.h>
#include <qqtcore.h>

/**
 * 这个是个虚类
 * 提供安装ClickHelper的能力
 * 为确定功能的子类Label服务
 */
class QQTSHARED_EXPORT QQtCanClickLabel : public QQtLabel
{
    Q_OBJECT
public:
    explicit QQtCanClickLabel ( QWidget* parent = 0 );
    virtual ~QQtCanClickLabel();

signals:

signals:

public:
    inline void setClickHelper ( QQtClickHelper* helper ) {
        uninstallClickHelper();
        mClickHelper = helper;
        installClickHelper();
    }
    inline const QQtClickHelper* clickHelper() const {
        return mClickHelper;
    }
protected:
    //需要重写
    virtual void installClickHelper() {}
    virtual void uninstallClickHelper() {}
    QQtClickHelper* mClickHelper;

    // QWidget interface
protected:
    virtual void mousePressEvent ( QMouseEvent* event ) override;
    virtual void mouseReleaseEvent ( QMouseEvent* event ) override;
    virtual void mouseDoubleClickEvent ( QMouseEvent* event ) override;
};

#endif // QQTCANCLICKLABEL_H
