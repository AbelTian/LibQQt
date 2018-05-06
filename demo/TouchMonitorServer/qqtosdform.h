#ifndef QQTOSDFORM_H
#define QQTOSDFORM_H

#include <QWidget>

namespace Ui {
class QQtOsdForm;
}

class QQtOsdForm : public QWidget
{
    Q_OBJECT

public:
    explicit QQtOsdForm ( QWidget* parent = 0 );
    ~QQtOsdForm();

private:
    Ui::QQtOsdForm* ui;

    // QWidget interface
protected:
    virtual void paintEvent ( QPaintEvent* event ) override;
};

#endif // QQTOSDFORM_H
