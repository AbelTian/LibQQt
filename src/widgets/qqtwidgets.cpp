#include "qqtwidgets.h"


tagBtnIconTable::tagBtnIconTable()
{
    pixmap[BTN_NORMAL] = "./skin/default/bt_bt_normal.png";
    pixmap[BTN_UNCHECK] = "./skin/default/bt_bt_normal.png";
#ifdef __EMBEDDED_LINUX__
    pixmap[BTN_HOVER] = "./skin/default/bt_bt_hover.png";
    pixmap[BTN_CHECK] = "./skin/default/bt_bt_hover.png";
    pixmap[BTN_PRESS] = "./skin/default/bt_bt_hover.png";
#else
    pixmap[BTN_HOVER] = "./skin/default/bt_bt_hover.png";
    pixmap[BTN_CHECK] = "./skin/default/bt_bt_check.png";
    pixmap[BTN_PRESS] = "./skin/default/bt_bt_press.png";
#endif
    pixmap[BTN_DISABLE] = "./skin/default/bt_bt_disable.png";
}

QString tagBtnIconTable::pixMap(int index)
{
    if (index < 0 || index + 1 > BTN_MAX)
        return pixmap[BTN_NORMAL];
    return pixmap[index];
}

void tagBtnIconTable::setPixMap(int index, QString pix)
{
    if (index < 0 || index + 1 > BTN_MAX)
        return;
    pixmap[index] = pix;
}

void tagBtnIconTable::initNormal(QString normal, QString press)
{
    if (!normal.isEmpty())
        pixmap[BTN_NORMAL] = normal;
    if (!press.isEmpty())
        pixmap[BTN_PRESS] = press;
}

void tagBtnIconTable::initCheck(QString uncheck, QString check)
{
    if (!uncheck.isEmpty())
        pixmap[BTN_UNCHECK] = uncheck;
    if (!check.isEmpty())
        pixmap[BTN_CHECK] = check;
}

void tagBtnIconTable::initOther(QString hover, QString disable)
{
    if (!hover.isEmpty())
        pixmap[BTN_HOVER] = hover;
    if (!disable.isEmpty())
        pixmap[BTN_DISABLE] = disable;
}

QString& tagBtnIconTable::operator [](int index)
{
    if (index < 0 || index >= BTN_MAX)
        return pixmap[0];

    return pixmap[index];
}

const QString& tagBtnIconTable::operator[](int index) const
{
    if (index < 0 || index >= BTN_MAX)
        return pixmap[0];

    return pixmap[index];
}


void moveCenter(QWidget* w)
{
    int x1 = 0, y1 = 0;

    x1 = (QApplication::desktop()->availableGeometry().width()
          - w->width()) / 2;
    y1 = (QApplication::desktop()->availableGeometry().height()
          - w->height()) / 2;


    w->move(x1, y1);

    return;
}


void moveRight(QWidget* w)
{
    w->move((QApplication::desktop()->width() - w->width()), 0);
}


