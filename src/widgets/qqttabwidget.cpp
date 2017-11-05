#include "qqttabwidget.h"
#include "qqtcore.h"
#include <QTabBar>

QQtTabWidget::QQtTabWidget(QWidget* parent) :
    QTabWidget(parent)
{
}

QQtTabWidget::~QQtTabWidget()
{
}

void QQtTabWidget::setObjectName(const QString& name)
{
    tabBar()->setObjectName(QString("%1_bar").arg(name));
    /*
     * pline() << "系统tabBar的类指针被替换掉了吗？" << tabBar();
     */
    QTabWidget::setObjectName(name);
}
