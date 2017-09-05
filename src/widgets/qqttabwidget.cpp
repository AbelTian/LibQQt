#include "qqttabwidget.h"
#include "ui_qqttabwidget.h"
#include "qqttabbar.h"
#include <QDebug>
#include <QPainter>
#include <QStylePainter>
#include <QStyleOptionTabWidgetFrameV2>
#include "qqtcore.h"

QQTTabWidget::QQTTabWidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::QQTTabWidget)
{
    m_bar = new QQTTabBar(this);
    setTabBar(m_bar);

    ui->setupUi(this);
}

QQTTabWidget::~QQTTabWidget()
{
    delete ui;
}

QQTTabBar *QQTTabWidget::cTabBar()
{
    return m_bar;
}

void QQTTabWidget::setObjectName(const QString &name)
{
    m_bar->setObjectName(QString("%1_bar").arg(name));
    QTabWidget::setObjectName(name);
}
