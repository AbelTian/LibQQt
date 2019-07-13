#ifndef CAMERACONTROLLERFORM_H
#define CAMERACONTROLLERFORM_H

#include <QWidget>

namespace Ui {
class CameraControllerForm;
}

class CameraControllerForm : public QWidget
{
    Q_OBJECT

public:
    explicit CameraControllerForm ( QWidget* parent = 0 );
    ~CameraControllerForm();

signals:
    //auto:true, manual:false
    void isomodel ( bool );
    void isovalue ( int );

private slots:
    void on_radioButton_toggled ( bool checked );

    void on_radioButton_2_toggled ( bool checked );

    void on_horizontalSlider_valueChanged ( int value );

private:
    Ui::CameraControllerForm* ui;
};

#endif // CAMERACONTROLLERFORM_H
