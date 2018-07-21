#ifndef QQTDATEEDIT_H
#define QQTDATEEDIT_H

#include <QDateEdit>
#include <qqtcore.h>

#include <qqtcore.h>
#include <qqt-local.h>

class QQTSHARED_EXPORT QQtDateEdit : public QDateEdit
{
    Q_OBJECT
public:
    explicit QQtDateEdit ( QWidget* parent = nullptr );
    virtual ~QQtDateEdit() {}

    /*QQtInput不支持Qt默认的QDateEdit，QDateTimeEdit，QTimeEdit，QSpinBox，QDoubleSpinBox，必须使用这些个QQt继承下来的类*/
    /*Qt默认Protected，这个函数，在QQtInput要使用这个函数，所以在这里公开出来*/
    QLineEdit* lineEdit() const { return QDateEdit::lineEdit(); }
    void setLineEdit ( QLineEdit* edit ) { return QDateEdit::setLineEdit ( edit ); }

signals:

public slots:
};

#endif // QQTDATEEDIT_H
