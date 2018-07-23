#ifndef QQTCOLORWIDGET_H
#define QQTCOLORWIDGET_H

#include <QWidget>

#include <qqt-local.h>
#include <qqtcore.h>

class QQTSHARED_EXPORT QQtColorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QQtColorWidget ( QWidget* parent = nullptr );
    virtual ~QQtColorWidget() {}

    void setColor ( const QRgb& rgb );

    QRgb getColor();

signals:

public slots:
private:
    QRgb mRgb;

    // QWidget interface
protected:
    virtual void paintEvent ( QPaintEvent* event ) override;
};

#endif // QQTCOLORWIDGET_H
