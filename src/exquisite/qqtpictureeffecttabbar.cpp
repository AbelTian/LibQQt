#include "qqtpictureeffecttabbar.h"
#include "QStylePainter"
#include "QStyleOptionTabV3"
#include "QDebug"
#include "QPixmap"
#include "QApplication"
#include "QToolButton"
#include "qqtcore.h"

QQtTabBar::QQtTabBar(QWidget* parent) :
    QTabBar(parent)
{
    setFocusPolicy(Qt::NoFocus);
    iconStyle = IconStyle_Cover_And_BottomText;
}

void QQtTabBar::setIconStyle(QQtTabBar::IconStyle iconStyle)
{
    if (this->iconStyle != iconStyle)
    {
        this->iconStyle = iconStyle;
        update();
    }
}

void QQtTabBar::tabPixmap(int index, QImage& icon, QImage& iconSel)
{
    if (index < 0 || index + 1 > count() || index + 1 > iconList.size())
        return;

    icon = QImage(iconList[index][BTN_NORMAL]);
    iconSel = QImage(iconList[index][BTN_PRESS]);

    return ;
}

void QQtTabBar::setTabPixmap(int index, const QString& icon, const QString& iconSel)
{
    if (index < 0 || index + 1 > count())
        return;

    TBtnIconTable table;
    table[BTN_NORMAL] = icon;
    table[BTN_PRESS] = iconSel;

    iconList.insert(index, table);
}

void QQtTabBar::paintEvent(QPaintEvent* e)
{
    Q_UNUSED(e)
    QStylePainter p(this);

    for (int index = 0; index < count(); index++)
    {
        //TODO:
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
        QStyleOptionTabV3 opt;
#else
        QStyleOptionTab opt;
#endif
        initStyleOption(&opt, index);
        opt.shape = verticalTabs() ? QTabBar::RoundedWest : QTabBar::RoundedNorth;

        QRect tabRectValue = tabRect(index);
        if (iconStyle == IconStyle_Cover_And_BottomText)
            tabRectValue = tabRect(index);
        else if (iconStyle == IconStyle_Left_And_RightText)
            tabRectValue = QRect(tabRectValue.left(), tabRectValue.top(),
                                 tabRectValue.height(), tabRectValue.height());

        if (iconList.size() > index)
        {
            int sel = currentIndex() == index ? BTN_PRESS : BTN_NORMAL;
            p.drawItemPixmap(tabRectValue, Qt::AlignCenter, QIcon(iconList[index][sel]).pixmap(rect().size(), QIcon::Normal, QIcon::On));
            /*
             * 失真不明显，使用以下方法
             */
            //QImage image(iconList[index][sel]);
            //p.drawItemPixmap(tabRectValue, Qt::AlignLeft |Qt::AlignTop, QPixmap::fromImage(image.scaled(tabRectValue.size(), Qt::KeepAspectRatio)));
        }

        //opt.palette.setColor(QPalette::Normal, QPalette::Text, QColor(255, 132, 0));
        opt.palette.setColor(QPalette::Normal, QPalette::Text, tabTextColor(index));
        opt.palette.setCurrentColorGroup(QPalette::Active);
        opt.state |= QStyle::State_Sunken;

        //-rect.height()/20 上移
        verticalTabs() ? tabRectValue.adjust(0, 0, 0, 0) : tabRectValue.adjust(0, 0, 0, 0);

        if (iconStyle == IconStyle_Cover_And_BottomText)
            tabRectValue = tabRect(index);
        else if (iconStyle == IconStyle_Left_And_RightText)
            tabRectValue = QRect(tabRectValue.left() + tabRectValue.height(), tabRectValue.top(),
                                 tabRectValue.width() - tabRectValue.height(), tabRectValue.height());

        int flags = Qt::AlignCenter;
        if (iconStyle == IconStyle_Cover_And_BottomText)
            flags = verticalTabs() ? Qt::AlignHCenter | Qt::AlignBottom : Qt::AlignCenter;
        else if (iconStyle == IconStyle_Left_And_RightText)
            flags =  Qt::AlignCenter;

        //pline() << objectName() << rect;
        if (index == currentIndex())
            p.drawItemText(tabRectValue, flags, opt.palette, true, opt.text, QPalette::Text);
        else
            p.drawItemText(tabRectValue, flags, opt.palette, true, opt.text, QPalette::BrightText);
    }
}

bool QQtTabBar::verticalTabs()
{
    return shape() == QTabBar::RoundedWest
           || shape() == QTabBar::RoundedEast
           || shape() == QTabBar::TriangularWest
           || shape() == QTabBar::TriangularEast;
}
