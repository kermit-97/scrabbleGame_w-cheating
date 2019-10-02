#include "custombutton_carta.h"

CustomButton_carta::CustomButton_carta(QWidget *parent) :
    QPushButton(parent)
{
}

QChar CustomButton_carta::getLettera() const
{
    return lettera;
}

void CustomButton_carta::setLettera(const QChar &value)
{
    lettera = value;
}
