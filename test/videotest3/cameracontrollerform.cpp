#include "cameracontrollerform.h"
#include "ui_cameracontrollerform.h"
#include <qqtcore.h>

CameraControllerForm::CameraControllerForm ( QWidget* parent ) :
    QWidget ( parent ),
    ui ( new Ui::CameraControllerForm )
{
    ui->setupUi ( this );
    ui->horizontalSlider->setRange ( 0, 10000 );
    ui->horizontalSlider->setSingleStep ( 200 );
}

CameraControllerForm::~CameraControllerForm()
{
    delete ui;
}

void CameraControllerForm::on_radioButton_toggled ( bool checked )
{
    if ( checked )
        emit isomodel ( false );
    pline() << checked;
}

void CameraControllerForm::on_radioButton_2_toggled ( bool checked )
{
    if ( checked )
        emit isomodel ( true );
    pline() << checked;
}

void CameraControllerForm::on_horizontalSlider_valueChanged ( int value )
{
    pline() << value;
    emit isovalue ( value );
}
