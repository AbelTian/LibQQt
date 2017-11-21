#ifndef QQTWIFIWIDGET_H
#define QQTWIFIWIDGET_H

#include "qstandarditemmodel.h"
#include "qqt-qt.h"
#include "qqtgui.h"
#include "qqtpassworddialog.h"
#include <QItemDelegate>
#include <QStylePainter>
#include "qqtcore.h"
#include "qqt-local.h"

class QQTSHARED_EXPORT QQtWiFiIdTextDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    QQtWiFiIdTextDelegate ( QObject* parent = 0 ) : QItemDelegate ( parent ), parent ( parent ) { }

private:
    QObject* parent;

    // QItemDelegate interface
protected:
    void drawCheck ( QPainter* painter, const QStyleOptionViewItem& option, const QRect& rect, Qt::CheckState state ) const;

    // QItemDelegate interface
protected:
    void drawDisplay ( QPainter* painter, const QStyleOptionViewItem& option, const QRect& rect,
                       const QString& text ) const;
};

namespace Ui {
class QQtWiFiWidget;
}

class QQtWiFiWidget : public QQTTableView
{
    Q_OBJECT

public:
    explicit QQtWiFiWidget ( QWidget* parent = 0 );
    ~QQtWiFiWidget();

private slots:
    void clickWIFI();
    void wifiRefreshed();
protected:
    TWifi currentWifi();
    bool setCurrentWifi ( QString bssid_mac, QString password = "" );
private:
    QQtEthenetManager* m_pManager;
    QQtWiFiIdTextDelegate* dg;

private:
    Ui::QQtWiFiWidget* ui;
    QStandardItemModel* m_model;
    QQtPasswordDialog* m_pass;
};

#endif // QQTWIFIWIDGET_H
