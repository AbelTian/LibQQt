#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>

#include "qqtcore.h"
#include "qqtwebprotocolmanager.h"

#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>

QT_CHARTS_USE_NAMESPACE


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

    void seeplot();
    void seereport();

private:
    Ui::MainWindow* ui;
    QQtWebProtocolManager* m_client;
    QMap<QString, QString> m_mapVege;
    QBarSet* m_barSet0;
    QBarSet* m_barSet1;
    QBarSet* m_barSet2;
    QBarSet* m_barSet3;
    QBarSet* m_barSet4;
};

#endif // MAINWINDOW_H
