#include "mainwindow.h"
#include <QApplication>
#include <qqtapplication.h>

class MyApp : public QQtApplication
{
public:
    explicit MyApp(int &argc, char **argv):QQtApplication(argc, argv){}
};

int main(int argc, char *argv[])
{
    MyApp a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
