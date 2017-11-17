#ifndef QQTHEADERVIEW_H
#define QQTHEADERVIEW_H

#include <QHeaderView>
#include <qqt-local.h>
/**
 * @brief The QQTHeaderView class
 * Qt4.8.7 不能HeaderView背景全部透明，重写
 */
class QQTSHARED_EXPORT QQTHeaderView : public QHeaderView
{
    Q_OBJECT
public:
    explicit QQTHeaderView ( Qt::Orientation orientation = Qt::Horizontal, QWidget* parent = 0 );

signals:

public slots:


    // QHeaderView interface
protected:
    void paintSection ( QPainter* painter, const QRect& rect, int logicalIndex ) const;
    QSize sectionSizeFromContents ( int logicalIndex ) const;

    // QWidget interface
protected:
    void paintEvent ( QPaintEvent* );

private:
    Qt::Orientation ori;
};

#endif // QQTHEADERVIEW_H
