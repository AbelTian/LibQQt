#ifndef QQTDATETIMEEDIT_H
#define QQTDATETIMEEDIT_H

#include <QDateTimeEdit>

class QQtDateTimeEdit : public QDateTimeEdit
{
    Q_OBJECT
public:
    explicit QQtDateTimeEdit ( QWidget* parent = nullptr );
    virtual ~QQtDateTimeEdit() {}

    QLineEdit* lineEdit() const { return QDateTimeEdit::lineEdit(); }
    void setLineEdit ( QLineEdit* edit ) { return QDateTimeEdit::setLineEdit ( edit ); }

signals:

public slots:
};

#endif // QQTDATETIMEEDIT_H
