#include "qqtmplayerwidget.h"
#include "ui_qqtmplayerwidget.h"

#include <QLabel>
#include <QSlider>

QQtMPlayerWidget::QQtMPlayerWidget ( QWidget* parent ) :
    QWidget ( parent ),
    ui ( new Ui::QQtMPlayerWidget )
{
    ui->setupUi ( this );

    m_bplayed = 0;
    app = new QQtMPlayer ( this );
    timer = new QTimer ( this );
    timer->setSingleShot ( false );
    connect ( timer, SIGNAL ( timeout() ), this, SLOT ( posChanged() ) );

    int min = 1331 / 60;
    int sec = 1331 % 60;
    ui->label_timelength->setText ( QString ( "%1:%2" )
                                    .arg ( min, 2, 10, QLatin1Char ( '0' ) )
                                    .arg ( sec, 2, 10, QLatin1Char ( '0' ) ) );
    ui->label_timepos->hide();
    ui->horizontalSlider_seek->hide();
    ui->btn_stop->hide();
    //ui->horizontalSlider_seek->setRange(0, 1331);


    ui->label_timepos->setFixedWidth ( 45 );
    ui->label_timelength->setFixedWidth ( 45 );
    pline() << ui->label_timelength->text();

    m_vol = 26;
    ui->sliderVol->setRange ( 0, 35 );
    ui->sliderVol->setValue ( m_vol );

    //ui->btn_mute->set
}

QQtMPlayerWidget::~QQtMPlayerWidget()
{
    delete ui;
}

void QQtMPlayerWidget::setSourceFile ( const QString& filename )
{
    m_filename = filename;
}

void QQtMPlayerWidget::on_toolButton_mute_clicked()
{
    static bool m = false;
    m = ~m;
    app->mute ( m );
}

void QQtMPlayerWidget::posChanged()
{
    return;

    double curpos = app->timePos();

    if ( curpos >= 1331 )
        app->stop();

    int nowPos = qRound ( curpos );

    int min = nowPos / 60;
    int sec = nowPos - min * 60;

    ui->label_timepos->setText ( QString ( "%1:%2" )
                                 .arg ( min, 2, 10, QLatin1Char ( '0' ) )
                                 .arg ( sec, 2, 10, QLatin1Char ( '0' ) ) );
    //ui->horizontalSlider_seek->setValue(curpos);

    if ( m_startPos < 6 )
    {
        m_startPos++;
        int min = m_startPos / 60;
        int sec = m_startPos - min * 60;
        ui->label_timepos->setText ( QString ( "%1:%2" )
                                     .arg ( min, 2, 10, QLatin1Char ( '0' ) )
                                     .arg ( sec, 2, 10, QLatin1Char ( '0' ) ) );
        //ui->horizontalSlider_seek->setValue(m_startPos);
        update();
    }

    pline() << ui->label_timepos->text();
}

void QQtMPlayerWidget::on_btn_play_clicked()
{
    if ( 0 == m_bplayed )
    {
        m_bplayed = 1;
        ui->btn_play->setText ( tr ( "Stop" ) );

        app->play ( m_filename, this->winId() );
        QPoint point ( ui->widget_show->rect().left(), ui->widget_show->rect().top() );
        app->setRect ( ui->widget_show->mapToGlobal ( point ).x(), ui->widget_show->mapToGlobal ( point ).y(),
                       ui->widget_show->rect().width(), ui->widget_show->rect().height() );
        ui->sliderVol->setValue ( m_vol );
    }
    else if ( 1 == m_bplayed )
    {
        m_bplayed = 0;
        ui->btn_play->setText ( tr ( "Play" ) );
        app->stop();
    }

    update();

    return;

    if ( 0 == m_bplayed )
    {
        m_bplayed = 1;
        app->play ( m_filename, this->winId() );
        QPoint point ( ui->widget_show->rect().left(), ui->widget_show->rect().top() );
        app->setRect ( ui->widget_show->mapToGlobal ( point ).x(), ui->widget_show->mapToGlobal ( point ).y(),
                       ui->widget_show->rect().width(), ui->widget_show->rect().height() );
        ui->sliderVol->setValue ( m_vol );
        //ui->horizontalSlider_seek->setValue(0);
        timer->start ( 1000 );
        m_startPos = -1;
        ui->btn_play->setText ( tr ( "Pause" ) );
    }
    else if ( 1 == m_bplayed )
    {
        m_bplayed = 2;
        timer->stop();
        app->pause();
        ui->btn_play->setText ( tr ( "Play" ) );
    }
    else if ( 2 == m_bplayed )
    {
        m_bplayed = 1;
        timer->start ( 1000 );
        app->pause();
        ui->btn_play->setText ( tr ( "Pause" ) );
    }
}

void QQtMPlayerWidget::on_btn_stop_clicked()
{
    if ( m_bplayed == 0 )
        return;

    m_bplayed = 0;
    //ui->horizontalSlider_seek->setValue(0);
    ui->label_timepos->setText ( "00:00" );
    timer->stop();
    app->stop();

    ui->btn_play->setText ( tr ( "Play" ) );
}


void QQtMPlayerWidget::on_sliderVol_valueChanged ( int value )
{
    app->setVolume ( value );
    m_vol = value;
}

void QQtMPlayerWidget::on_btn_mute_toggled ( bool checked )
{
    app->mute ( checked ? true : false );
    pline() << checked;
}
