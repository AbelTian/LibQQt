#ifndef QQTPICTURETABBAR_H
#define QQTPICTURETABBAR_H

#include <QTabBar>
#include <QList>
#include <QColor>
#include "qqtcore.h"
#include "qqtwidgets.h"
#include "qqttabbar.h"
#include "qqt-local.h"
#include "qqtdictionary.h"

/**
 * @brief The QQtPictureTabBar class
 * 使用图片的tabbar，支持竖向和横向。
 * 图片和文字，支持多种排布格式。
 * 竖向tabbar的文字是横向的。
 */
class QQTSHARED_EXPORT QQtPictureTabBar : public QQtTabBar
{
    Q_OBJECT

public:
    explicit QQtPictureTabBar ( QWidget* parent = 0 );

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
        //default
        IconStyle_Left_And_RightText,
        IconStyle_Right_And_LeftText,
        IconStyle_MiddleText,

        //color style
        ColorStyle_Left_And_RightText,

        IconStyle_Max_Style
    };

    /*
     * 设置x方向、y方向的layout间距。
     * setContentsMargins(left, top, right, bottom); is a gool idea.
     */
    void setLayoutSpacing ( int spacing = 0 ) { this->spacing = spacing; }

    /*TabBar的风格*/
    IconStyle getIconStyle() const { return iconStyle; }
    void setIconStyle ( IconStyle iconStyle );

    /**
     * 背景部分，这里设置的是Tab的背景图
     */
    /*使用颜色*/
    QColor getBackgroundColor() const { return backgroundColor; }
    void setBackgroundColor ( QColor backgroundColor );//effected by drawbase
    /*使用图片*/
    void tabPixmap ( int index, QImage& img, QImage& imgSel );
    void setTabPixmap ( int index, const QString& img = QString(),
                        const QString& imgSel = QString() );

    /**
     * Icon部分，这里设置的是Tab里的Icon
     * 不设置背景则显示icon
     */
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
    QQtDictionary dict1;
    IconStyle iconStyle;
    QFont textFont;
    QColor textColor;
    QColor selectedTextColor;
    QColor backgroundColor;
    int spacing;
};

#endif // QQTPICTURETABBAR_H
