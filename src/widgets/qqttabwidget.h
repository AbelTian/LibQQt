#ifndef QQTTABWIDGET_H
#define QQTTABWIDGET_H

#include <QTabWidget>
#include "qqttabbar.h"
#include "qqt-local.h"

namespace Ui
{
class QQTTabWidget;
}

class QQTSHARED_EXPORT QQTTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit QQTTabWidget(QWidget* parent = 0);
    ~QQTTabWidget();

    QQTTabBar* cTabBar();
    void setObjectName(const QString& name);
    void setToolTipDuration(int index) { Q_UNUSED(index) ; }

private:
    Ui::QQTTabWidget* ui;

    QQTTabBar* m_bar;
};

#endif // QQTTABWIDGET_H
