#include "qqtslidetabwidget.h"

QQtSlideTabWidget::QQtSlideTabWidget(QWidget* parent) : QQtTabWidget(parent)
{
    m_bar = new QQtSlideTabBar(this);
    setTabBar(m_bar);
}


void QQtSlideTabWidget::setObjectName(const QString& name)
{
    m_bar->setObjectName(QString("%1_bar").arg(name));
    return QQtTabWidget::setObjectName(name);
}
