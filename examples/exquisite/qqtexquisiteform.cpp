#include "qqtexquisiteform.h"
#include "ui_qqtexquisiteform.h"

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
    connect(ui->hs0, SIGNAL(valueChanged(int)), ui->w0, SLOT(setValue(int)));
    connect(ui->hs0, SIGNAL(valueChanged(int)), ui->w2, SLOT(setValue(int)));
    connect(ui->hs0, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));
    m_timer = new QTimer(this);
    m_timer->setSingleShot(false);

    m_t1 = new QTimer(this);
    m_t1->setSingleShot(false);

    connect(m_t1, SIGNAL(timeout()), this, SLOT(setValueDown()));
    connect(m_timer, SIGNAL(timeout()), this, SLOT(setValue()));

    value = 0;
    m_t1->start(10);
}

QQtExquisiteForm::~QQtExquisiteForm()
{
    delete ui;
}

void QQtExquisiteForm::setValue(int value)
{
    this->value = value;
}

void QQtExquisiteForm::setValue()
{
    if(value < 80)
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
        m_t1->stop();
        m_timer->start(10);
        event->accept();
    }

    QDialog::keyPressEvent(event);

}

void QQtExquisiteForm::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Up) {
        m_t1->start(10);
        m_timer->stop();
        event->accept();
    }
    QDialog::keyReleaseEvent(event);
}
