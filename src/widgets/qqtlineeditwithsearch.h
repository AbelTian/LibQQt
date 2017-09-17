#ifndef QSEARCHLINEEDIT_H
#define QSEARCHLINEEDIT_H

#include <QLineEdit>
#include <QPushButton>
#include <qqt-local.h>

class QQTSHARED_EXPORT QQTLineEditWithSearch : public QLineEdit
{
    Q_OBJECT
public:
    explicit QQTLineEditWithSearch(QWidget *parent = 0);
    void setButtonText(QString text);
    void setObjectName(const QString &name);

signals:
    void btnClicked();

public slots:

private:
    QPushButton* m_btnBrower;

    // QObject interface
};

#endif // QSEARCHLINEEDIT_H
