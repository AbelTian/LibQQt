#include "qqtgifcheckbox.h"

QQtGifCheckBox::QQtGifCheckBox ( QWidget* parent ) : QQtCheckBox ( parent )
{

}

QString QQtGifCheckBox::stateImage ( int index )
{
    if ( index < BTN_NORMAL || index > BTN_MAX - 1 )
        return mIconTable[BTN_NORMAL];
    return mIconTable[index];
}

void QQtGifCheckBox::setStateImage ( int index, const QString& image )
{
    if ( index < BTN_NORMAL || index > BTN_MAX - 1 )
        return;
    mIconTable[index] = image;
    translateImage();
    update();
}

void QQtGifCheckBox::setNormalImage ( const QString& normal, const QString& press )
{
    mIconTable[BTN_NORMAL] = normal;
    mIconTable[BTN_PRESS] = press;
    translateImage();
    update();
}

void QQtGifCheckBox::setHoverImage ( const QString& hover )
{
    mIconTable[BTN_HOVER] = hover;
    translateImage();
    update();
}

void QQtGifCheckBox::setDisableImage ( const QString& disable )
{
    mIconTable[BTN_DISABLE] = disable;
    translateImage();
    update();
}

const TBtnIconTable& QQtGifCheckBox::iconTable() const
{
    return mIconTable;
}

TBtnIconTable& QQtGifCheckBox::iconTable()
{
    return mIconTable;
}

void QQtGifCheckBox::renderToVariable()
{
    TBtnIconTable& pic = iconTable();
}

void QQtGifCheckBox::translateImage()
{
    renderToVariable();
}

void QQtGifCheckBox::slotFramePlayback()
{
    //把movie的图片设置到mImage。
    setImage ( m_movie->currentImage() );
}
