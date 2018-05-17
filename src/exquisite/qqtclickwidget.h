#ifndef QQTCLICKWIDGET_H
#define QQTCLICKWIDGET_H

#include <qqtcanclickwidget.h>
#include <qqtclickhelper.h>

#include <qqt-local.h>
#include <qqtcore.h>

/**
 * 添加了longClick支持的QQtCanClickWidget
 * 这个Widget表示了如何使用QQtWidgetClickHelper和它的子类
*/
class QQTSHARED_EXPORT QQtClickWidget : public QQtCanClickWidget
{
    Q_OBJECT
public:
    explicit QQtClickWidget ( QWidget* parent = 0 );
    virtual ~QQtClickWidget();

    /**
     * 按键功能支持者
     */
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

#endif // QQTCLICKWIDGET_H
