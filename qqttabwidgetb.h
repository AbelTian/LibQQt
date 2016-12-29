#ifndef QQTTABWIDGETB_H
#define QQTTABWIDGETB_H

#include <QTabWidget>

namespace Ui {
class QQTTabWidgetB;
}

class QQTTabWidgetB : public QTabWidget
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
