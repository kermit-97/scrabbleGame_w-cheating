#include "jolly_dialog.h"
#include "ui_jolly_dialog.h"

Jolly_Dialog::Jolly_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Jolly_Dialog)
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

    for (int x = 0; x < ui->gridLayout->count(); x++)
    {
        QPushButton *button = qobject_cast<QPushButton*>(ui->gridLayout->itemAt(x)->widget());
        button->setFlat(true);
        button->setAutoFillBackground(true);
        button->setPalette(palette_button);
    }
}

Jolly_Dialog::~Jolly_Dialog()
{
    delete ui;
}

void Jolly_Dialog::on_pushButton_clicked()
{
    sendLetter('A');
    this->close();
}

void Jolly_Dialog::on_pushButton_2_clicked()
{
    sendLetter('B');
    this->close();
}

void Jolly_Dialog::on_pushButton_3_clicked()
{
    sendLetter('C');
    this->close();
}

void Jolly_Dialog::on_pushButton_4_clicked()
{
    sendLetter('D');
    this->close();
}

void Jolly_Dialog::on_pushButton_5_clicked()
{
    sendLetter('E');
    this->close();
}

void Jolly_Dialog::on_pushButton_6_clicked()
{
    sendLetter('F');
    this->close();
}

void Jolly_Dialog::on_pushButton_7_clicked()
{
    sendLetter('G');
    this->close();
}

void Jolly_Dialog::on_pushButton_8_clicked()
{
    sendLetter('H');
    this->close();
}

void Jolly_Dialog::on_pushButton_9_clicked()
{
    sendLetter('I');
    this->close();
}

void Jolly_Dialog::on_pushButton_10_clicked()
{
    sendLetter('L');
    this->close();
}

void Jolly_Dialog::on_pushButton_11_clicked()
{
    sendLetter('M');
    this->close();
}

void Jolly_Dialog::on_pushButton_12_clicked()
{
    sendLetter('N');
    this->close();
}

void Jolly_Dialog::on_pushButton_13_clicked()
{
    sendLetter('O');
    this->close();
}

void Jolly_Dialog::on_pushButton_14_clicked()
{
    sendLetter('P');
    this->close();
}

void Jolly_Dialog::on_pushButton_15_clicked()
{
    sendLetter('Q');
    this->close();
}

void Jolly_Dialog::on_pushButton_16_clicked()
{
    sendLetter('R');
    this->close();
}

void Jolly_Dialog::on_pushButton_17_clicked()
{
    sendLetter('S');
    this->close();
}

void Jolly_Dialog::on_pushButton_18_clicked()
{
    sendLetter('T');
    this->close();
}

void Jolly_Dialog::on_pushButton_19_clicked()
{
    sendLetter('U');
    this->close();
}

void Jolly_Dialog::on_pushButton_20_clicked()
{
    sendLetter('V');
    this->close();
}

void Jolly_Dialog::on_pushButton_21_clicked()
{
    sendLetter('Z');
    this->close();
}
