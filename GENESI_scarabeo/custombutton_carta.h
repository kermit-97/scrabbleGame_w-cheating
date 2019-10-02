#ifndef CUSTOMBUTTON_CARTA_H
#define CUSTOMBUTTON_CARTA_H

#include <QPushButton>
#include <QString>
#include <QChar>

using namespace std;

class CustomButton_carta : public QPushButton
{
    Q_OBJECT

public:
     explicit CustomButton_carta(QWidget *parent = 0);

    // getter and setters
    QChar getLettera() const;
    void setLettera(const QChar &value);

private:
    QChar lettera;      // lettera associata alla carta
};


#endif // CUSTOMBUTTON_CARTA_H
