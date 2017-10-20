#include "qqttreeview.h"
#include "ui_qqttreeview.h"
#include <QFile>

QQTTreeView::QQTTreeView(QWidget *parent) :
    QTreeView(parent),
    ui(new Ui::QQTTreeView)
{
    ui->setupUi(this);

    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    header()->setResizeMode(QHeaderView::ResizeToContents);
#else
    header()->setSectionResizeMode(QHeaderView::ResizeToContents);
#endif

#ifdef __EMBEDDED_LINUX__
    setFocusPolicy(Qt::NoFocus);
    QFont fnt(font());
    fnt.setPointSize(16);
    setFont(fnt);
#endif
}

QQTTreeView::~QQTTreeView()
{
    delete ui;
}


void QQTTreeView::drawRow(QPainter *painter, const QStyleOptionViewItem &options, const QModelIndex &index) const
{
    return QTreeView::drawRow(painter, options, index);
}

void QQTTreeView::drawBranches(QPainter *painter, const QRect &rect, const QModelIndex &index) const
{
    return QTreeView::drawBranches(painter, rect, index);
}
