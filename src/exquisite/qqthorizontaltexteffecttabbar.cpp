#include "qqthorizontaltexteffecttabbar.h"
#include "QStylePainter"
#include "QStyleOptionTabV3"
#include "QDebug"
#include "QPixmap"
#include "QApplication"
#include "QToolButton"
#include "qqtcore.h"

QQtHorizontalTextEffectTabBar::QQtHorizontalTextEffectTabBar(QWidget* parent) :
    QQtTabBar(parent)
{
    setFocusPolicy(Qt::NoFocus);
}

void QQtHorizontalTextEffectTabBar::paintEvent(QPaintEvent* e)
{
    Q_UNUSED(e)

    QStyleOptionTabBarBase optTabBase;
    initStyleBaseOption(&optTabBase, this, size());

    QStylePainter p(this);
    int selected = -1;
    int cutLeft = -1;
    int cutRight = -1;
    bool vertical = verticalTabs();
    QStyleOptionTab cutTabLeft;
    QStyleOptionTab cutTabRight;

    selected = currentIndex();


    //ignore drag and drop
    //if (d->dragInProgress)
    //selected = d->pressedIndex;

    ;

    for (int i = 0; i < count(); ++i)
        optTabBase.tabBarRect |= tabRect(i);

    optTabBase.selectedTabRect = tabRect(selected);

    if (drawBase())
        p.drawPrimitive(QStyle::PE_FrameTabBarBase, optTabBase);

    for (int i = 0; i < count(); ++i)
    {
        QStyleOptionTab tab;
        initStyleOption(&tab, i);

        //drag and drop ignore
//        if (d->paintWithOffsets && d->tabList[i].dragOffset != 0)
//        {
//            if (vertical)
//            {
//                tab.rect.moveTop(tab.rect.y() + d->tabList[i].dragOffset);
//            }
//            else
//            {
//                tab.rect.moveLeft(tab.rect.x() + d->tabList[i].dragOffset);
//            }
//        }

        if (!(tab.state & QStyle::State_Enabled))
        {
            tab.palette.setCurrentColorGroup(QPalette::Disabled);
        }

        // If this tab is partially obscured, make a note of it so that we can pass the information
        // along when we draw the tear.
        QRect tabRect = this->tabRect(i);
        int tabStart = vertical ? tabRect.top() : tabRect.left();
        int tabEnd = vertical ? tabRect.bottom() : tabRect.right();

        // Don't bother drawing a tab if the entire tab is outside of the visible tab bar.
        if ((!vertical && (tab.rect.right() < 0 || tab.rect.left() > width()))
            || (vertical && (tab.rect.bottom() < 0 || tab.rect.top() > height())))
            continue;

        optTabBase.tabBarRect |= tab.rect;
        if (i == selected)
            continue;
        setShape(QTabBar::RoundedNorth);
        p.drawControl(QStyle::CE_TabBarTab, tab);
        setShape(QTabBar::RoundedWest);
    }

    // Draw the selected tab last to get it "on top"
    if (selected >= 0)
    {
        QStyleOptionTab tab;
        initStyleOption(&tab, selected);
        //ignore
//        if (d->paintWithOffsets && d->tabList[selected].dragOffset != 0)
//        {
//            if (vertical)
//                tab.rect.moveTop(tab.rect.y() + d->tabList[selected].dragOffset);
//            else
//                tab.rect.moveLeft(tab.rect.x() + d->tabList[selected].dragOffset);
//        }
        setShape(QTabBar::RoundedNorth);
        p.drawControl(QStyle::CE_TabBarTab, tab);
        setShape(QTabBar::RoundedWest);
    }

    // Only draw the tear indicator if necessary. Most of the time we don't need too.
    if (0 && cutLeft >= 0)
    {
        cutTabLeft.rect = rect();
        cutTabLeft.rect = style()->subElementRect(QStyle::SE_TabBarTearIndicatorLeft, &cutTabLeft, this);
        p.drawPrimitive(QStyle::PE_IndicatorTabTearLeft, cutTabLeft);
    }

    if (0 && cutRight >= 0)
    {
        cutTabRight.rect = rect();
        cutTabRight.rect = style()->subElementRect(QStyle::SE_TabBarTearIndicatorRight, &cutTabRight, this);
        p.drawPrimitive(QStyle::PE_IndicatorTabTearRight, cutTabRight);
    }
}

void QQtHorizontalTextEffectTabBar::drawTextLabel(QPainter* p)
{
//    for (int i = 0; i < count(); ++i)
//    {
//        QStyleOptionTab opt;
//        initStyleOption(&opt, i);

//    }
//    if (const QStyleOptionTab* tab = qstyleoption_cast<const QStyleOptionTab*>(opt))
//    {
//        QRect tr = tab->rect;
//        bool verticalTabs = tab->shape == QTabBar::RoundedEast
//                            || tab->shape == QTabBar::RoundedWest
//                            || tab->shape == QTabBar::TriangularEast
//                            || tab->shape == QTabBar::TriangularWest;

//        int alignment = Qt::AlignCenter | Qt::TextShowMnemonic;
//        if (!proxy()->styleHint(SH_UnderlineShortcut, opt, widget))
//            alignment |= Qt::TextHideMnemonic;

//        if (verticalTabs)
//        {
//            p->save();
//            int newX, newY, newRot;
//            if (tab->shape == QTabBar::RoundedEast || tab->shape == QTabBar::TriangularEast)
//            {
//                newX = tr.width() + tr.x();
//                newY = tr.y();
//                newRot = 90;
//            }
//            else
//            {
//                newX = tr.x();
//                newY = tr.y() + tr.height();
//                newRot = -90;
//            }
//            QTransform m = QTransform::fromTranslate(newX, newY);
//            m.rotate(newRot);
//            p->setTransform(m, true);
//        }

//        QRect iconRect;
//        d->tabLayout(tab, widget, &tr, &iconRect);
//        tr = proxy()->subElementRect(SE_TabBarTabText, opt, widget); //we compute tr twice because the style may override subElementRect

//        if (!tab->icon.isNull())
//        {
//            QPixmap tabIcon = tab->icon.pixmap(qt_getWindow(widget), tab->iconSize,
//                                               (tab->state & State_Enabled) ? QIcon::Normal
//                                               : QIcon::Disabled,
//                                               (tab->state & State_Selected) ? QIcon::On
//                                               : QIcon::Off);
//            p->drawPixmap(iconRect.x(), iconRect.y(), tabIcon);
//        }

//        proxy()->drawItemText(p, tr, alignment, tab->palette, tab->state & State_Enabled, tab->text, QPalette::WindowText);

//        if (verticalTabs)
//            p->restore();

//        if (tab->state & State_HasFocus)
//        {
//            const int OFFSET = 1 + pixelMetric(PM_DefaultFrameWidth);

//            int x1, x2;
//            x1 = tab->rect.left();
//            x2 = tab->rect.right() - 1;

//            QStyleOptionFocusRect fropt;
//            fropt.QStyleOption::operator=(*tab);
//            fropt.rect.setRect(x1 + 1 + OFFSET, tab->rect.y() + OFFSET,
//                               x2 - x1 - 2 * OFFSET, tab->rect.height() - 2 * OFFSET);
//            drawPrimitive(PE_FrameFocusRect, &fropt, p, widget);
//        }
//    }
}
