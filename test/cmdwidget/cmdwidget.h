#ifndef CMDWIDGET_H
#define CMDWIDGET_H

#include <QWidget>

namespace Ui {
class CmdWidget;
}

class CmdWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CmdWidget(QWidget *parent = 0);
    ~CmdWidget();

private:
    Ui::CmdWidget *ui;
};

#endif // CMDWIDGET_H
