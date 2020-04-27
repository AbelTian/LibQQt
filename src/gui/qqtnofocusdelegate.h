#ifndef QQTNOFOCUSDELEGATE_H
#define QQTNOFOCUSDELEGATE_H

#include <QObject>
#include <QPainter>
#include <QModelIndex>
#include <QItemDelegate>
#include <QStyleOptionViewItem>

#include <qqt-local.h>
/**
 * @brief The QQtNoFocusDelegate class
 * Qt Table Item没有选中框
 */
class QQTSHARED_EXPORT QQtNoFocusDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    explicit QQtNoFocusDelegate ( QObject* parent = 0 )
        : QItemDelegate ( parent ) {}
    virtual ~QQtNoFocusDelegate() {}

protected:

private:


    // QItemDelegate interface
protected:
    virtual void drawFocus ( QPainter* painter, const QStyleOptionViewItem& option,
                             const QRect& rect ) const override {
    }
};

#endif // QQTNOFOCUSDELEGATE_H

