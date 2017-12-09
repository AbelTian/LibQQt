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
    explicit QQtPictureEffectTabBar ( QWidget* parent = 0 );

    enum IconStyle
    {
        //picture style
        IconStyle_Top_And_BottomText,
        IconStyle_Bottom_And_TopText,
        IconStyle_Left_And_RightText,
        IconStyle_Right_And_LeftText,
        IconStyle_MiddleText,

        //color style
        ColorStyle_Left_And_RightText,

        IconStyle_Max_Style
    };

    /*TabBar的风格*/
    IconStyle getIconStyle() const { return iconStyle; }
    void setIconStyle ( IconStyle iconStyle );

    /*背景部分 使用颜色*/
    //effected by drawbase
    QColor getBackgroundColor() const { return backgroundColor; }
    void setBackgroundColor ( QColor backgroundColor );

    /*背景部分 使用图片*/
    void tabPixmap ( int index, QImage& img, QImage& imgSel );
    void setTabPixmap ( int index, const QString& img = QString(),
                        const QString& imgSel = QString() );

    /*Icon部分*/
    void tabIcon ( int index, QImage& icon, QImage& iconSel );
    void setTabIcon ( int index, const QString& icon = QString(),
                      const QString& iconSel = QString() );

    /*文字部分*/
    QFont getTextFont() const { return textFont; }
    void setTextFont ( QFont textFont );
    QColor getTextColor() const { return textColor; }
    void setTextColor ( QColor textColor );
    QColor getSelectedTextColor() const { return selectedTextColor; }
    void setSelectedTextColor ( QColor selectedTextColor );

protected:
    virtual void paintEvent ( QPaintEvent* );
    virtual void drawBackground ( QPainter* p );
    virtual void drawPicture ( QPainter* p );
    virtual void drawIcon ( QPainter* p );
    virtual void drawText ( QPainter* p );

public slots:

private:
    QList<TBtnIconTable> imgList;
    QList<TBtnIconTable> iconList;
    IconStyle iconStyle;
    QFont textFont;
    QColor textColor;
    QColor selectedTextColor;
    QColor backgroundColor;
};

#endif // QQTPICTUREEFFECTTABBAR_H
