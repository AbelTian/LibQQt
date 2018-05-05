#include "qqtmultipagetablewidget.h"
#include "ui_qqtmultipagetablewidget.h"
#include "qqtcore.h"
#include "qqtsql.h"
#include "qqt-qt.h"

QQtMultiPageTableWidget::QQtMultiPageTableWidget ( QWidget* parent ) :
    QWidget ( parent ),
    ui ( new Ui::QQtMultiPageTableWidget )
{
    ui->setupUi ( this );

    m_db = newDatabaseConnection();

    m_pageNum = 0;
    m_numPerPage = 14;
    selectionMode = QAbstractItemView::MultiSelection;
    altColor = true;
    resizeMode = QHeaderView::ResizeToContents;

    ui->btnJump->setFixedWidth ( 30 );
    ui->btnLeft->setFixedWidth ( 30 );
    ui->btnRight->setFixedWidth ( 30 );
    ui->btnLeftHead->setFixedWidth ( 30 );
    ui->btnRightHead->setFixedWidth ( 30 );
    ui->leNum->setFixedWidth ( 40 );
    ui->btnJump->setHidden ( true );
    ui->leNum->setHidden ( true );
    ui->btnRightHead->setHidden ( true );
    ui->btnRight->setHidden ( true );
    ui->btnLeftHead->setHidden ( true );
    ui->btnLeft->setHidden ( true );

}

QQtMultiPageTableWidget::~QQtMultiPageTableWidget()
{
    delete ui;
}

void QQtMultiPageTableWidget::setDB ( QString db )
{
    m_name = db;
    setDatabaseName ( m_db, m_name );
}

void QQtMultiPageTableWidget::setTable ( QString table )
{
    m_table = table;
}

void QQtMultiPageTableWidget::setRelation ( int column, const QSqlRelation& relation )
{
    m_columnRelation.insert ( column, relation );
}

void QQtMultiPageTableWidget::query ( QString filter )
{
    ptime(); //3ms

    //high?
    QQtSleep ( 478 );

    QSqlQuery query ( m_db );
    query.exec ( QString ( "select count(*) from %1" ).arg ( m_table ) );

    int num = 0;

    if ( query.next() )
    {
        num = query.value ( 0 ).toInt();
        pline() << "record num:" << num;
    }

    query.finish();

    int pageNum = 0;

    if ( num % m_numPerPage > 0 )
        pageNum = num / m_numPerPage + 1;
    else
        pageNum = num / m_numPerPage;

    m_pageNum = pageNum;

    int pix = 0;

#if 0

    /*
     * 首次做检查，每隔10张*14条
     */
    if ( m_pageNum > ui->stWidgetPage->count() )
        pix = m_pageNum - ui->stWidgetPage->count() + 10；
#else
    /*
     * 每次做检查，每次的延迟比较均匀 每隔1张*14条
     */
    pix = m_pageNum - ui->stWidgetPage->count();

#endif

              // pix >= 1 start work
              for ( int i = 0; i < pix; i++ )
        {
            //ptime();//89ms
            QQtTableWidget* page = new QQtTableWidget ( this );
            //ptime();//2ms
            page->setDB ( m_name );
            //ptime();//8ms
            page->setTable ( m_table );
            //ptime();//14ms
            //query
            //ptime();//3ms
            QAbstractItemModel* m_model = page->model();

            for ( int i = 0; i < m_model->columnCount(); i++ )
                m_model->setHeaderData (
                    i, Qt::Horizontal,
                    m_headerData.value ( i, m_model->headerData ( i, Qt::Horizontal ).toString() ) );

            //ptime();//1ms
            page->setSelectionMode ( selectionMode );
            page->setAlternatingRowColors ( altColor );
#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
            page->horizontalHeader()->setResizeMode ( resizeMode );
#else
            page->horizontalHeader()->setSectionResizeMode ( resizeMode );
#endif

            //ptime();//0ms
            for ( int i = 0; i < m_model->columnCount(); i++ )
#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
                page->horizontalHeader()->setResizeMode ( i, m_resizeMode.value ( i, resizeMode ) );

#else
                page->horizontalHeader()->setSectionResizeMode ( i, m_resizeMode.value ( i, resizeMode ) );
#endif

            //ptime();//QHash(338ms) QMap(372ms) 400ms(QHash等几乎不耗时)
            for ( int i = 0; i < m_model->columnCount(); i++ )
                page->setColumnWidth ( i, m_columnWidth.value ( i ) );

            //ptime();
            for ( int i = 0; i < m_model->columnCount(); i++ )
                page->setColumnHidden ( i, m_columnHidden.value ( i ) );

            //ptime();//219ms
            ui->stWidgetPage->addWidget ( page );
            //ptime();
        }

    for ( int i = 0; i < m_pageNum; i++ )
    {
        QQtTableWidget* page = ( QQtTableWidget* ) ( ui->stWidgetPage->widget ( i ) );
        page->query ( QString ( "%1 limit %2 offset %3" )
                      .arg ( filter )
                      .arg ( m_numPerPage )
                      .arg ( i * m_numPerPage ) );
    }
}

int QQtMultiPageTableWidget::pageNum()
{
    return m_pageNum;
}

int QQtMultiPageTableWidget::currentPage()
{
    return ui->stWidgetPage->currentIndex() + 1;
}

void QQtMultiPageTableWidget::setCurrentPage ( int index )
{
    if ( index < 1 || index > m_pageNum )
        return;

    ui->stWidgetPage->setCurrentIndex ( index - 1 );
    ui->lbPos->setText ( QString ( "%1/%2" ).arg ( index ).arg ( m_pageNum ) );
}

void QQtMultiPageTableWidget::setRecordNumPerPage ( int num )
{
    m_numPerPage = num;
}

void QQtMultiPageTableWidget::setColumnHidden ( int key, bool value )
{
    m_columnHidden.insert ( key, value );
}

void QQtMultiPageTableWidget::setSelectionMode ( QAbstractItemView::SelectionMode mode )
{
    selectionMode = mode;
}

void QQtMultiPageTableWidget::setResizeMode ( QHeaderView::ResizeMode mode )
{
    resizeMode = mode;
}

void QQtMultiPageTableWidget::setResizeMode ( int column, QHeaderView::ResizeMode mode )
{
    m_resizeMode.insert ( column, mode );
}

void QQtMultiPageTableWidget::setAlternatingRowColors ( bool alt )
{
    altColor = alt;
}

void QQtMultiPageTableWidget::setHeaderData ( Qt::Orientation, QStringList dataList )
{
    for ( int i = 0; i < dataList.size(); i++ )
    {
        m_headerData.insert ( i, dataList.at ( i ) );
    }
}

void QQtMultiPageTableWidget::setHeaderData ( int i, Qt::Orientation, QString data )
{
    m_headerData.insert ( i, data );
}

void QQtMultiPageTableWidget::setColumnWidth ( int column, int width )
{
    m_columnWidth.insert ( column, width );
}

void QQtMultiPageTableWidget::on_btnLeft_clicked()
{
    int index = ui->stWidgetPage->currentIndex();

    if ( index > 0 )
        index--;

    ui->stWidgetPage->setCurrentIndex ( index );
    ui->lbPos->setText ( QString ( "%1/%2" ).arg ( index + 1 ).arg ( m_pageNum ) );
}

void QQtMultiPageTableWidget::on_btnRight_clicked()
{
    int index = ui->stWidgetPage->currentIndex();

    if ( index < m_pageNum - 1 )
        index++;

    ui->stWidgetPage->setCurrentIndex ( index );
    ui->lbPos->setText ( QString ( "%1/%2" ).arg ( index + 1 ).arg ( m_pageNum ) );
}

void QQtMultiPageTableWidget::on_btnJump_clicked()
{
    int num = ui->leNum->text().toInt();

    if ( num <= m_pageNum && num > 0 )
    {
        ui->stWidgetPage->setCurrentIndex ( num - 1 );
        ui->lbPos->setText ( QString ( "%1/%2" ).arg ( num ).arg ( m_pageNum ) );
    }
}

void QQtMultiPageTableWidget::on_btnLeftHead_clicked()
{
    ui->stWidgetPage->setCurrentIndex ( 0 );
    ui->lbPos->setText ( QString ( "%1/%2" ).arg ( 1 ).arg ( m_pageNum ) );
}

void QQtMultiPageTableWidget::on_btnRightHead_clicked()
{
    int index = m_pageNum - 1;
    ui->stWidgetPage->setCurrentIndex ( index );
    ui->lbPos->setText ( QString ( "%1/%2" ).arg ( index + 1 ).arg ( m_pageNum ) );
}

void QQtMultiPageTableWidget::selectedRows ( int column, QVector<QStringList>& strl )
{
    for ( int i = 0; i < m_pageNum; i++ )
    {
        QQtTableWidget* page = ( QQtTableWidget* ) ui->stWidgetPage->widget ( i );
        QMap<int, QStringList> ids;
        page->selectedRows ( column, ids );
        QMapIterator<int, QStringList> itor ( ids );

        while ( itor.hasNext() )
        {
            itor.next();
            strl.append ( itor.value() );
        }
    }

    return;
}

QQtTableWidget* QQtMultiPageTableWidget::selectedRows ( int column )
{
    QString sectionName;
    QSqlQuery query ( m_db );
    query.exec ( QString ( "select * from %1 limit 0" ).arg ( m_table ) );
    sectionName = query.record().fieldName ( column );
    query.finish();
    pline() << sectionName;

    QVector<QStringList> lid;
    selectedRows ( column, lid );

    static QQtTableWidget* page = new QQtTableWidget ( this );
    page->setDB ( m_name );
    page->setTable ( m_table );

    QString excp;

    for ( int i = 0; i < lid.count() - 1; i++ )
        excp += QString ( "%1 = '%2' or " ).arg ( sectionName ).arg ( lid[i].at ( column ) );

    excp += QString ( "%1 = '%2'" ).arg ( sectionName ).arg ( lid.last().at ( column ) );
    page->query ( excp );

    QAbstractItemModel* m_model = page->model();

    for ( int i = 0; i < m_model->columnCount(); i++ )
        m_model->setHeaderData (
            i, Qt::Horizontal,
            m_headerData.value ( i, m_model->headerData ( i, Qt::Horizontal ).toString() ) );

    page->setSelectionMode ( selectionMode );
    page->setAlternatingRowColors ( altColor );
#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
    page->horizontalHeader()->setResizeMode ( resizeMode );
#else
    page->horizontalHeader()->setSectionResizeMode ( resizeMode );
#endif

    for ( int i = 0; i < m_model->columnCount(); i++ )
    {
        page->setColumnHidden ( i, m_columnHidden.value ( i ) );
#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
        page->horizontalHeader()->setResizeMode ( i, m_resizeMode.value ( i, resizeMode ) );
#else
        page->horizontalHeader()->setSectionResizeMode ( i, m_resizeMode.value ( i, resizeMode ) );
#endif
        page->setColumnWidth ( i, m_columnWidth.value ( i ) );
    }

    return page;
}


void QQtMultiPageTableWidget::removeSelectedRows ( int column )
{
    for ( int i = 0; i < m_pageNum; i++ )
    {
        QQtTableWidget* page = ( QQtTableWidget* ) ui->stWidgetPage->widget ( i );
        QMap<int, QStringList> ids;
        page->selectedRows ( column, ids );
        page->removeRows ( column, ids.values() );
    }
}
