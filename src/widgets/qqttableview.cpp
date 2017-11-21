#include "qqttableview.h"
#include <QFile>
#include <QScrollBar>
#include <QSqlRelationalDelegate>

QQtTableView::QQtTableView(QWidget* parent) :
    QTableView(parent)
{
    m_header = new QQtHeaderView(Qt::Horizontal, this);
    m_vheader = new QQtHeaderView(Qt::Vertical, this);

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

QQtTableView::~QQtTableView()
{
}

void QQtTableView::setQQTHeader()
{
    setHorizontalHeader(m_header);
}

void QQtTableView::setQQTVHeader()
{
    setVerticalHeader(m_vheader);
}

void QQtTableView::setObjectName(const QString& name)
{
    QTableView::setObjectName(name);
    horizontalHeader()->setObjectName(QString("%1_Header").arg(name));
    verticalHeader()->setObjectName(QString("%1_VHeader").arg(name));
    m_header->setObjectName(QString("%1_QQTHeader").arg(name));
    m_vheader->setObjectName(QString("%1_QQTVHeader").arg(name));
}
