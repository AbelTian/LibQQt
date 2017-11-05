#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <QKeyEvent>
#include <qqtcore.h>
#include <qqtslideeffecttabbar.h>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    value = 0;
    curmaxValue = 80;

    ui->hs0->setRange(0, 100);

    ui->w01->setRange(0, 100);
    ui->w01->setBackgroundColor(QColor(60, 80, 100));
    ui->w01->setPercentStyle(QQtCustomEffectProgressBar::PercentStyle_Arc);
    ui->w01->setShowFree(true);
    ui->w01->setShowSmallCircle(true);

    ui->w0->setRange(0, 100);
    ui->w0->setBackgroundColor(QColor(60, 80, 100));
    ui->w0->setPercentStyle(QQtCustomEffectProgressBar::PercentStyle_Polo);

    ui->w1->setBackgroundColor(QColor(60, 80, 100));
    ui->w1->setRange(0, 100);
    ui->w1->setPercentStyle(QQtCustomEffectProgressBar::PercentStyle_Arc_Polo);

    ui->w2->setBackgroundColor(QColor(20, 40, 100));
    ui->w2->setPercentStyle(QQtCustomEffectProgressBar::PercentStyle_Wave);
    ui->w2->setRange(0, 80);
    ui->w2->setWaveDensity(2);
    ui->w2->setWaveDirection(QQtCustomEffectProgressBar::WaveDirection_Left_Right);
    ui->w2->setWaveHeight(2);
    ui->w2->setWaveSpeed(6);
    //ui->w2->setCircleType(QQtCustomEffectProgressBar::CircleType_Image);
    //ui->w2->setCircleImage("./xxtest.png");

    ui->w5->setRange(0, 100);
    ui->w5->setDesignStyle(QQtCustomEffectProgressBar::DesignStyle_Ellipse);
    ui->w5->setBackgroundColor(QColor(36, 80, 100));
    ui->w5->setRange(0, 100);
    ui->w5->setPercentStyle(QQtCustomEffectProgressBar::PercentStyle_Arc);

    ui->w6->setRange(0, 100);
    ui->w6->setDesignStyle(QQtCustomEffectProgressBar::DesignStyle_Ellipse);
    ui->w6->setBackgroundColor(QColor(36, 80, 100));
    ui->w6->setRange(0, 100);
    ui->w6->setPercentStyle(QQtCustomEffectProgressBar::PercentStyle_Polo);

    ui->w3->setRange(0, 100);
    ui->w3->setDesignStyle(QQtCustomEffectProgressBar::DesignStyle_Ellipse);
    ui->w3->setBackgroundColor(QColor(36, 80, 100));
    ui->w3->setRange(0, 100);
    ui->w3->setPercentStyle(QQtCustomEffectProgressBar::PercentStyle_Arc_Polo);

    ui->w4->setRange(0, 80);
    ui->w4->setDesignStyle(QQtCustomEffectProgressBar::DesignStyle_Ellipse);
    ui->w4->setBackgroundColor(QColor(20, 40, 100));
    ui->w4->setWaveDensity(2);
    ui->w4->setWaveDirection(QQtCustomEffectProgressBar::WaveDirection_Left_Right);
    ui->w4->setWaveHeight(2);
    ui->w4->setWaveSpeed(6);
    ui->w4->setPercentStyle(QQtCustomEffectProgressBar::PercentStyle_Wave);

    ui->w40->setRange(0, 100);
    ui->w40->setDesignStyle(QQtCustomEffectProgressBar::DesignStyle_Rectangle);
    ui->w40->setBackgroundColor(QColor(36, 80, 100));
    ui->w40->setRange(0, 100);
    ui->w40->setPercentStyle(QQtCustomEffectProgressBar::PercentStyle_Arc);

    ui->w41->setRange(0, 100);
    ui->w41->setDesignStyle(QQtCustomEffectProgressBar::DesignStyle_Rectangle);
    ui->w41->setBackgroundColor(QColor(36, 80, 100));
    ui->w41->setRange(0, 100);
    ui->w41->setPercentStyle(QQtCustomEffectProgressBar::PercentStyle_Polo);

    ui->w42->setRange(0, 100);
    ui->w42->setDesignStyle(QQtCustomEffectProgressBar::DesignStyle_Rectangle);
    ui->w42->setBackgroundColor(QColor(36, 80, 100));
    ui->w42->setRange(0, 100);
    ui->w42->setPercentStyle(QQtCustomEffectProgressBar::PercentStyle_Arc_Polo);

    ui->w43->setRange(0, 80);
    ui->w43->setDesignStyle(QQtCustomEffectProgressBar::DesignStyle_Rectangle);
    ui->w43->setBackgroundColor(QColor(20, 40, 100));
    ui->w43->setWaveDensity(2);
    ui->w43->setWaveDirection(QQtCustomEffectProgressBar::WaveDirection_Left_Right);
    ui->w43->setWaveHeight(2);
    ui->w43->setWaveSpeed(6);
    ui->w43->setPercentStyle(QQtCustomEffectProgressBar::PercentStyle_Wave);

    ui->w50->setRange(0, 100);
    ui->w50->setDesignStyle(QQtCustomEffectProgressBar::DesignStyle_Square);
    ui->w50->setBackgroundColor(QColor(36, 80, 100));
    ui->w50->setRange(0, 100);
    ui->w50->setPercentStyle(QQtCustomEffectProgressBar::PercentStyle_Arc);

    ui->w51->setRange(0, 100);
    ui->w51->setDesignStyle(QQtCustomEffectProgressBar::DesignStyle_Square);
    ui->w51->setBackgroundColor(QColor(36, 80, 100));
    ui->w51->setRange(0, 100);
    ui->w51->setPercentStyle(QQtCustomEffectProgressBar::PercentStyle_Polo);

    ui->w52->setRange(0, 100);
    ui->w52->setDesignStyle(QQtCustomEffectProgressBar::DesignStyle_Square);
    ui->w52->setBackgroundColor(QColor(36, 80, 100));
    ui->w52->setRange(0, 100);
    ui->w52->setPercentStyle(QQtCustomEffectProgressBar::PercentStyle_Arc_Polo);

    ui->w53->setRange(0, 80);
    ui->w53->setDesignStyle(QQtCustomEffectProgressBar::DesignStyle_Square);
    ui->w53->setBackgroundColor(QColor(20, 40, 100));
    ui->w53->setWaveDensity(2);
    ui->w53->setWaveDirection(QQtCustomEffectProgressBar::WaveDirection_Left_Right);
    ui->w53->setWaveHeight(2);
    ui->w53->setWaveSpeed(6);
    ui->w53->setPercentStyle(QQtCustomEffectProgressBar::PercentStyle_Wave);

    //ui->w60->setRange(0, 100);
    //ui->w60->setValue(100);

    connect(ui->hs0, SIGNAL(valueChanged(int)), ui->w01, SLOT(setValue(int)));
    connect(ui->hs0, SIGNAL(valueChanged(int)), ui->w0, SLOT(setValue(int)));
    connect(ui->hs0, SIGNAL(valueChanged(int)), ui->w1, SLOT(setValue(int)));
    connect(ui->hs0, SIGNAL(valueChanged(int)), ui->w2, SLOT(setValue(int)));
    connect(ui->hs0, SIGNAL(valueChanged(int)), ui->w3, SLOT(setValue(int)));
    connect(ui->hs0, SIGNAL(valueChanged(int)), ui->w4, SLOT(setValue(int)));
    connect(ui->hs0, SIGNAL(valueChanged(int)), ui->w5, SLOT(setValue(int)));
    connect(ui->hs0, SIGNAL(valueChanged(int)), ui->w6, SLOT(setValue(int)));
    connect(ui->hs0, SIGNAL(valueChanged(int)), ui->w40, SLOT(setValue(int)));
    connect(ui->hs0, SIGNAL(valueChanged(int)), ui->w41, SLOT(setValue(int)));
    connect(ui->hs0, SIGNAL(valueChanged(int)), ui->w42, SLOT(setValue(int)));
    connect(ui->hs0, SIGNAL(valueChanged(int)), ui->w43, SLOT(setValue(int)));
    connect(ui->hs0, SIGNAL(valueChanged(int)), ui->w50, SLOT(setValue(int)));
    connect(ui->hs0, SIGNAL(valueChanged(int)), ui->w51, SLOT(setValue(int)));
    connect(ui->hs0, SIGNAL(valueChanged(int)), ui->w52, SLOT(setValue(int)));
    connect(ui->hs0, SIGNAL(valueChanged(int)), ui->w53, SLOT(setValue(int)));
    connect(ui->hs0, SIGNAL(valueChanged(int)), ui->w60, SLOT(setValue(int)));

    connect(ui->hs0, SIGNAL(valueChanged(int)), ui->w7, SLOT(setValue(int)));
    connect(ui->hs0, SIGNAL(valueChanged(int)), ui->w8, SLOT(setValue(int)));

    connect(ui->hs0, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));

    ui->hs0->installEventFilter(this);

    m_timer = new QTimer(this);
    m_timer->setSingleShot(false);

    m_timer_down = new QTimer(this);
    m_timer_down->setSingleShot(false);

    connect(m_timer_down, SIGNAL(timeout()), this, SLOT(setValueDown()));
    connect(m_timer, SIGNAL(timeout()), this, SLOT(setValue()));

    m_timer_down->start(10);

    /*
    ui->w60->setFixedHeight(30);
    QQtSlideEffectTabBar* bar = new QQtSlideEffectTabBar(ui->tab_6);
    QQtSlideEffectTabBar* bar2 = new QQtSlideEffectTabBar(ui->tab_6);
    bar->addTab("xxx");
    bar->addTab("ccc");
    bar2->setShape(QQtSlideEffectTabBar::RoundedEast);
    bar2->addTab("yyy");
    bar2->addTab("ddd");

    QSpacerItem* space = new QSpacerItem(800, 30, QSizePolicy::Maximum);
    QGridLayout* lay = new QGridLayout(ui->tab_6);
    lay->addWidget(ui->w60, 1, 1, 1, 2);
    lay->addWidget(bar, 2, 1, 1, 2);
    lay->addWidget(bar2, 3, 1, 1, 1);
    lay->addItem(space, 3, 2, 1, 1);

    ui->tab_6->setLayout(lay);
    */
    /*
    QQtSlideEffectTabBar* bar2 = new QQtSlideEffectTabBar(ui->tab_6);
    ui->tb1->setTabBar(bar2);
    */
    //QQtSlideEffectTabBar* bar = new QQtSlideEffectTabBar(ui->tb0);
    //ui->tb0->setTabBar(bar);
    //ui->tb0->setObjectName("tb0");

    ui->w77->addTab("ddd");
    ui->w77->addTab("xxxx");
    ui->w77->setFixedHeight(28);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setValue(int value)
{
    this->value = value;
}

void MainWindow::setValue()
{
    //pline() << value;
    if (value > curmaxValue)
        return;

    if (value < curmaxValue)
        value++;

    ui->hs0->setValue(value);
}

void MainWindow::setValueDown()
{
    if (value > 0)
        value--;
    ui->hs0->setValue(value);
}


void MainWindow::keyPressEvent(QKeyEvent* event)
{
    //pline() << hex << event->key();
    if (event->key() == Qt::Key_Up)
    {
        m_timer_down->stop();
        m_timer->start(10);
        event->accept();
    }

    QMainWindow::keyPressEvent(event);

}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Up)
    {
        m_timer_down->start(10);
        m_timer->stop();
        event->accept();
    }
    QMainWindow::keyReleaseEvent(event);
}

bool MainWindow::eventFilter(QObject* watched, QEvent* event)
{
    if (event->type() != QEvent::Paint)
        ;//pline() << watched << hex << event->type();
    if (watched == ui->hs0)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent* e = (QMouseEvent*)event;
            //pline() << hex << e->button();
            if (e->button() == Qt::LeftButton)
            {
                curmaxValue = ui->hs0->minimum() + (ui->hs0->maximum() - ui->hs0->minimum()) * e->x() / ui->hs0->width();
                m_timer_down->stop();
                m_timer->start(10);
                // not necessary because of the bug later.
                event->accept();
                // bug:in theory this return is not necessary, after accept, parent won't handle this e continue;
                // but, it handled. handled once, but child has no action any.
                // then, use return ,don't goto parent, well to use.
                return true;
            }
        }
        if (event->type() == QEvent::MouseButtonRelease)
        {
            QMouseEvent* e = (QMouseEvent*)event;
            //pline() << hex << e->button();
            if (e->button() == Qt::LeftButton)
            {
                curmaxValue = 80;
                m_timer->stop();
                m_timer_down->start(10);
                event->accept();
                /*!
                 * linux
                 * after click slider, all key event come here....
                 * because, focus hasn't coming back,
                 * but on mac, focus has coming back.
                !*/
                ui->w0->setFocus();
                return true;
            }
        }
        if (event->type() == QEvent::MouseMove)
        {
            QMouseEvent* e = (QMouseEvent*)event;
            //pline() << hex << e->button();
            if (e->button() == Qt::NoButton)
            {
                curmaxValue = ui->hs0->minimum() + (ui->hs0->maximum() - ui->hs0->minimum()) * e->x() / ui->hs0->width();
                value = curmaxValue - 1;
                //pline() << curmaxValue;
                event->accept();
                return true;
            }
        }
        /*fix the parent handled bug terminally*/
        if (event->type() == QEvent::Paint)
        {
            return QMainWindow::eventFilter(watched, event);
        }
        //+ fix bug
        return true;
    }
    return QMainWindow::eventFilter(watched, event);
}
