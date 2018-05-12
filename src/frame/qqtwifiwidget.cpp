#include "qqtwifiwidget.h"
#include "ui_qqtwifiwidget.h"
#include "qqtlinux.h"
#include "qqtcore.h"
#include "qqtmsgbox.h"
#include "qqtethenetmanager.h"


void QQtWiFiIdTextDelegate::drawCheck ( QPainter* painter, const QStyleOptionViewItem& option, const QRect& rect,
                                        Qt::CheckState state ) const
{
#if 0

    if ( !rect.isValid() )
        return;

    QStyleOptionViewItem opt ( option );
    opt.rect = rect;
    opt.state = opt.state & ~QStyle::State_HasFocus;

    switch ( state )
    {
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

    QApplication::style()->drawPrimitive ( QStyle::PE_IndicatorViewItemCheck, &opt, painter );
#else
    QItemDelegate::drawCheck ( painter, option, rect, state );
#endif
}

void QQtWiFiIdTextDelegate::drawDisplay ( QPainter* painter, const QStyleOptionViewItem& option, const QRect& rect,
                                          const QString& text ) const
{
    if ( "COMPLETED" == text )
        painter->drawImage ( rect, QImage ( "./skin/default/bk_sel.png" ) );
}

QQtWiFiWidget::QQtWiFiWidget ( QWidget* parent ) :
    QQtTableView ( parent ),
    ui ( new Ui::QQtWiFiWidget )
{
    ui->setupUi ( this );

    connect ( this, SIGNAL ( clicked ( QModelIndex ) ),
              this, SLOT ( clickWIFI() ), Qt::QueuedConnection );
    m_pass = new QQtPasswordDialog ( this );

    m_pManager = QQtEthenetManager::Instance ( this );
    connect ( m_pManager, SIGNAL ( sigRefreshed() ), this, SLOT ( wifiRefreshed() ) );

    m_model = new QStandardItemModel ( this );
    m_model->setColumnCount ( ESSID_MAX );
    setModel ( m_model );

    setSelectionMode ( QAbstractItemView::SingleSelection );
    setSelectionBehavior ( QAbstractItemView::SelectRows );
    setEditTriggers ( QAbstractItemView::NoEditTriggers );
    horizontalHeader()->setHidden ( true );
    verticalHeader()->setHidden ( true );
    resizeColumnsToContents();
    horizontalHeader()->setStretchLastSection ( true );
    setShowGrid ( true );

#ifdef __EMBEDDED_LINUX__
    setFocusPolicy ( Qt::NoFocus );
#endif
    dg = new QQtWiFiIdTextDelegate ( this );
    setItemDelegateForColumn ( ESSID_STATUS, dg );

    for ( int i = ESSID_TYPE; i < ESSID_MAX; i++ )
        setColumnHidden ( i, true );

#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
    horizontalHeader()->setResizeMode ( 0, QHeaderView::Fixed );
#else
    horizontalHeader()->setSectionResizeMode ( 0, QHeaderView::Fixed );
#endif
    setColumnWidth ( ESSID_STATUS, 40 );

}

QQtWiFiWidget::~QQtWiFiWidget()
{
    delete ui;
}


TWifi QQtWiFiWidget::currentWifi()
{
    return m_pManager->currentWifi();
}


bool QQtWiFiWidget::setCurrentWifi ( QString bssid_mac, QString password )
{
    return m_pManager->setCurrentWifi ( bssid_mac, password );
}

void QQtWiFiWidget::wifiRefreshed()
{
    int row = 0;
    m_model->removeRows ( row, m_model->rowCount() );
    QList<TWifi>& list = m_pManager->wifiList();
    m_model->insertRows ( row, list.size() );

    for ( QList<TWifi>::Iterator it = list.begin();
          it != list.end(); it++ )
    {
        TWifi wifi = * ( TWifi* ) ( &*it );

        for ( int i = ESSID_STATUS; i < ESSID_MAX; i++ )
            m_model->setData ( m_model->index ( row, i ), wifi[i] );

        row++;
    }

    m_model->submit();
}

void QQtWiFiWidget::clickWIFI()
{
    QString name = m_model->data ( m_model->index ( currentIndex().row(), ESSID_NAME ) ).toString();
    QString encryt = m_model->data ( m_model->index ( currentIndex().row(), ESSID_ENCRYP ) ).toString();
    QString type = m_model->data ( m_model->index ( currentIndex().row(), ESSID_TYPE ) ).toString();
    QString mac = m_model->data ( m_model->index ( currentIndex().row(), ESSID_BSSID ) ).toString();

    QQtEthenetManager::Instance()->setRefresh ( false );

    do
    {
        if ( "YES" == encryt )
        {
            m_pass->setWifiName ( name );

            if ( QQtPasswordDialog::Rejected == m_pass->exec() )
                break;
        }

        bool ok = setCurrentWifi ( mac, m_pass->wifiPwd() );

        pline() << ok;

        if ( !ok )
        {
            QQtMsgBox::warning ( this, tr ( "Password error" ) );
            break;
        }

        pline() << name << encryt << m_pass->wifiPwd();
    }
    while ( 0 );

    QQtEthenetManager::Instance()->setRefresh();
}

