#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>

#include "qqtcore.h"
#include "qqtwebworkclient.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow ( QWidget* parent = 0 );
    ~MainWindow();
private slots:
    void currentItemChanged ( QListWidgetItem*, QListWidgetItem* );
    void replyFinished ( QNetworkReply* reply );
private:
    Ui::MainWindow* ui;
    QQtWebWorkClient* m_client;
    QMap<QString, QString> m_mapVege;
};

#endif // MAINWINDOW_H
