#ifndef QQTDOUBLECLICKWIDGET_H
#define QQTDOUBLECLICKWIDGET_H

#include <qqtcanclickwidget.h>
#include <qqtdoubleclickhelper.h>

#include <qqt-local.h>
#include <qqtcore.h>

/**
 * 添加了doubleClick支持的QQtClickWidget
 * 这个Widget表示了如何使用QQtWidgetClickHelper和它的子类
*/
class QQTSHARED_EXPORT QQtDoubleClickWidget : public QQtCanClickWidget
{
    Q_OBJECT
public:
    explicit QQtDoubleClickWidget ( QWidget* parent = 0 );
    virtual ~QQtDoubleClickWidget();

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

#endif // QQTDOUBLECLICKWIDGET_H
