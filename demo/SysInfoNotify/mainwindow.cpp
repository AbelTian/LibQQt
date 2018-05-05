#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "qqtsysteminfo.h"

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );

    TCPUTable cpu;
    QQtSystemInfo s;
    s.getCPUInfo ( cpu );
    s.getCPUInfo ( cpu );
    pline() << cpu.mNum;
    QListIterator<TCPUInfo> itor ( cpu.mList );
    while ( itor.hasNext() )
    {
        const TCPUInfo& c = itor.next();
        pline() << c.mCoreNum;
    }
    TMemTable mem;
    s.getMEMInfo ( mem );
    pline() << mem.mNum;
}

MainWindow::~MainWindow()
{
    delete ui;
}
