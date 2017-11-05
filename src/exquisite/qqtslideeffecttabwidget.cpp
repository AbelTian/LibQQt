#include "qqtslideeffecttabwidget.h"

QQtSlideEffectTabWidget::QQtSlideEffectTabWidget(QWidget* parent) : QQtTabWidget(parent)
{
    m_bar = new QQtSlideEffectTabBar(this);
    setTabBar(m_bar);
}


void QQtSlideEffectTabWidget::setObjectName(const QString& name)
{
    m_bar->setObjectName(QString("%1_bar").arg(name));
    return QQtTabWidget::setObjectName(name);
}

QTabBar* QQtSlideEffectTabWidget::localTabBar() const
{
    return m_bar;
}
