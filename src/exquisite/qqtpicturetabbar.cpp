#include "qqtpicturetabbar.h"
#include "QStylePainter"
#include "QStyleOptionTabV3"
#include "QDebug"
#include "QPixmap"
#include "QApplication"
#include "QToolButton"
#include "qqtcore.h"

QQtPictureTabBar::QQtPictureTabBar ( QWidget* parent ) :
    QQtTabBar ( parent )
{
    setFocusPolicy ( Qt::NoFocus );
    iconStyle = IconStyle_Left_And_RightText;
    spacing = 0;
    textColor = QColor ( 0, 0, 0 );
    backgroundColor = QColor ( 0, 0, 0 );
    selectedTextColor = QColor ( 255, 255, 255 );
    textFont = QApplication::font();
    setDrawBase ( true );

    //不设置就获取，你图什么？
    dict1["image"].setType ( QQtDictionary::DictList );
    dict1["icon"].setType ( QQtDictionary::DictList );
}

void QQtPictureTabBar::setIconStyle ( QQtPictureTabBar::IconStyle iconStyle )
{
    if ( this->iconStyle != iconStyle )
    {
        this->iconStyle = iconStyle;
        update();
    }
}

void QQtPictureTabBar::setTextFont ( QFont textFont )
{
    if ( this->textFont != textFont )
    {
        this->textFont = textFont;
        update();
    }
}

void QQtPictureTabBar::setTextColor ( QColor textColor )
{
    if ( this->textColor != textColor )
    {
        this->textColor = textColor;
        update();
    }
}

void QQtPictureTabBar::setSelectedTextColor ( QColor selectedTextColor )
{
    if ( this->selectedTextColor != selectedTextColor )
    {
        this->selectedTextColor = selectedTextColor;
        update();
    }
}

void QQtPictureTabBar::tabPixmap ( int index, QImage& img, QImage& imgSel )
{
    if ( index < 0 || index + 1 > count() || index + 1 > dict1["image"].size() )
        return;

    img = QImage ( dict1["image"][index][BTN_NORMAL].getValue().toString() );
    imgSel = QImage ( dict1["image"][index][BTN_PRESS].getValue().toString() );

    return ;
}

void QQtPictureTabBar::setTabPixmap ( int index, const QString& img, const QString& imgSel )
{
    if ( index < 0 || index + 1 > count() )
        return;


    dict1["image"][index][BTN_NORMAL] = img;
    dict1["image"][index][BTN_PRESS] = imgSel;
}

void QQtPictureTabBar::tabIcon ( int index, QImage& icon, QImage& iconSel )
{
    if ( index < 0 || index + 1 > count() || index + 1 > dict1["icon"].size() )
        return;

    icon = QImage ( dict1["icon"][index][BTN_NORMAL].getValue().toString() );
    iconSel = QImage ( dict1["icon"][index][BTN_PRESS].getValue().toString() );
    //pline() << icon;
    //pline() << iconSel;

    return ;
}

void QQtPictureTabBar::setTabIcon ( int index, const QString& icon, const QString& iconSel )
{
    if ( index < 0 || index + 1 > count() )
        return;


    dict1["icon"][index][BTN_NORMAL] = icon;
    dict1["icon"][index][BTN_PRESS] = iconSel;

    //pline() << dict1["icon"][index][BTN_NORMAL];
    //pline() << dict1["icon"][index][BTN_PRESS];

}

void QQtPictureTabBar::setBackgroundColor ( QColor backgroundColor )
{
    if ( this->backgroundColor != backgroundColor )
    {
        this->backgroundColor = backgroundColor;
        update();
    }
}

void QQtPictureTabBar::paintEvent ( QPaintEvent* e )
{
    Q_UNUSED ( e )
    QPainter p ( this );
    drawBackground ( &p );
    drawIcon ( &p );
    drawText ( &p );
}

void QQtPictureTabBar::drawBackground ( QPainter* p )
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

void QQtPictureTabBar::drawPicture ( QPainter* p )
{
    for ( int index = 0; index < count(); index++ )
    {
        QRect tRect0 = tabRect ( index );

        if ( dict1["image"].size() > index )
        {
            p->save();
            int sel = currentIndex() == index ? BTN_PRESS : BTN_NORMAL;
#if 1
            //tabRect = rect()?
            p->drawPixmap ( tRect0, QIcon ( dict1["image"][index][sel].getValue().toString() ).pixmap ( tRect0.size(),
                            QIcon::Normal, QIcon::On ) );
#endif

            /*
             * 失真不明显，使用以下方法
             */
#if 0
            QImage image ( dict1["image"][index][sel].getValue().toString() );
            p.drawItemPixmap ( tabRectValue, Qt::AlignLeft | Qt::AlignTop, QPixmap::fromImage ( image.scaled ( tabRectValue.size(),
                               Qt::KeepAspectRatio ) ) );
#endif

            //需要QStylePainter支援
            //为什么不用这个呢?因为上边那个QIcon直接缩放到了完整的符合Icon大小的图.直接居中.
            //这个不需要,多次一举.
#if 0
            p->drawItemPixmap ( tRect0, Qt::AlignCenter,
                                QIcon ( dict1["image"][index][sel].getValue().toString() ).pixmap ( tRect0.size(), QIcon::Normal,
                                        QIcon::On )  );
#endif
            p->restore();
        }
    }
}

void QQtPictureTabBar::drawColor ( QPainter* p )
{
    for ( int index = 0; index < count(); index++ )
    {
        p->save();
        p->setBrush ( QBrush ( backgroundColor ) );

        QRect tRect0 = tabRect ( index );

        p->fillRect ( tRect0, backgroundColor );
        p->restore();
    }
}

void QQtPictureTabBar::drawIcon ( QPainter* p )
{
    if ( iconStyle == IconStyle_MiddleText )
        return;

    for ( int index = 0; index < count(); index++ )
    {
        QRect tRect0 = tabRect ( index );

        /*
         * 适配contentMargin
         */
        tRect0.adjust ( contentsMargins().left(),
                        contentsMargins().top(),
                        -contentsMargins().right(),
                        -contentsMargins().bottom() );
        /*
         * 适配图片的上下左右
         */
        int x = ( tRect0.width() - iconSize().width() ) / 2;
        int y = ( tRect0.height() - iconSize().height() ) / 2;

        if ( iconStyle == IconStyle_Top_And_BottomText )
            tRect0 = QRect ( tRect0.left() + x,
                             tRect0.top(),
                             iconSize().width(),
                             iconSize().height() );
        else if ( iconStyle == IconStyle_Bottom_And_TopText )
            tRect0 = QRect ( tRect0.left() + x,
                             tRect0.bottom() - iconSize().height(),
                             iconSize().width(),
                             iconSize().height() );
        else if ( iconStyle == IconStyle_Right_And_LeftText )
            tRect0 = QRect ( tRect0.right() - iconSize().width(),
                             tRect0.top() + y,
                             iconSize().width(),
                             iconSize().height() );
        else if ( iconStyle == IconStyle_Left_And_RightText )
            tRect0 = QRect ( tRect0.left(),
                             tRect0.top() + y,
                             iconSize().width(),
                             iconSize().height() );

        QIcon::Mode mode = QIcon::Normal;

        /*这个效果没法看*/
        if ( currentIndex() == index )
        {
            ;//mode = QIcon::Selected;
        }

        int sel = BTN_NORMAL;
        sel = currentIndex() == index ? BTN_PRESS : BTN_NORMAL;

        //pline() << dict1["icon"].size() << index << dict1["icon"][index][sel].getValue().toString();

        if ( dict1["icon"].size() > index )
        {
            p->save();
            //tabRect = rect()?
            p->drawPixmap ( tRect0, QIcon ( dict1["icon"][index][sel].getValue().toString() ).pixmap ( tRect0.size(), mode,
                            QIcon::On ) );
            /*
             * 失真不明显，使用以下方法
             */
            //QImage image(dict1["icon"][index][sel].getValue().toString());
            //p.drawItemPixmap(tabRectValue, Qt::AlignLeft |Qt::AlignTop, QPixmap::fromImage(image.scaled(tabRectValue.size(), Qt::KeepAspectRatio)));
            p->restore();
        }
    }
}

void QQtPictureTabBar::drawText ( QPainter* p )
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
                             tRect0.top() + iconSize().height() + spacing,
                             tRect0.width(),
                             tRect0.height() - ( iconSize().height() + spacing ) );
        }
        else if ( iconStyle == IconStyle_Bottom_And_TopText )
        {
            tRect0 = QRect ( tRect0.left(),
                             tRect0.top(),
                             tRect0.width(),
                             tRect0.height() - ( iconSize().height() + spacing ) );
        }
        else if ( iconStyle == IconStyle_Right_And_LeftText )
        {
            tRect0 = QRect ( tRect0.left(),
                             tRect0.top(),
                             tRect0.width() - ( iconSize().width() + spacing ),
                             tRect0.height() );
        }
        else if ( iconStyle == IconStyle_Left_And_RightText )
        {
            tRect0 = QRect ( tRect0.left() + ( iconSize().width() + spacing ),
                             tRect0.top(),
                             tRect0.width() - ( iconSize().width() + spacing ),
                             tRect0.height() );
        }

        int flags = Qt::AlignCenter;

        if ( iconStyle == IconStyle_Top_And_BottomText )
            flags = Qt::AlignHCenter | Qt::AlignVCenter;
        else if ( iconStyle == IconStyle_Bottom_And_TopText )
            flags = Qt::AlignHCenter | Qt::AlignVCenter;
        else if ( iconStyle == IconStyle_Right_And_LeftText )
            flags = Qt::AlignVCenter | Qt::AlignHCenter;
        else if ( iconStyle == IconStyle_Left_And_RightText )
            flags = Qt::AlignVCenter | Qt::AlignHCenter;
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
