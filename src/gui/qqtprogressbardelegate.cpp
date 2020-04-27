#include <qqtprogressbardelegate.h>

#include <QApplication>
#include <QCommonStyle>

QQtProgressBarDelegate::QQtProgressBarDelegate ( QObject* parent )
    : QItemDelegate ( parent ) {}

QQtProgressBarDelegate::~QQtProgressBarDelegate() {}

void QQtProgressBarDelegate::drawDisplay ( QPainter* painter, const QStyleOptionViewItem& option, const QRect& rect,
                                           const QString& text ) const
{

    bool ok = false;
    int pos = text.toInt ( &ok );

    if ( ok )
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

        QStyleOptionProgressBar bar;

        //no need?
        //bar.init ( this );

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
