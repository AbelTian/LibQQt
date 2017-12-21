#ifndef QQTDATEEDIT_H
#define QQTDATEEDIT_H

#include <QDateEdit>

class QQtDateEdit : public QDateEdit
{
    Q_OBJECT
public:
    explicit QQtDateEdit ( QWidget* parent = nullptr );
    virtual ~QQtDateEdit() {}

    QLineEdit* lineEdit() const { return QDateEdit::lineEdit(); }
    void setLineEdit ( QLineEdit* edit ) { return QDateEdit::setLineEdit ( edit ); }

signals:

public slots:
};

#endif // QQTDATEEDIT_H
