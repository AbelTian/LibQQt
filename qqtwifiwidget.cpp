#include "qqtwifiwidget.h"
#include "ui_qqtwifiwidget.h"
#include "qqtlinux.h"
#include "qqtdefine.h"
#include "qqtethenetmanager.h"
#include "qqtmsgbox.h"


void QQTWIFIIDTextDelegate::drawCheck(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, Qt::CheckState state) const
{
#if 0
    if (!rect.isValid())
        return;
    QStyleOptionViewItem opt(option);
    opt.rect = rect;
    opt.state = opt.state & ~QStyle::State_HasFocus;
    switch (state) {
    case Qt::Unchecked:
        opt.state |= QStyle::State_Off;
        break;
    case Qt::PartiallyChecked:
        opt.state |= QStyle::State_NoChange;
        break;
    case Qt::Checked:
        opt.state |= QStyle::State_On;
        break;
    }
    QApplication::style()->drawPrimitive(QStyle::PE_IndicatorViewItemCheck, &opt, painter);
#else
    QItemDelegate::drawCheck(painter, option, rect, state);
#endif
}

void QQTWIFIIDTextDelegate::drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const
{
    if("COMPLETED" == text)
        painter->drawImage(rect, QImage("./skin/default/bk_sel.png"));
}

QQTWIFIWidget::QQTWIFIWidget(QWidget *parent) :
    QQTTableView(parent),
    ui(new Ui::QQTWIFIWidget)
{
    ui->setupUi(this);

    connect(this, SIGNAL(clicked(QModelIndex)),
            this, SLOT(clickWIFI()), Qt::QueuedConnection);
    m_pass = new QQTPasswordDialog(this);

    m_pManager = QQTEthenetManager::Instance(this);
    connect(m_pManager, SIGNAL(sigRefreshed()), this, SLOT(wifiRefreshed()));

    m_model = new QQTStandardItemModel(this);
    m_model->setColumnCount(ESSID_MAX);
    setModel(m_model);

    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    horizontalHeader()->setHidden(true);
    verticalHeader()->setHidden(true);
    resizeColumnsToContents();
    horizontalHeader()->setStretchLastSection(true);
    setShowGrid(true);

#ifdef __MIPS_LINUX__
    setFocusPolicy(Qt::NoFocus);
#endif
    dg = new QQTWIFIIDTextDelegate(this);
    setItemDelegateForColumn(ESSID_STATUS, dg);
    for(int i = ESSID_TYPE; i < ESSID_MAX; i++)
        setColumnHidden(i, true);
#ifdef __QT5__
    horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
#else
    horizontalHeader()->setResizeMode(0, QHeaderView::Fixed);
#endif
    setColumnWidth(ESSID_STATUS, 40);

}

QQTWIFIWidget::~QQTWIFIWidget()
{
    delete ui;
}


TWifi QQTWIFIWidget::currentWifi()
{
    return m_pManager->currentWifi();
}


bool QQTWIFIWidget::setCurrentWifi(QString bssid_mac, QString password)
{
    return m_pManager->setCurrentWifi(bssid_mac, password);
}

void QQTWIFIWidget::wifiRefreshed()
{
    int row = 0;
    m_model->removeRows(row, m_model->rowCount());
    QList<TWifi>& list = m_pManager->wifiList();
    m_model->insertRows(row, list.size());
    for(QList<TWifi>::Iterator it = list.begin();
        it != list.end(); it++)
    {
        TWifi wifi = *(TWifi*)(&*it);
        for(int i = ESSID_STATUS; i < ESSID_MAX; i++)
            m_model->setData(m_model->index(row, i), wifi[i]);
        row++;
    }
    m_model->submit();
}

void QQTWIFIWidget::clickWIFI()
{
    QString name = m_model->data(m_model->index(currentIndex().row(), ESSID_NAME)).toString();
    QString encryt = m_model->data(m_model->index(currentIndex().row(), ESSID_ENCRYP)).toString();
    QString type = m_model->data(m_model->index(currentIndex().row(), ESSID_TYPE)).toString();
    QString mac = m_model->data(m_model->index(currentIndex().row(), ESSID_BSSID)).toString();

    QQTEthenetManager::Instance()->setRefresh(false);
    do
    {
        if("YES" == encryt)
        {
            m_pass->setWifiName(name);
            if(QQTPasswordDialog::Rejected == m_pass->exec())
                break;
        }

        bool ok = setCurrentWifi(mac, m_pass->wifiPwd());

        pline() << ok;

        if(!ok)
        {
            QQTMsgBox::warning(this, tr("Password error"));
            break;
        }

        pline() << name << encryt << m_pass->wifiPwd();
    }while(0);
    QQTEthenetManager::Instance()->setRefresh();
}

