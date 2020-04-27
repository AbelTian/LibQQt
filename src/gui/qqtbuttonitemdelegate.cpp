#include <qqtbuttonitemdelegate.h>


#include <QApplication>
#include <QCommonStyle>

QQtButtonItemDelegate::QQtButtonItemDelegate ( QObject* parent )
    : QItemDelegate ( parent )
{
    setStyleEffect();
}

QQtButtonItemDelegate::~QQtButtonItemDelegate() {}

void QQtButtonItemDelegate::setStyleEffect ( bool effect )
{
    mStyleEffect = effect;
}

bool QQtButtonItemDelegate::styleEffect() const
{
    return mStyleEffect;
}

void QQtButtonItemDelegate::drawDisplay ( QPainter* painter, const QStyleOptionViewItem& option, const QRect& rect,
                                          const QString& text ) const
{

    bool ok = styleEffect();

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
    else
        QItemDelegate::drawDisplay ( painter, option, rect, text );
}
