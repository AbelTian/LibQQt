#include "qqtsvgwidget.h"

QQtSvgWidget::QQtSvgWidget(QWidget* parent) : QSvgWidget(parent)
{

}

void QQtSvgWidget::setSvgFile(QString& filename)
{
    return load(filename);
}

void QQtSvgWidget::setSvgContent(QByteArray& bytes)
{
    return load(bytes);
}
