#ifndef TABELLONE_H
#define TABELLONE_H

#include <QString>
#include <QChar>
#include <vector>
#include <QMessageBox>
#include "dict.h"
#include "legenda.h"

using namespace::std;

class Tabellone
{
public:
    Tabellone();

    int calcolaPunteggio();                 // calcola il punteggio con le lettere inserite nell'ultimo turno

    bool isNear(int x, int y);              // ritorna vero se la casella x_y è vicina ad un'altra casella con al suo interno una lettera

    int firstUp(int x, int y);              // ritorna la distanza della prima casella libera a destra/alto/basso/sinistra della casella x_y
    int firstRight(int x, int y);           // nel caso in cui ritorni 0, non ci sono caselle libere
    int firstDown(int x, int y);
    int firstLeft(int x, int y);

    void setNuovaLetteraValue(bool value, int x, int y);        // assegna alla casella x_y il valore value
    void setLetteraValue(QChar value,int x, int y);             // assegna alla casella x_y il valore value
    void setJollyValue(bool value, int x, int y);               // assegna alla casella x_y il valore value

    // getters and setters
    vector<vector<unsigned int> > getCampo() const;
    void setCampo(const vector<vector<unsigned int> > &value);

    vector<vector<QChar> > getLettere() const;
    void setLettere(const vector<vector<QChar> > &value);

    vector<vector<bool> > getNuovaLettera() const;
    void setNuovaLettera(const vector<vector<bool> > &value);

    vector<vector<bool> > getJolly() const;
    void setJolly(const vector<vector<bool> > &value);

private:
    vector<vector<unsigned int>> campo;     // rappresenta il tabellone con le relative caselle
    vector<vector<QChar>> lettere;          // rappresenta le lettere posizionate sul campo da gioco
    vector<vector<bool>> nuovaLettera;      // indica quali sono le lettere inserite nel turno corrente
    vector<vector<bool>> jolly;             // indica quali sono le lettere corrispondenti ad un jolly
};

#endif // TABELLONE_H
