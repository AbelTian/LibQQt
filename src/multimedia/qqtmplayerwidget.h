#ifndef QQTMPLAYERWIDGET_H
#define QQTMPLAYERWIDGET_H

#include <QWidget>
#include <QTimer>
#include "qqtmplayer.h"

namespace Ui {
class QQtMPlayerWidget;
}

class QQtMPlayerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QQtMPlayerWidget ( QWidget* parent = 0 );
    ~QQtMPlayerWidget();

    void setSourceFile ( const QString& filename );

    void stop() {
        on_btn_stop_clicked();
    }

private slots:
    void on_toolButton_mute_clicked();

    void posChanged();

    void on_btn_play_clicked();

    void on_btn_stop_clicked();

    void on_sliderVol_valueChanged ( int value );

    void on_btn_mute_toggled ( bool checked );

private:
    Ui::QQtMPlayerWidget* ui;

    QString m_filename;
    QQtMPlayer* app;
    QTimer* timer;
    quint8 m_bplayed;
    int m_startPos;
    int m_vol;
};

#endif // QQTMPLAYERWIDGET_H
