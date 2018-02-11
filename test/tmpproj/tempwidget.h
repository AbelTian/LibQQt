#ifndef TEMPWIDGET_H
#define TEMPWIDGET_H

#include <QWidget>

namespace Ui {
class TempWidget;
}

class TempWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TempWidget(QWidget *parent = 0);
    ~TempWidget();

private:
    Ui::TempWidget *ui;
};

#endif // TEMPWIDGET_H
