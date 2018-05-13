#ifndef QSEARCHLINEEDIT_H
#define QSEARCHLINEEDIT_H

#include <QLineEdit>
#include <QPushButton>
#include <qqt-local.h>

class QQTSHARED_EXPORT QQtLineEditWithSearch : public QLineEdit
{
    Q_OBJECT
public:
    explicit QQtLineEditWithSearch ( QWidget* parent = 0 );
    void setButtonText ( QString text );
    void setObjectName ( const QString& name );

signals:
    void btnClicked();

public slots:

private:
    QPushButton* m_btnBrower;

    // QObject interface
};

#endif // QSEARCHLINEEDIT_H
