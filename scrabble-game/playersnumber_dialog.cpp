#include "playersnumber_dialog.h"
#include "ui_playersnumber_dialog.h"

playersNumber_Dialog::playersNumber_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::playersNumber_Dialog)
{
    ui->setupUi(this);

    // questo codice viene utilizzato per l'immagine di sfondo
    QPixmap bkgnd_dialog(":/images/F4F1DE.png");   // con ":" mi riferisco alle mie risorse (v. Resources e file qrc)
    bkgnd_dialog = bkgnd_dialog.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette_dialog;
    palette_dialog.setBrush(QPalette::Window, bkgnd_dialog);
    this->setPalette(palette_dialog);

    // immagine applicata sui bottoni
    QPixmap bkgnd_button(":/images/FFFFFF.png");   // con ":" mi riferisco alle mie risorse (v. Resources e file qrc)
    bkgnd_button = bkgnd_button.scaled(ui->pushButton->size(), Qt::IgnoreAspectRatio);
    QPalette palette_button;
    palette_button.setBrush(QPalette::Button, bkgnd_button);
    ui->pushButton->setFlat(true);
    ui->pushButton->setAutoFillBackground(true);
    ui->pushButton->setPalette(palette_button);

    ui->pushButton_2->setFlat(true);
    ui->pushButton_2->setAutoFillBackground(true);
    ui->pushButton_2->setPalette(palette_button);

    ui->pushButton_3->setFlat(true);
    ui->pushButton_3->setAutoFillBackground(true);
    ui->pushButton_3->setPalette(palette_button);
}

playersNumber_Dialog::~playersNumber_Dialog()
{
    delete ui;
}

void playersNumber_Dialog::on_pushButton_clicked()
{
    sendPlayersNumber(2);
    this->close();
}

void playersNumber_Dialog::on_pushButton_2_clicked()
{
    sendPlayersNumber(3);
    this->close();
}

void playersNumber_Dialog::on_pushButton_3_clicked()
{
    sendPlayersNumber(4);
    this->close();
}
