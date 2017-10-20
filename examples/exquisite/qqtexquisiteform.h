#ifndef QQTEXQUISITEFORM_H
#define QQTEXQUISITEFORM_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class QQtExquisiteForm;
}

class QQtExquisiteForm : public QDialog
{
    Q_OBJECT

public:
    explicit QQtExquisiteForm(QWidget *parent = 0);
    ~QQtExquisiteForm();

private slots:
    void setValue(int);
    void setValue();
    void setValueDown();
private:
    Ui::QQtExquisiteForm *ui;
    QTimer* m_timer ;
    QTimer* m_t1 ;
    int value;

    // QWidget interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // QQTEXQUISITEFORM_H
