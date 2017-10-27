#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qtsoap.h>
#include <qqt-qt.h>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = 0);
    ~MainWindow();

private slots:
    void onResponse(const QtSoapMessage&);
    void onSubmit();

private:
    QtSoapHttpTransport* m_pHttp;
    QLabel* m_pQQLabel;
    QLabel* m_pStateLabel ;
    QLineEdit* m_pQQLineEdit ;
    QLineEdit* m_pStateLineEdit;
    QPushButton*  m_pSubmitButton ;
};

#endif // MAINWINDOW_H
