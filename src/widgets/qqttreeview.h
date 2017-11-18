#ifndef QQTTREEVIEW_H
#define QQTTREEVIEW_H

#include <QTreeView>
#include <qqt-local.h>

class QQTSHARED_EXPORT QQtTreeView : public QTreeView
{
    Q_OBJECT

public:
    explicit QQtTreeView ( QWidget* parent = 0 );
    virtual ~QQtTreeView();

private:

    // QQtTreeView interface
protected:
    void drawRow ( QPainter* painter, const QStyleOptionViewItem& options, const QModelIndex& index ) const;
    void drawBranches ( QPainter* painter, const QRect& rect, const QModelIndex& index ) const;
};

#endif // QQTTREEVIEW_H
