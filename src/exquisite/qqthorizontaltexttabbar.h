#ifndef QQTHORIZONTALTEXTTABBAR_H
#define QQTHORIZONTALTEXTTABBAR_H

#include <QColor>
#include "qqtcore.h"
#include "qqtwidgets.h"
#include "qqt-local.h"
#include <qqttabbar.h>

/**
 * @brief The QQtHorizontalTextTabBar class
 * Qt tabbar竖排文字也是竖着的，QQt改成横的。
 */
class QQTSHARED_EXPORT QQtHorizontalTextTabBar : public QQtTabBar
{
    Q_OBJECT

public:
    explicit QQtHorizontalTextTabBar ( QWidget* parent = 0 );

protected:
    virtual void paintEvent ( QPaintEvent* );
    virtual void drawTextLabel ( QPainter* p );

public slots:

private:
    static void initStyleBaseOption ( QStyleOptionTabBarBase* optTabBase, QTabBar* tabbar, QSize size ) {
//        QStyleOptionTab tabOverlap;
//        tabOverlap.shape = tabbar->shape();
//        int overlap = tabbar->style()->pixelMetric(QStyle::PM_TabBarBaseOverlap, &tabOverlap, tabbar);
//        QWidget* theParent = tabbar->parentWidget();
//        optTabBase->init(tabbar);
//        optTabBase->shape = tabbar->shape();
//        optTabBase->documentMode = tabbar->documentMode();
//        if (theParent && overlap > 0)
//        {
//            QRect rect;
//            switch (tabOverlap.shape)
//            {
//            case QTabBar::RoundedNorth:
//            case QTabBar::TriangularNorth:
//                rect.setRect(0, size.height() - overlap, size.width(), overlap);
//                break;
//            case QTabBar::RoundedSouth:
//            case QTabBar::TriangularSouth:
//                rect.setRect(0, 0, size.width(), overlap);
//                break;
//            case QTabBar::RoundedEast:
//            case QTabBar::TriangularEast:
//                rect.setRect(0, 0, overlap, size.height());
//                break;
//            case QTabBar::RoundedWest:
//            case QTabBar::TriangularWest:
//                rect.setRect(size.width() - overlap, 0, overlap, size.height());
//                break;
//            }
//            optTabBase->rect = rect;
//        }
    }
};

#endif // QQTHORIZONTALTEXTTABBAR_H
