#ifndef FRAMELESSFORM_H
#define FRAMELESSFORM_H

#include <QWidget>

namespace Ui {
class FramelessForm;
}

//测试framelesshelper，即将废弃。
class FramelessForm : public QWidget
{
    Q_OBJECT

public:
    explicit FramelessForm ( QWidget* parent = 0 );
    ~FramelessForm();

private:
    Ui::FramelessForm* ui;
};

#endif // FRAMELESSFORM_H
