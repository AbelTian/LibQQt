#ifndef RLINEEDIT_H
#define RLINEEDIT_H

#include <QLineEdit>

class RLineEdit : public QLineEdit
{
public:
    explicit RLineEdit(QWidget* parent=0);

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *) override;
    void focusOutEvent(QFocusEvent *) override;
};

#endif // RLINEEDIT_H
