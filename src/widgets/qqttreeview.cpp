#include "qqttreeview.h"
#include <QHeaderView>

QQtTreeView::QQtTreeView(QWidget* parent) :
    QTreeView(parent)
{
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

QQtTreeView::~QQtTreeView()
{
}


void QQtTreeView::drawRow(QPainter* painter, const QStyleOptionViewItem& options, const QModelIndex& index) const
{
    return QTreeView::drawRow(painter, options, index);
}

void QQtTreeView::drawBranches(QPainter* painter, const QRect& rect, const QModelIndex& index) const
{
    return QTreeView::drawBranches(painter, rect, index);
}
