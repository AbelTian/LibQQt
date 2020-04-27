#ifndef QQTBUTTONITEMDELEGATE_H
#define QQTBUTTONITEMDELEGATE_H


#include <QApplication>
#include <QItemDelegate>
#include <QStyleOptionViewItem>
#include <QPushButton>
#include <QPainter>

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
 *
 * 无法正常显示
 */
class QQTSHARED_EXPORT QQtButtonItemDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    explicit QQtButtonItemDelegate ( QObject* parent = 0 )
        : QItemDelegate ( parent ) {}
    virtual ~QQtButtonItemDelegate() {}

protected:

private:

    // QItemDelegate interface
protected:
    virtual void drawDisplay ( QPainter* painter, const QStyleOptionViewItem& option,
                               const QRect& rect, const QString& text ) const override

    {
#if 0
        int radio = 5;
#else
        int radio = 0;
#endif
        int top = option.rect.top() + radio;
        int left = option.rect.left() + radio;
        int width = option.rect.width() - 2 * radio;
        int height = option.rect.height() - 2 * radio;

        QStyleOptionButton item;

        //no need?
        item.init ( option.widget );

        item.rect.setRect ( left, top, width, height ); //设置其在表格中的位置
        item.state = option.state;

        item.text = QString ( "%1" ).arg ( text );
        item.icon = option.icon;

        //最后一个参数有必要给一个QPushButton吗？
        //可以用样式表美化这个PushButton吗？
        QApplication::style()->drawControl ( QStyle::CE_PushButton, &item, painter );
    }
};

#endif // QQTBUTTONITEMDELEGATE_H

