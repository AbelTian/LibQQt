#ifndef QQTCANCLICKWIDGET_H
#define QQTCANCLICKWIDGET_H

#include <qqtwidget.h>
#include <qqtclickhelper.h>

#include <qqt-local.h>
#include <qqtcore.h>

/**
 * 这个是个虚类
 * 提供安装ClickHelper的能力
 * 为确定功能的子类Widget服务
 */
class QQTSHARED_EXPORT QQtCanClickWidget : public QQtWidget
{
    Q_OBJECT
public:
    explicit QQtCanClickWidget ( QWidget* parent = 0 );
    virtual ~QQtCanClickWidget();

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

#endif // QQTCANCLICKWIDGET_H
