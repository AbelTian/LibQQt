#ifndef QQTDATETIMEEDIT_H
#define QQTDATETIMEEDIT_H

#include <QDateTimeEdit>
#include <qqtcore.h>
#include <qqtcore.h>
#include <qqt-local.h>

class QQTSHARED_EXPORT QQtDateTimeEdit : public QDateTimeEdit
{
    Q_OBJECT
public:
    explicit QQtDateTimeEdit ( QWidget* parent = nullptr );
    virtual ~QQtDateTimeEdit() {}

    /*QQtInput不支持Qt默认的QDateEdit，QDateTimeEdit，QTimeEdit，QSpinBox，QDoubleSpinBox，必须使用这些个QQt继承下来的类*/
    /*Qt默认Protected，这个函数，在QQtInput要使用这个函数，所以在这里公开出来*/
    QLineEdit* lineEdit() const { return QDateTimeEdit::lineEdit(); }
    void setLineEdit ( QLineEdit* edit ) { return QDateTimeEdit::setLineEdit ( edit ); }

signals:

public slots:
};

#endif // QQTDATETIMEEDIT_H
