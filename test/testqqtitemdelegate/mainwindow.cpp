#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );

    QFile rfc ( conf_root ( "rfc.json" ) );
    rfc.open ( QFile::ReadOnly );
    QByteArray bytes;
    if ( rfc.isOpen() )
        bytes = rfc.readAll();
    rfc.close();

    mDict.fromJson ( bytes );

    mModel = new UserCustomTreeModel ( this );
    ui->treeView->setModel ( mModel );

    ui->treeView->header()->setSectionResizeMode ( RfcName, QHeaderView::ResizeToContents );
    ui->treeView->header()->setStretchLastSection ( false );
    //ui->treeView->setEditTriggers ( QTreeView::NoEditTriggers );
    ui->treeView->setSelectionMode ( QTreeView::SingleSelection );

    //ui->treeView->setItemDelegateForColumn ( RfcDownProgress, new QQtProgressBarDelegate ( this ) );
    //ui->treeView->setItemDelegateForColumn ( RfcDownStatus, new QQtButtonItemDelegate ( this ) );
    ui->treeView->setItemDelegateForColumn ( RfcDownStatus, new QQtCheckBoxDelegate ( this ) );
    ui->treeView->setItemDelegateForColumn ( RfcDownProgress, new QQtSliderItemDelegate ( this ) );

    mModel->query ( mDict );
    ui->treeView->resizeColumnToContents ( RfcName );
}

MainWindow::~MainWindow()
{
    delete ui;
}
