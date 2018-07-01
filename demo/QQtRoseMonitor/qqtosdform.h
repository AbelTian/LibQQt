#ifndef QQTOSDFORM_H
#define QQTOSDFORM_H

#include <QQtWidget>

namespace Ui {
class QQtOsdForm;
}

class QQtOsdForm : public QQtWidget
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

    // QWidget interface
protected:
    virtual void mousePressEvent ( QMouseEvent* event ) override;
};

#endif // QQTOSDFORM_H
