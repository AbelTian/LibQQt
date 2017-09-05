#include "qqtwindow.h"
#include "ui_qqtwindow.h"
#include "qqtobjectfactory.h"
#include "qqtgui-qt.h"
#include "qqtcore.h"
#include "qqtwidgets.h"
#include "qqtanimation.h"
#include "qqtobjectfactory.h"
#include "animationmanager.h"

QQTWindow::QQTWindow(QWidget *parent) :
    QStackedWidget(parent),
    ui(new Ui::QQTWindow)
{
    ui->setupUi(this);

    QQTObjectFactory::registerObject(this);

#ifdef __MIPS_LINUX__
    /*
     * 这里只要frameless足够
     */
    setWindowFlags(Qt::FramelessWindowHint);
    /*
     * 控件背景透明，显示设置的图片背景或者下一级背景。
     */
    setAttribute(Qt::WA_TranslucentBackground, true);
#endif
    setFixedSize(1024, 600);
    moveCenter(this);

    QQTObjectFactory::registerObject(ui->pushButton);
    QQTObjectFactory::registerObject(ui->pushButton_2);
    QQTObjectFactory::registerObject(ui->pushButton_3);
    QQTObjectFactory::registerObject(ui->pushButton_4);
    QQTObjectFactory::registerObject(ui->pushButton_5);
    QQTObjectFactory::registerObject(ui->pushButton_6);

    /**
     * @brief QQTAnimationManager::Instance
     * 开启或者关闭动画
     */
    AnimationManager::Instance(this);
}

QQTWindow::~QQTWindow()
{
    delete ui;
}
