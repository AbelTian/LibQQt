#ifndef QQTTABBAR_H
#define QQTTABBAR_H

#include <QTabBar>
#include <QList>
#include <QColor>
#include "qqtcore.h"
#include "qqtwidgets.h"
#include "qqt-local.h"

class QQTSHARED_EXPORT QQtTabBar : public QTabBar
{
    Q_OBJECT

public:
    explicit QQtTabBar(QWidget* parent = 0);

    enum IconStyle
    {
        IconStyle_Cover_And_BottomText,
        IconStyle_Left_And_RightText,
        IconStyle_Max_Style
    };

    IconStyle getIconStyle() const { return iconStyle; }
    void setIconStyle(IconStyle iconStyle);

    void tabPixmap(int index, QImage& icon, QImage& iconSel);
    void setTabPixmap(int index, const QString& icon = QString(), const QString& iconSel = QString());

protected:
    void paintEvent(QPaintEvent*);

private:
    inline bool verticalTabs();

public slots:

private:
    QList<TBtnIconTable> iconList;
    IconStyle iconStyle;
};

#endif // QQTTABBAR_H
