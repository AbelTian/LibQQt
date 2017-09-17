#ifndef QQTTREEVIEW_H
#define QQTTREEVIEW_H

#include <QTreeView>
#include <qqt.h>

namespace Ui {
class QQTTreeView;
}

class QQTSHARED_EXPORT QQTTreeView : public QTreeView
{
    Q_OBJECT

public:
    explicit QQTTreeView(QWidget *parent = 0);
    ~QQTTreeView();

private:
    Ui::QQTTreeView *ui;

    // QQTTreeView interface
protected:
    void drawRow(QPainter *painter, const QStyleOptionViewItem &options, const QModelIndex &index) const;
    void drawBranches(QPainter *painter, const QRect &rect, const QModelIndex &index) const;
};

#endif // QQTTREEVIEW_H
