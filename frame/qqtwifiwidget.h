#ifndef QQTWIFIWIDGET_H
#define QQTWIFIWIDGET_H

#include "qstandarditemmodel.h"
#include "qqtgui-qt.h"
#include "qqtgui.h"
#include "qqtpassworddialog.h"
#include <QItemDelegate>
#include <QStylePainter>
#include "qqtdefine.h"

class QQTWIFIIDTextDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    QQTWIFIIDTextDelegate(QObject *parent = 0): QItemDelegate(parent), parent(parent) { }

private:
    QObject* parent;

    // QItemDelegate interface
protected:
    void drawCheck(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, Qt::CheckState state) const;

    // QItemDelegate interface
protected:
    void drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const;
};

namespace Ui {
class QQTWIFIWidget;
}

class QQTWIFIWidget : public QQTTableView
{
    Q_OBJECT

public:
    explicit QQTWIFIWidget(QWidget *parent = 0);
    ~QQTWIFIWidget();

private slots:
    void clickWIFI();
    void wifiRefreshed();
protected:
    TWifi currentWifi();
    bool setCurrentWifi(QString bssid_mac, QString password = "");
private:
    QQTEthenetManager* m_pManager;
    QQTWIFIIDTextDelegate* dg;

private:
    Ui::QQTWIFIWidget *ui;
    QStandardItemModel* m_model;
    QQTPasswordDialog* m_pass;
};

#endif // QQTWIFIWIDGET_H
