#include "qqtpictureeffecttabwidget.h"

QQtPictureEffectTabWidget::QQtPictureEffectTabWidget(QWidget* parent) : QQtTabWidget(parent)
{
    m_bar = new QQtPictureEffectTabBar(this);
    setTabBar(m_bar);
    /*
     * pline() << "这是我设置的bar：" << bar;
     */
}

void QQtPictureEffectTabWidget::setObjectName(const QString& name)
{
    m_bar->setObjectName(QString("%1_bar").arg(name));
    return QQtTabWidget::setObjectName(name);
}
