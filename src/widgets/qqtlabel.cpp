#include "qqtlabel.h"

QQtLabel::QQtLabel(QWidget* parent) : QLabel(parent)
{

}


void QQtLabel::mouseReleaseEvent(QMouseEvent* event)
{
    emit click();
    return QLabel::mouseReleaseEvent(event);
}


void QQtLabel::mouseDoubleClickEvent(QMouseEvent* event)
{
    emit doubleClick();
    return QLabel::mouseDoubleClickEvent(event);
}
