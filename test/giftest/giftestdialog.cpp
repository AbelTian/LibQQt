#include "giftestdialog.h"
#include "ui_giftestdialog.h"

GifTestDialog::GifTestDialog ( QWidget* parent ) :
    QDialog ( parent ),
    ui ( new Ui::GifTestDialog )
{
    ui->setupUi ( this );
    ui->labelGif->setGifFile ( "./waiting.gif" );
    pline() << QMovie::supportedFormats();
}

GifTestDialog::~GifTestDialog()
{
    delete ui;
}
