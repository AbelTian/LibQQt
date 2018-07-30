#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qqttablemodel.h"
#include "qqtframe.h"
#include "qqtword.h"
#include "qqtcore.h"
#include "qqtprinter.h"

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );

#ifdef __EMBEDDED_LINUX__
    showFullScreen();
    ui->lineEdit->setText ( "/Application/ccc.pdf" );
#else
    ui->lineEdit->setText ( "/home/tdr/Develop/ccc.pdf" );
#endif

    ui->tableView->setDB ( DB_MANAGER );
    ui->tableView->setTable ( "User" );
    ui->tableView->query ( "" );
    ui->tableView->horizontalHeader()->setSectionResizeMode ( QQtHeaderView::ResizeToContents );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if ( ui->lineEdit->text().isEmpty() )
        return;

    QQtWord word;
    //所有对QQtWord的设置,做在这里.
    word.initWord();

    //work flow
    word.setFooterText ( "Company T", word.headerFont(), Qt::AlignLeft );
    word.setHeaderText ( "Company T Header", word.headerFont(), Qt::AlignLeft );

    word.addText ( "Main Page", word.titleFont(), Qt::AlignCenter );

    word.addText ( "Now, this is first section.", word.mainFont(), Qt::AlignLeft );
    word.addText ( "Now, this is second section.", word.mainFont(), Qt::AlignLeft  );
    word.addText ( "Now, this is third section.", word.mainFont(), Qt::AlignLeft  );
    word.addText ( "Now, this is four section.", word.mainFont(), Qt::AlignLeft  );

    word.addText ( "八荣八耻", word.title2Font(), Qt::AlignLeft );
    word.addText ( "以热爱祖国为荣、以危害祖国为耻。" );
    word.addText ( "以服务人民为荣、以背离人民为耻。" );
    word.addText ( "以崇尚科学为荣、以愚昧无知为耻。" );
    word.addText ( "以辛勤劳动为荣、以好逸恶劳为耻。" );
    word.addText ( "以团结互助为荣、以损人利己为耻。" );
    word.addText ( "以诚实守信为荣、以见利忘义为耻。" );
    word.addText ( "以遵纪守法为荣、以违法乱纪为耻。" );
    word.addText ( "以艰苦奋斗为荣、以骄奢淫逸为耻。" );

    word.addText ( "社会主义核心价值观", word.title2Font(), Qt::AlignLeft );
    word.addText ( "富强、民主、文明、和谐，" );
    word.addText ( "自由、平等、公正、法治，" );
    word.addText ( "爱国、敬业、诚信、友善。" );

    //word.addText ( "  人民代表大会制度是我国的根本政治制度。它是以人民代表大会为核心和主要内容的国家政权组织形式。这一制度的内容主要为两个方面：一是关于人民代表大会本身的产生、组织、职权和行使职权程序等一系列规定；二是关于人民代表大会与人民的关系，人民代表大会与行政机关、审判机关、检察机关、军事机关的关系，以及中央政权和地方政权的关系等一系列规定。这一制度的核心是保证国家的一切权力属于人民，人民通过人民代表大会这一组织形式参与国家事务的管理，行使当家作主的权力。",
    //               word.mainFont(), Qt::AlignLeft );

    QQtTableWidget tableWidget;
    tableWidget.setDB ( DB_MANAGER );
    tableWidget.setTable ( "User" );
    tableWidget.query ( "" );
    tableWidget.horizontalHeader()->setSectionResizeMode ( QQtHeaderView::ResizeToContents );
    tableWidget.setFixedWidth ( 523.8 );
    pline() << word.clientRectF() << word.paperRect();
    word.addTable ( &tableWidget );

    word.addSignoffText ( "Reporter: Tianduanrui" );

    QList<QImage> papers;
    //分辨率可以随意一点.一般用于显示器正常显示,为96.
    QRectF paperRect = word.getTargetRectF ( 300, 300 );
    word.exportImage ( papers, paperRect );
    pline() << papers;

    QQtPrinter printer;
    pline() << printer.logicalDpiX() << printer.logicalDpiY();
    printer.setOutputFileName ( ui->lineEdit->text() );
    printer.generateToPdfFile ( papers, paperRect );
}
