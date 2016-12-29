#ifndef QQTTABWIDGET_H
#define QQTTABWIDGET_H

#include <QTabWidget>
#include "qqttabbar.h"

namespace Ui {
class QQTTabWidget;
}

class QQTTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit QQTTabWidget(QWidget *parent = 0);
    ~QQTTabWidget();

    QQTTabBar* cTabBar();
    void setObjectName(const QString &name);
    void setToolTipDuration(int index){;}

private:
    Ui::QQTTabWidget *ui;

    QQTTabBar* m_bar;
};

#endif // QQTTABWIDGET_H
