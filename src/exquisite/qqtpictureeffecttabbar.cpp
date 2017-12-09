#include "qqtpictureeffecttabbar.h"
#include "QStylePainter"
#include "QStyleOptionTabV3"
#include "QDebug"
#include "QPixmap"
#include "QApplication"
#include "QToolButton"
#include "qqtcore.h"

QQtPictureEffectTabBar::QQtPictureEffectTabBar ( QWidget* parent ) :
    QQtTabBar ( parent )
{
    setFocusPolicy ( Qt::NoFocus );
    iconStyle = IconStyle_Left_And_RightText;
    textColor = QColor ( 0, 0, 0 );
    backgroundColor = QColor ( 0, 0, 0 );
    selectedTextColor = QColor ( 255, 255, 255 );
    textFont = QApplication::font();
    setDrawBase ( true );
}

void QQtPictureEffectTabBar::setIconStyle ( QQtPictureEffectTabBar::IconStyle iconStyle )
{
    if ( this->iconStyle != iconStyle )
    {
        this->iconStyle = iconStyle;
        update();
    }
}

void QQtPictureEffectTabBar::setTextFont ( QFont textFont )
{
    if ( this->textFont != textFont )
    {
        this->textFont = textFont;
        update();
    }
}

void QQtPictureEffectTabBar::setTextColor ( QColor textColor )
{
    if ( this->textColor != textColor )
    {
        this->textColor = textColor;
        update();
    }
}

void QQtPictureEffectTabBar::setSelectedTextColor ( QColor selectedTextColor )
{
    if ( this->selectedTextColor != selectedTextColor )
    {
        this->selectedTextColor = selectedTextColor;
        update();
    }
}

void QQtPictureEffectTabBar::tabPixmap ( int index, QImage& img, QImage& imgSel )
{
    if ( index < 0 || index + 1 > count() || index + 1 > imgList.size() )
        return;

    img = QImage ( imgList[index][BTN_NORMAL] );
    imgSel = QImage ( imgList[index][BTN_PRESS] );

    return ;
}

void QQtPictureEffectTabBar::setTabPixmap ( int index, const QString& img, const QString& imgSel )
{
    if ( index < 0 || index + 1 > count() )
        return;

    TBtnIconTable table;
    table[BTN_NORMAL] = img;
    table[BTN_PRESS] = imgSel;

    imgList.insert ( index, table );
}

void QQtPictureEffectTabBar::tabIcon ( int index, QImage& icon, QImage& iconSel )
{
    if ( index < 0 || index + 1 > count() || index + 1 > imgList.size() )
        return;

    icon = QImage ( iconList[index][BTN_NORMAL] );
    iconSel = QImage ( iconList[index][BTN_PRESS] );

    return ;
}

void QQtPictureEffectTabBar::setTabIcon ( int index, const QString& icon, const QString& iconSel )
{
    if ( index < 0 || index + 1 > count() )
        return;

    TBtnIconTable table;
    table[BTN_NORMAL] = icon;
    table[BTN_PRESS] = iconSel;

    iconList.insert ( index, table );
}

void QQtPictureEffectTabBar::setBackgroundColor ( QColor backgroundColor )
{
    if ( this->backgroundColor != backgroundColor )
    {
        this->backgroundColor = backgroundColor;
        update();
    }
}

void QQtPictureEffectTabBar::paintEvent ( QPaintEvent* e )
{
    Q_UNUSED ( e )
    QPainter p ( this );
    drawBackground ( &p );
    drawIcon ( &p );
    drawText ( &p );
}

void QQtPictureEffectTabBar::drawBackground ( QPainter* p )
{
    bool b = drawBase();

    /*setDrawBase(True)启动ColorStyle*/
    if ( !b )
        return;

    switch ( iconStyle )
    {
    case IconStyle_Top_And_BottomText:
    case IconStyle_Bottom_And_TopText:
    case IconStyle_Left_And_RightText:
    case IconStyle_Right_And_LeftText:
    case IconStyle_MiddleText:
        drawPicture ( p );
        break;

    case ColorStyle_Left_And_RightText:
        drawColor ( p );
        break;

    case IconStyle_Max_Style:
    default:
        break;
    }
}

void QQtPictureEffectTabBar::drawPicture ( QPainter* p )
{
    for ( int index = 0; index < count(); index++ )
    {
        QRect tRect0 = tabRect ( index );

        tRect0.adjust ( contentsMargins().left(),
                        contentsMargins().top(),
                        -contentsMargins().right(),
                        -contentsMargins().bottom() );

        if ( imgList.size() > index )
        {
            p->save();
            int sel = currentIndex() == index ? BTN_PRESS : BTN_NORMAL;
            //tabRect = rect()?
            p->drawPixmap ( tRect0, QIcon ( imgList[index][sel] ).pixmap ( tRect0.size(), QIcon::Normal, QIcon::On ) );
            /*
             * 失真不明显，使用以下方法
             */
            //QImage image(iconList[index][sel]);
            //p.drawItemPixmap(tabRectValue, Qt::AlignLeft |Qt::AlignTop, QPixmap::fromImage(image.scaled(tabRectValue.size(), Qt::KeepAspectRatio)));
            p->restore();
        }
    }
}

void QQtPictureEffectTabBar::drawColor ( QPainter* p )
{
    for ( int index = 0; index < count(); index++ )
    {
        p->save();
        p->setBrush ( QBrush ( backgroundColor ) );

        QRect tRect0 = tabRect ( index );
        tRect0.adjust ( contentsMargins().left(),
                        contentsMargins().top(),
                        -contentsMargins().right(),
                        -contentsMargins().bottom() );

        p->fillRect ( tRect0, backgroundColor );
        p->restore();
    }
}

void QQtPictureEffectTabBar::drawIcon ( QPainter* p )
{
    if ( iconStyle == IconStyle_MiddleText )
        return;

    for ( int index = 0; index < count(); index++ )
    {
        QRect tRect0 = tabRect ( index );

        tRect0.adjust ( contentsMargins().left(),
                        contentsMargins().top(),
                        -contentsMargins().right(),
                        -contentsMargins().bottom() );

        if ( iconStyle == IconStyle_Top_And_BottomText )
            tRect0 = QRect ( tRect0.left(), tRect0.top(),
                             tRect0.width(), tRect0.width() );
        else if ( iconStyle == IconStyle_Bottom_And_TopText )
            tRect0 = QRect ( tRect0.left(),
                             tRect0.bottom() - tRect0.width(),
                             tRect0.width(),
                             tRect0.width() );
        else if ( iconStyle == IconStyle_Right_And_LeftText )
            tRect0 = QRect ( tRect0.right() - tRect0.height(),
                             tRect0.top(),
                             tRect0.height(),
                             tRect0.height() );
        else if ( iconStyle == IconStyle_Left_And_RightText )
            tRect0 = QRect ( tRect0.left(), tRect0.top(),
                             tRect0.height(), tRect0.height() );

        QIcon::Mode mode = QIcon::Normal;

        /*这个效果没法看*/
        if ( currentIndex() == index )
            ;//mode = QIcon::Selected;

        if ( iconList.size() > index )
        {
            p->save();
            int sel = currentIndex() == index ? BTN_PRESS : BTN_NORMAL;
            //tabRect = rect()?
            p->drawPixmap ( tRect0, QIcon ( iconList[index][sel] ).pixmap ( tRect0.size(), mode, QIcon::On ) );
            /*
             * 失真不明显，使用以下方法
             */
            //QImage image(iconList[index][sel]);
            //p.drawItemPixmap(tabRectValue, Qt::AlignLeft |Qt::AlignTop, QPixmap::fromImage(image.scaled(tabRectValue.size(), Qt::KeepAspectRatio)));
            p->restore();
        }
    }
}

void QQtPictureEffectTabBar::drawText ( QPainter* p )
{
    for ( int index = 0; index < count(); index++ )
    {
        QRect tRect0 = tabRect ( index );

        tRect0.adjust ( contentsMargins().left(),
                        contentsMargins().top(),
                        -contentsMargins().right(),
                        -contentsMargins().bottom() );

        //-rect.height()/20 上移
        verticalTabs() ? tRect0.adjust ( 0, 0, 0, 0 ) : tRect0.adjust ( 0, 0, 0, 0 );

        if ( iconStyle == IconStyle_Top_And_BottomText )
        {
            tRect0 = QRect ( tRect0.left(),
                             tRect0.top() + tRect0.width(),
                             tRect0.width(),
                             tRect0.height() - tRect0.width() );
        }
        else if ( iconStyle == IconStyle_Bottom_And_TopText )
        {
            tRect0 = QRect ( tRect0.left(),
                             tRect0.top(),
                             tRect0.width(),
                             tRect0.height() - tRect0.width() );
        }
        else if ( iconStyle == IconStyle_Right_And_LeftText )
        {
            tRect0 = QRect ( tRect0.left(),
                             tRect0.top(),
                             tRect0.width() - tRect0.height(),
                             tRect0.height() );
        }
        else if ( iconStyle == IconStyle_Left_And_RightText )
        {
            tRect0 = QRect ( tRect0.left() + tRect0.height(),
                             tRect0.top(),
                             tRect0.width() - tRect0.height(),
                             tRect0.height() );
        }

        int flags = Qt::AlignCenter;

        if ( iconStyle == IconStyle_Top_And_BottomText )
            flags = Qt::AlignHCenter | Qt::AlignBottom;
        else if ( iconStyle == IconStyle_Bottom_And_TopText )
            flags = Qt::AlignHCenter | Qt::AlignTop;
        else if ( iconStyle == IconStyle_Right_And_LeftText )
            flags = Qt::AlignVCenter | Qt::AlignLeft;
        else if ( iconStyle == IconStyle_Left_And_RightText )
            flags = Qt::AlignVCenter | Qt::AlignRight;
        else if ( iconStyle == IconStyle_MiddleText )
            flags = Qt::AlignVCenter | Qt::AlignHCenter;

        //pline() << objectName() << rect;
        //if on board text is normal, this is right. otherwise the palette is right
        p->save();
        p->setFont ( textFont );

        if ( index == currentIndex() )
            p->setPen ( selectedTextColor );
        else
            p->setPen ( textColor );

        p->drawText ( tRect0, flags, tabText ( index ) );
        p->restore();
    }
}
