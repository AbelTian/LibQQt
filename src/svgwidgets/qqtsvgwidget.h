#ifndef QQTSVGWIDGET_H
#define QQTSVGWIDGET_H

#include <QSvgWidget>
#include <qqt-local.h>

class QQTSHARED_EXPORT QQtSvgWidget : public QSvgWidget
{
    Q_OBJECT
public:
    explicit QQtSvgWidget ( QWidget* parent = nullptr );
    explicit QQtSvgWidget ( const QString& file, QWidget* parent = nullptr );

    void setSvgFile ( QString& filename );
    void setSvgContent ( QByteArray& bytes );
signals:

public slots:
};

#endif // QQTSVGWIDGET_H
