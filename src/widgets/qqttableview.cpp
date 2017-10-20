#include "qqttableview.h"
#include "ui_qqttableview.h"
#include <QFile>
#include <QScrollBar>
#include <QSqlRelationalDelegate>

QQTTableView::QQTTableView(QWidget *parent) :
    QTableView(parent),
    ui(new Ui::QQTTableView)
{
    ui->setupUi(this);

    m_header = new QQTHeaderView(Qt::Horizontal, this);
    m_vheader = new QQTHeaderView(Qt::Vertical, this);

    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    /*
     * 如果没有这个中介，release版本无故会崩溃。
     */
    setItemDelegate(new QSqlRelationalDelegate(this));
#ifdef __EMBEDDED_LINUX__
    setFocusPolicy(Qt::NoFocus);
#endif

}

QQTTableView::~QQTTableView()
{
    delete ui;
}

void QQTTableView::setQQTHeader()
{
    setHorizontalHeader(m_header);
}

void QQTTableView::setQQTVHeader()
{
    setVerticalHeader(m_vheader);
}

void QQTTableView::setObjectName(const QString &name)
{
    QTableView::setObjectName(name);
    horizontalHeader()->setObjectName(QString("%1_Header").arg(name));
    verticalHeader()->setObjectName(QString("%1_VHeader").arg(name));
    m_header->setObjectName(QString("%1_QQTHeader").arg(name));
    m_vheader->setObjectName(QString("%1_QQTVHeader").arg(name));
}
