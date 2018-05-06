#ifndef QQTCOLORWIDGET_H
#define QQTCOLORWIDGET_H

#include <QWidget>

class QQtColorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QQtColorWidget ( QWidget* parent = nullptr );

    void setColor ( const QRgb& rgb );

    QRgb getColor();

signals:

public slots:
private:
    QRgb mRgb;
};

#endif // QQTCOLORWIDGET_H
