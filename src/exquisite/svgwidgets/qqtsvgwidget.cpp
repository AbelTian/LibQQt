#include "qqtsvgwidget.h"
#include <QPainter>
#include <QSvgRenderer>
#include <QImage>
#include <QIcon>

QQtSvgWidget::QQtSvgWidget ( QWidget* parent ) : QSvgWidget ( parent )
{

}

QQtSvgWidget::QQtSvgWidget ( const QString& file, QWidget* parent ) :
    QSvgWidget ( file, parent )
{

}

void QQtSvgWidget::setSvgFile ( QString& filename )
{
    return load ( filename );
}

void QQtSvgWidget::setSvgContent ( QByteArray& bytes )
{
    return load ( bytes );
}
