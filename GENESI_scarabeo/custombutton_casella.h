#ifndef CUSTOMBUTTON_CASELLA_H
#define CUSTOMBUTTON_CASELLA_H

#include <QPushButton>
#include <QString>
#include <QChar>

using namespace std;

class CustomButton_casella : public QPushButton
{
    Q_OBJECT

public:
     explicit CustomButton_casella(QWidget *parent = 0);

    // getter and setters
    unsigned int getCasella() const;
    void setCasella(unsigned int value);

    int getCoord_y() const;
    void setCoord_y(int value);

    int getCoord_x() const;
    void setCoord_x(int value);

    QChar getLettera() const;
    void setLettera(const QChar &value);

    bool getIsNew() const;
    void setIsNew(bool value);

    bool getIsJolly() const;
    void setIsJolly(bool value);

private:
    int coord_x;            // coordinata x della cella in cui si trova la casella
    int coord_y;            // coordinata y della cella in cui si trova la casella
    unsigned int casella;   // tipo di casella
    bool isNew;             // indica se la lettera associata alla casella è stata posizionata in questo turno
    bool isJolly;           // indica se la lettera è un jolly
    QChar lettera;          // lettera associata alla casella del tabellone

signals:
    void send_clicked();        // manda un segnale alla mainwindow che una casella è stata cliccata
private slots:
    void handle_clicked();      // gestisce quando un bottone viene premuto
};


#endif // CUSTOMBUTTON_CASELLA_H
