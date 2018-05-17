#ifndef QQTCLICKLABEL_H
#define QQTCLICKLABEL_H

#include <qqtcanclicklabel.h>
#include <qqtclickhelper.h>

#include <qqt-local.h>
#include <qqtcore.h>

/**
 * 这个是个虚类
 * 提供安装ClickHelper的能力
 */
class QQTSHARED_EXPORT QQtClickLabel : public QQtCanClickLabel
{
    Q_OBJECT
public:
    explicit QQtClickLabel ( QWidget* parent = 0 );
    virtual ~QQtClickLabel();

signals:
    void click();
    void longClick();

signals:
    void clickWithPoint ( QPoint point );
    void longClickWithPoint ( QPoint point );

    // QQtWidget interface
protected:
    virtual void installClickHelper() override;
    virtual void uninstallClickHelper() override;
};

#endif // QQTCLICKLABEL_H
