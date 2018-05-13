#ifndef QQTDOUBLESPINBOX_H
#define QQTDOUBLESPINBOX_H

#include <QDoubleSpinBox>
#include <qqtcore.h>

class QQtDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    explicit QQtDoubleSpinBox ( QWidget* parent = nullptr );
    virtual ~QQtDoubleSpinBox() {}

    QLineEdit* lineEdit() const { return QDoubleSpinBox::lineEdit(); }
    void setLineEdit ( QLineEdit* edit ) { return QDoubleSpinBox::setLineEdit ( edit ); }

signals:

public slots:
};

#endif // QQTDOUBLESPINBOX_H
