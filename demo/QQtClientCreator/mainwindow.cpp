#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QKeyEvent>

MainWindow::MainWindow ( QWidget* parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
{
    ui->setupUi ( this );

    QFile file ( "templete/qqtuserprotocol.h" );
    file.open ( QFile::ReadOnly );
    headerFileBytes = file.readAll();
    file.close();

    file.setFileName ( "templete/qqtuserprotocol.cpp" );
    file.open ( QFile::ReadOnly );
    sourceFileBytes = file.readAll();
    file.close();

    ui->lineEdit->installEventFilter ( this );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if ( ui->lineEdit->text().isEmpty() )
        return;

    QByteArray className = ui->lineEdit->text().toLocal8Bit();
    QByteArray HongName = className.toUpper();
    QByteArray fileName = className.toLower();

    QByteArray headerFileBytes = this->headerFileBytes;
    QByteArray sourceFileBytes = this->sourceFileBytes;

    headerFileBytes.replace ( "QQtUser", className );
    headerFileBytes.replace ( "QQTUSER", HongName );

    sourceFileBytes.replace ( "QQtUser", className );
    sourceFileBytes.replace ( "qqtuser", fileName );

    QFile headerFile ( QString ( "%1protocol.h" ).arg ( QString ( fileName ) ) );
    QFile sourceFile ( QString ( "%1protocol.cpp" ).arg ( QString ( fileName ) ) );

    headerFile.open ( QFile::Truncate | QFile::WriteOnly );
    headerFile.write ( headerFileBytes );
    headerFile.close();

    sourceFile.open ( QFile::Truncate | QFile::WriteOnly );
    sourceFile.write ( sourceFileBytes );
    sourceFile.close();

}


bool MainWindow::eventFilter ( QObject* watched, QEvent* event )
{
    if ( watched == ui->lineEdit )
    {
        if ( event->type() == QEvent::KeyPress )
        {
            QKeyEvent* e = ( QKeyEvent* ) event;
            if ( e->key() == Qt::Key_Enter
                 || e->key() == Qt::Key_Return )
            {
                on_pushButton_clicked();
            }
        }
    }
}
