#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <QKeyEvent>
#include <qqtcore.h>
#include <qcustomplot.h>
#include <QTime>

QCPGraph* g0 = NULL;
QTime start;

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    value = 0;
    curmaxValue = 80;

    ui->hs0->setRange(0, 100);


    connect(ui->hs0, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));

    ui->hs0->installEventFilter(this);

    m_timer = new QTimer(this);
    m_timer->setSingleShot(false);

    m_timer_down = new QTimer(this);
    m_timer_down->setSingleShot(false);

    connect(m_timer_down, SIGNAL(timeout()), this, SLOT(setValueDown()));
    connect(m_timer, SIGNAL(timeout()), this, SLOT(setValue()));

    m_timer_down->start(10);

    ui->w99->xAxis->setTickLabelType(QCPAxis::ltNumber);
    ui->w99->xAxis->setAutoTickStep(true);
    ui->w99->xAxis->setTickStep(5);
    ui->w99->xAxis->setRange(0, 100);
    ui->w99->yAxis->setRange(0, 200);

    g0 = ui->w99->addGraph(ui->w99->xAxis, ui->w99->yAxis);
    start = QTime::currentTime();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setValue(int value)
{
    this->value = value;

    QTime ecl = QTime::currentTime();
    int key = -ecl.msecsTo(start) / 10;
    g0->addData(key, ui->hs0->value());
    ui->w99->xAxis->setRange(0, key + 100, Qt::AlignLeft);
    ui->w99->replot();
    //pline() << key;
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
                ui->w99->setFocus();
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
