#ifndef QQTSPINBOX_H
#define QQTSPINBOX_H

#include <QSpinBox>
#include <qqtcore.h>
#include <qqtcore.h>
#include <qqt-local.h>

class QQTSHARED_EXPORT QQtSpinBox : public QSpinBox
{
    Q_OBJECT
public:
    explicit QQtSpinBox ( QWidget* parent = nullptr );
    virtual ~QQtSpinBox() {}

    QLineEdit* lineEdit() const { return QSpinBox::lineEdit(); }
    void setLineEdit ( QLineEdit* edit ) { return QSpinBox::setLineEdit ( edit ); }

signals:

public slots:
};

#endif // QQTSPINBOX_H
