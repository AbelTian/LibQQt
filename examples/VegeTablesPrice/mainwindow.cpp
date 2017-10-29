#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QDebug"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList vl;
    vl << "西葫芦";
    vl << "土豆";
    vl << "茄子";
    vl << "西红柿";
    vl << "玉米";
    vl << "小麦";
    vl << "棉花";
    vl << "西瓜";
    vl << "白蒜";
    vl << "辣椒";
    vl << "菠菜";
    vl << "胡萝卜";
    vl << "黑木耳";
    vl << "白木耳";
    vl << "蓬蒿";
    vl << "小葱";
    vl << "山药";
    vl << "苹果";
    vl << "香瓜";
    vl << "枣";
    vl << "梨";
    vl << "香蕉";
    vl << "蒜薹";
    vl << "豆角";
    vl << "茴香";
    ui->lw->addItems(vl);


    connect(ui->lw, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),
            this, SLOT(currentItemChanged(QListWidgetItem*, QListWidgetItem*)));

    ui->lw->setCurrentRow(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::currentItemChanged(QListWidgetItem* cur, QListWidgetItem* prev)
{
    qDebug() << cur << prev;
    if (!cur)
        return;

    QString url = QString("http://www.baidu.com/s?wd=%1%2").arg(cur->text()).arg("价格");

}
