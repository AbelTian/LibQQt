#include "qqtwindow.h"
#include "ui_qqtwindow.h"
#include "qqtobjectfactory.h"
#include "qqt-qt.h"
#include "qqtcore.h"
#include "qqtwidgets.h"
#include "qqtanimation.h"
#include "qqtobjectfactory.h"
#include "animationmanager.h"

QQTWindow::QQTWindow(QWidget* parent) :
    QStackedWidget(parent),
    ui(new Ui::QQTWindow)
{
    ui->setupUi(this);

    QQtObjectParcel::registerObject(this);

#ifdef __EMBEDDED_LINUX__
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

    QQtObjectParcel::registerObject(ui->pushButton);
    QQtObjectParcel::registerObject(ui->pushButton_2);
    QQtObjectParcel::registerObject(ui->pushButton_3);
    QQtObjectParcel::registerObject(ui->pushButton_4);
    QQtObjectParcel::registerObject(ui->pushButton_5);
    QQtObjectParcel::registerObject(ui->pushButton_6);

    /**
     * @brief QQtAnimationManager::Instance
     * 开启或者关闭动画
     */
    AnimationManager::Instance(this);
}

QQTWindow::~QQTWindow()
{
    delete ui;
}
