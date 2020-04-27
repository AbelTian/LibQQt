#ifndef QQTPROGRESSBARDELEGATE_H
#define QQTPROGRESSBARDELEGATE_H

#include <QObject>
#include <QPainter>
#include <QModelIndex>
#include <QItemDelegate>
#include <QStyleOptionViewItem>

#include <qqt-local.h>
/**
 * @brief The QQtProgressBarDelegate class
 * Qt表格进度条代理
 *
 * 不用代理也可以。
 * QTableWidget::setCellWidget(int row, int column, QWidget *widget)
 * QAbstractItemView::setIndexWidget(const QModelIndex &index, QWidget *widget)
 */
class QQTSHARED_EXPORT QQtProgressBarDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    explicit QQtProgressBarDelegate ( QObject* parent = 0 );
    virtual ~QQtProgressBarDelegate();

protected:

private:

    // QItemDelegate interface
protected:
    virtual void drawDisplay ( QPainter* painter, const QStyleOptionViewItem& option, const QRect& rect,
                               const QString& text ) const override;
};

#endif // QQTPROGRESSBARDELEGATE_H

