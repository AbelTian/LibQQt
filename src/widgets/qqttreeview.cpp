#include "qqttreeview.h"
#include <QHeaderView>

QQtTreeView::QQtTreeView ( QWidget* parent ) :
    QTreeView ( parent )
{
    setSelectionMode ( QAbstractItemView::SingleSelection );
    setSelectionBehavior ( QAbstractItemView::SelectRows );
    setEditTriggers ( QAbstractItemView::NoEditTriggers );
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    header()->setSectionResizeMode ( QHeaderView::ResizeToContents );
#else
    header()->setResizeMode ( QHeaderView::ResizeToContents );
#endif

#ifdef __EMBEDDED_LINUX__
    setFocusPolicy ( Qt::NoFocus );
    QFont fnt ( font() );
    fnt.setPointSize ( 16 );
    setFont ( fnt );
#endif
}

QQtTreeView::~QQtTreeView()
{
}
