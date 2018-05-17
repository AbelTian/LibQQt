#ifndef QQTDOUBLECLICKLABEL_H
#define QQTDOUBLECLICKLABEL_H

#include <qqtcanclicklabel.h>
#include <qqtdoubleclickhelper.h>

#include <qqt-local.h>
#include <qqtcore.h>

/**
 * 这个是个虚类
 * 提供安装ClickHelper的能力
 */
class QQTSHARED_EXPORT QQtDoubleClickLabel : public QQtCanClickLabel
{
    Q_OBJECT
public:
    explicit QQtDoubleClickLabel ( QWidget* parent = 0 );
    virtual ~QQtDoubleClickLabel();

signals:
    void click();
    void longClick();
    void doubleClick();

signals:
    void clickWithPoint ( QPoint point );
    void longClickWithPoint ( QPoint point );
    void doubleClickWithPoint ( QPoint point );

    // QQtWidget interface
protected:
    virtual void installClickHelper() override;
    virtual void uninstallClickHelper() override;
};

#endif // QQTDOUBLECLICKLABEL_H
