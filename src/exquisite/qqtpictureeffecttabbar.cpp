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
    iconStyle = IconStyle_Cover_And_RightText;
    textColor = QColor(0, 0, 0);
    backgroundColor = QColor(0, 0, 0);
    selectedTextColor = QColor(255, 255, 255);
    textFont = QApplication::font();
    setDrawBase(false);
}

void QQtTabBar::setIconStyle(QQtTabBar::IconStyle iconStyle)
{
    if (this->iconStyle != iconStyle)
    {
        this->iconStyle = iconStyle;
        update();
    }
}

void QQtTabBar::setTextFont(QFont textFont)
{
    if (this->textFont != textFont)
    {
        this->textFont = textFont;
        update();
    }
}

void QQtTabBar::setTextColor(QColor textColor)
{
    if (this->textColor != textColor)
    {
        this->textColor = textColor;
        update();
    }
}

void QQtTabBar::setSelectedTextColor(QColor selectedTextColor)
{
    if (this->selectedTextColor != selectedTextColor)
    {
        this->selectedTextColor = selectedTextColor;
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

void QQtTabBar::setBackgroundColor(QColor backgroundColor)
{
    if (this->backgroundColor != backgroundColor)
    {
        this->backgroundColor = backgroundColor;
        update();
    }
}

void QQtTabBar::paintEvent(QPaintEvent* e)
{
    Q_UNUSED(e)
    QPainter p(this);
    drawBackground(&p);
    drawPicture(&p);
    drawText(&p);
}

void QQtTabBar::drawBackground(QPainter* p)
{
    bool b = drawBase();
    if (b)
    {
        for (int index = 0; index < count(); index++)
        {
            p->save();

            p->setBrush(QBrush(backgroundColor));
            p->fillRect(tabRect(index), backgroundColor);
            p->restore();
        }
    }
}

void QQtTabBar::drawPicture(QPainter* p)
{
    for (int index = 0; index < count(); index++)
    {
        QRect iconRect = tabRect(index);
        if (iconStyle == IconStyle_Left_And_RightText)
            iconRect = QRect(iconRect.left(), iconRect.top(),
                             iconRect.height(), iconRect.height());

        if (iconList.size() > index)
        {
            p->save();
            int sel = currentIndex() == index ? BTN_PRESS : BTN_NORMAL;
            //tabRect = rect()?
            p->drawPixmap(iconRect, QIcon(iconList[index][sel]).pixmap(iconRect.size(), QIcon::Normal, QIcon::On));
            /*
             * 失真不明显，使用以下方法
             */
            //QImage image(iconList[index][sel]);
            //p.drawItemPixmap(tabRectValue, Qt::AlignLeft |Qt::AlignTop, QPixmap::fromImage(image.scaled(tabRectValue.size(), Qt::KeepAspectRatio)));
            p->restore();
        }
    }
}

void QQtTabBar::drawText(QPainter* p)
{
    for (int index = 0; index < count(); index++)
    {
        QRect tabTextRect = tabRect(index);
        //-rect.height()/20 上移
        verticalTabs() ? tabTextRect.adjust(0, 0, 0, 0) : tabTextRect.adjust(0, 0, 0, 0);

        if (iconStyle == IconStyle_Left_And_RightText)
            tabTextRect = QRect(tabTextRect.left() + tabTextRect.height(), tabTextRect.top(),
                                tabTextRect.width() - tabTextRect.height(), tabTextRect.height());

        int flags = Qt::AlignCenter;
        if (iconStyle == IconStyle_Cover_And_BottomText)
            flags = Qt::AlignHCenter | Qt::AlignBottom;
        else if (iconStyle == IconStyle_Cover_And_TopText)
            flags = Qt::AlignHCenter | Qt::AlignTop;
        else if (iconStyle == IconStyle_Cover_And_LeftText)
            flags = Qt::AlignVCenter | Qt::AlignLeft;
        else if (iconStyle == IconStyle_Cover_And_RightText)
            flags = Qt::AlignVCenter | Qt::AlignRight;

        //pline() << objectName() << rect;
        //if on board text is normal, this is right. otherwise the palette is right
        p->save();
        p->setFont(textFont);
        if (index == currentIndex())
            p->setPen(selectedTextColor);
        else
            p->setPen(textColor);
        p->drawText(tabTextRect, flags, tabText(index));
        p->restore();
    }
}

bool QQtTabBar::verticalTabs()
{
    return shape() == QTabBar::RoundedWest
           || shape() == QTabBar::RoundedEast
           || shape() == QTabBar::TriangularWest
           || shape() == QTabBar::TriangularEast;
}
