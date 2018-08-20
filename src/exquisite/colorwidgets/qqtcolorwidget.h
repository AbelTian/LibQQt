#ifndef QQTCOLORWIDGET_H
#define QQTCOLORWIDGET_H

#include <QWidget>

#include <qqt-local.h>
#include <qqtcore.h>

/**
 * @brief The QQtColorWidget class
 * 实现思路: styleSheet, palette, paintEvent三个选择一个.
 */
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
