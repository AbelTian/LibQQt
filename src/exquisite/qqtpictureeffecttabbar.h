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
        /*
         * 依赖iconSize，layoutSpacing设置图片位置
         */
        //picture style
        IconStyle_Top_And_BottomText,
        IconStyle_Bottom_And_TopText,
        /*
         * 依赖iconSize，layoutSpacing设置图片位置
         */
        IconStyle_Left_And_RightText,
        IconStyle_Right_And_LeftText,
        IconStyle_MiddleText,

        //color style
        ColorStyle_Left_And_RightText,

        IconStyle_Max_Style
    };

    /*
     * 设置x方向、y方向的layout间距。
     */
    void setLayoutSpacing(int spacing = 0) { this->spacing = spacing; }
    //setContentsMargins(left, top, right, bottom); is a gool idea.

    /*TabBar的风格*/
    IconStyle getIconStyle() const { return iconStyle; }
    void setIconStyle ( IconStyle iconStyle );

    /*背景部分，这里设置的是Tab的背景图*/
    /*使用颜色*/
    QColor getBackgroundColor() const { return backgroundColor; }
    void setBackgroundColor ( QColor backgroundColor );//effected by drawbase
    /*使用图片*/
    void tabPixmap ( int index, QImage& img, QImage& imgSel );
    void setTabPixmap ( int index, const QString& img = QString(),
                        const QString& imgSel = QString() );

    /*Icon部分，这里设置的是Tab里的Icon*/
    void tabIcon ( int index, QImage& icon, QImage& iconSel );
    void setTabIcon ( int index, const QString& icon = QString(),
                      const QString& iconSel = QString() );

    /*文字部分，这里设置的是Tab里显示的文字*/
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
    virtual void drawColor ( QPainter* p );
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
    int spacing;
};

#endif // QQTPICTUREEFFECTTABBAR_H
