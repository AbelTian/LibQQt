#ifndef QQTPROGRESSBARDELEGATE_H
#define QQTPROGRESSBARDELEGATE_H

#include <QApplication>
#include <QItemDelegate>
#include <QStyleOptionViewItem>
#include <QPainter>

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
    explicit QQtProgressBarDelegate ( QObject* parent = 0 )
        : QItemDelegate ( parent ) {}
    virtual ~QQtProgressBarDelegate() {}

protected:

private:

    // QItemDelegate interface
protected:
    virtual void drawDisplay ( QPainter* painter, const QStyleOptionViewItem& option,
                               const QRect& rect, const QString& text ) const override {

        bool ok = false;
        int pos = text.toInt ( &ok );

        if ( ok ) {
#if 0
            int radio = 5;
#else
            int radio = 0;
#endif
            int top = option.rect.top() + radio;
            int left = option.rect.left() + radio;
            int width = option.rect.width() - 2 * radio;
            int height = option.rect.height() - 2 * radio;

            QStyleOptionProgressBar bar;

            //no need?
            bar.init ( option.widget );

            bar.rect.setRect ( left, top, width, height ); //设置其在表格中的位置
            bar.state = option.state;

            //设置对应model列的值，需要自定义model
            bar.progress = pos;
            bar.maximum = 100;
            bar.minimum = 0;
            bar.textVisible = true;
            bar.text = QString ( "%1%" ).arg ( bar.progress );
            bar.textAlignment = Qt::AlignCenter;

            //最后一个参数有必要给一个QProgressBar吗？
            //可以用样式表美化这个ProgressBar吗？
            QApplication::style()->drawControl ( QStyle::CE_ProgressBar, &bar, painter );
        }
        else
            QItemDelegate::drawDisplay ( painter, option, rect, text );
    }
};

#endif // QQTPROGRESSBARDELEGATE_H

