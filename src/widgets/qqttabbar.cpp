#include "qqttabbar.h"
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
}

bool QQtTabBar::verticalTabs()
{
    return shape() == QTabBar::RoundedWest
           || shape() == QTabBar::RoundedEast
           || shape() == QTabBar::TriangularWest
           || shape() == QTabBar::TriangularEast;
}
