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

