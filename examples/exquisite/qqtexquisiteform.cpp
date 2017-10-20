#include "qqtexquisiteform.h"
#include "ui_qqtexquisiteform.h"

#include <QMouseEvent>
#include <QKeyEvent>
#include <qqtcore.h>

QQtExquisiteForm::QQtExquisiteForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QQtExquisiteForm)
{
    ui->setupUi(this);
    ui->hs0->setRange(0, 100);

    ui->w0->setMinValue(0);
    ui->w0->setMaxValue(80);


    ui->w2->setRange(0, 80);
    //ui->w2->setCircleType(QQtCustomProgressBar::CircleType_Image);
    //ui->w2->setCircleImage("./xxtest.png");
    ui->w2->setCircleColor(QColor(20, 40, 100));

    connect(ui->hs0, SIGNAL(valueChanged(int)), ui->w0, SLOT(setValue(int)));
    connect(ui->hs0, SIGNAL(valueChanged(int)), ui->w2, SLOT(setValue(int)));
    m_timer = new QTimer(this);
    m_timer->setSingleShot(false);

    m_timer_down = new QTimer(this);
    m_timer_down->setSingleShot(false);

    connect(m_timer_down, SIGNAL(timeout()), this, SLOT(setValueDown()));
    connect(m_timer, SIGNAL(timeout()), this, SLOT(setValue()));

    value = 0;
    curmaxValue = 80;
    m_timer_down->start(10);

    ui->hs0->installEventFilter(this);
}

QQtExquisiteForm::~QQtExquisiteForm()
{
    delete ui;
}

void QQtExquisiteForm::setValue()
{
    if(value>curmaxValue)
        return;

    if(value < curmaxValue)
        value++;

    ui->hs0->setValue(value);
}

void QQtExquisiteForm::setValueDown()
{
    if(value > 0)
        value--;
    ui->hs0->setValue(value);
}


void QQtExquisiteForm::keyPressEvent(QKeyEvent *event)
{
    //pline() << hex << event->key();
    if(event->key() == Qt::Key_Up) {
        m_timer_down->stop();
        m_timer->start(10);
        event->accept();
    }

    QDialog::keyPressEvent(event);

}

void QQtExquisiteForm::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Up) {
        m_timer_down->start(10);
        m_timer->stop();
        event->accept();
    }
    QDialog::keyReleaseEvent(event);
}

bool QQtExquisiteForm::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->hs0){
        if(event->type() == QEvent::MouseButtonPress) {
            QMouseEvent* e = (QMouseEvent*)event;
            //pline() << hex << e->button();
            if(e->button() == Qt::LeftButton) {
                curmaxValue = ui->hs0->minimum() + (ui->hs0->maximum()-ui->hs0->minimum()) * e->x() / ui->hs0->width();
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
        if(event->type() == QEvent::MouseButtonRelease) {
            QMouseEvent* e = (QMouseEvent*)event;
            //pline() << hex << e->button();
            if(e->button() == Qt::LeftButton) {
                curmaxValue = 80;
                m_timer->stop();
                m_timer_down->start(10);
                event->accept();
            }
        }
    }
    return QDialog::eventFilter(watched, event);
}
