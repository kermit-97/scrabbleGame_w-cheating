#include "custombutton_casella.h"

CustomButton_casella::CustomButton_casella(QWidget *parent) :
    QPushButton(parent)
{
}

unsigned int CustomButton_casella::getCasella() const
{
    return casella;
}

void CustomButton_casella::setCasella(unsigned int value)
{
    casella = value;
}

int CustomButton_casella::getCoord_y() const
{
    return coord_y;
}

void CustomButton_casella::setCoord_y(int value)
{
    coord_y = value;
}

int CustomButton_casella::getCoord_x() const
{
    return coord_x;
}

void CustomButton_casella::setCoord_x(int value)
{
    coord_x = value;
}

QChar CustomButton_casella::getLettera() const
{
    return lettera;
}

void CustomButton_casella::setLettera(const QChar &value)
{
    lettera = value;
}

bool CustomButton_casella::getIsNew() const
{
    return isNew;
}

void CustomButton_casella::setIsNew(bool value)
{
    isNew = value;
}

bool CustomButton_casella::getIsJolly() const
{
    return isJolly;
}

void CustomButton_casella::setIsJolly(bool value)
{
    isJolly = value;
}

void CustomButton_casella::handle_clicked()
{
    send_clicked();
}
