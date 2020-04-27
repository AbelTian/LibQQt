#ifndef QQTBUTTONITEMDELEGATE_H
#define QQTBUTTONITEMDELEGATE_H

#include <QObject>
#include <QPainter>
#include <QModelIndex>
#include <QItemDelegate>
#include <QStyleOptionViewItem>

#include <qqt-local.h>
/**
 * @brief The QQtButtonItemDelegate class
 * Qt表格 按钮代理
 *
 * 不用代理也可以。
 * QTableWidget::setCellWidget(int row, int column, QWidget *widget)
 * QAbstractItemView::setIndexWidget(const QModelIndex &index, QWidget *widget)
 *
 * M model      对数据的抽象模型，
 * V view       对窗口的抽象模型，有table、treetable等
 * C controler  联系model、view的交互工作，包括delegate、写在window，dialog里面的业务代码。
 */
class QQTSHARED_EXPORT QQtButtonItemDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    explicit QQtButtonItemDelegate ( QObject* parent = 0 );
    virtual ~QQtButtonItemDelegate();

    //设置开启Button Style，关闭后和不设置是一样的。默认开启。
    void setStyleEffect ( bool effect = true );
    bool styleEffect() const;

protected:

private:
    bool mStyleEffect;

    // QItemDelegate interface
protected:
    virtual void drawDisplay ( QPainter* painter, const QStyleOptionViewItem& option, const QRect& rect,
                               const QString& text ) const override;
};

#endif // QQTBUTTONITEMDELEGATE_H

