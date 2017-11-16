#ifndef QQTPICTUREEFFECTTABBAR_H
#define QQTPICTUREEFFECTTABBAR_H

#include <QTabBar>
#include <QList>
#include <QColor>
#include "qqtcore.h"
#include "qqtwidgets.h"
#include "qqttabbar.h"
#include "qqt-local.h"

class QQTSHARED_EXPORT QQtPictureEffectTabBar : public QQtTabBar
{
    Q_OBJECT

public:
    explicit QQtPictureEffectTabBar(QWidget* parent = 0);

    enum IconStyle
    {
        //picture style
        IconStyle_Cover_And_TopText,
        IconStyle_Cover_And_BottomText,
        IconStyle_Cover_And_LeftText,
        IconStyle_Cover_And_RightText,
        //color style
        IconStyle_Left_And_RightText,
        IconStyle_Max_Style
    };

    IconStyle getIconStyle() const { return iconStyle; }
    void setIconStyle(IconStyle iconStyle);

    QFont getTextFont() const { return textFont; }
    void setTextFont(QFont textFont);

    QColor getTextColor() const { return textColor; }
    void setTextColor(QColor textColor);

    QColor getSelectedTextColor() const { return selectedTextColor; }
    void setSelectedTextColor(QColor selectedTextColor);

    void tabPixmap(int index, QImage& icon, QImage& iconSel);
    void setTabPixmap(int index, const QString& icon = QString(), const QString& iconSel = QString());

    //effected by drawbase
    QColor getBackgroundColor() const { return backgroundColor; }
    void setBackgroundColor(QColor backgroundColor);
protected:
    virtual void paintEvent(QPaintEvent*);
    virtual void drawBackground(QPainter* p);
    virtual void drawPicture(QPainter* p);
    virtual void drawText(QPainter* p);

public slots:

private:
    QList<TBtnIconTable> iconList;
    IconStyle iconStyle;
    QFont textFont;
    QColor textColor;
    QColor selectedTextColor;
    QColor backgroundColor;
};

#endif // QQTPICTUREEFFECTTABBAR_H
