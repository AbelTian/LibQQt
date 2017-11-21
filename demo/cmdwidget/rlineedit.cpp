#include "rlineedit.h"
#include <QDebug>
#include <QKeyEvent>
#include <QApplication>
#include <QProcess>
#include <QProcessEnvironment>

RLineEdit::RLineEdit(QWidget *parent) :
    QLineEdit(parent)
{

}


void RLineEdit::keyPressEvent(QKeyEvent *e)
{
    QLineEdit::keyPressEvent(e);
    qDebug() << "a" << e;
    //enter to run
    if(e->key() == Qt::Key_Return)
    {
        qDebug() << text();
        if(!text().isEmpty())
        {
            //shell and application
            //need set current directory
#ifdef __WIN64__
            if(text().trimmed() == "cmd" ||
                    text().trimmed() == "cmd.exe")
                system(text().toLocal8Bit().constData());

            QStringList cmd;
            cmd += "cmd.exe";
            cmd += "/c";
            cmd += text();
            QProcess::startDetached("cmd.exe", cmd);
#else
            QStringList cmd;
            cmd += "/bin/sh";
            cmd += "-c";
            cmd += text();
            QProcess::startDetached("/bin/sh", cmd);
#endif
            qApp->quit();
        }
    }
}

void RLineEdit::focusOutEvent(QFocusEvent *e)
{
    QLineEdit::focusOutEvent(e);
    qDebug() << "b" << e;
    //app quit
    qApp->quit();
}
