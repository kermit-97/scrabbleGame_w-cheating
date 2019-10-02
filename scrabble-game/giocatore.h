#ifndef GIOCATORE_H
#define GIOCATORE_H

#include <QString>
#include <QtAlgorithms>

class Giocatore
{
public:
    Giocatore();

    void aggiungi_carta(QChar carta);       // aggiunge la carta alla mano del giocatore

    // getter and setters
    QString getNome() const;
    void setNome(const QString &value);

    unsigned int getPunteggio() const;
    void setPunteggio(unsigned int value);

    QString getCarte() const;
    void setCarte(const QString &value);

private:
    QString nome;               // nome del giocatore
    unsigned int punteggio;     // punteggio del giocatore
    QString carte;              // carte in possesso del giocatore
};

#endif // GIOCATORE_H
