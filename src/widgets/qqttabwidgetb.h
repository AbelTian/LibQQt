#ifndef QQTTABWIDGETB_H
#define QQTTABWIDGETB_H

#include <QTabWidget>
#include <qqt.h>

namespace Ui {
class QQTTabWidgetB;
}

class QQTSHARED_EXPORT QQTTabWidgetB : public QTabWidget
{
    Q_OBJECT

public:
    explicit QQTTabWidgetB(QWidget *parent = 0);
    ~QQTTabWidgetB();

    QTabBar* tabBar() { return QTabWidget::tabBar(); }

private:
    Ui::QQTTabWidgetB *ui;
};

#endif // QQTTABWIDGETB_H
