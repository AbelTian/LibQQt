#include "qqthorizontaltexttabwidget.h"

QQtHorizontalTextTabWidget::QQtHorizontalTextTabWidget(QWidget* parent) : QQtTabWidget(parent)
{
    m_bar = new QQtHorizontalTextTabBar(this);
    setTabBar(m_bar);
    /*
     * pline() << "这是我设置的bar：" << bar;
     */
}

void QQtHorizontalTextTabWidget::setObjectName(const QString& name)
{
    m_bar->setObjectName(QString("%1_bar").arg(name));
    return QQtTabWidget::setObjectName(name);
}
