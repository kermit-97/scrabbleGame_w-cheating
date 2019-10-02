#include "giocatore.h"

Giocatore::Giocatore()
{
    punteggio = 0;
}

QString Giocatore::getNome() const
{
    return nome;
}

void Giocatore::setNome(const QString &value)
{
    nome = value;
}

unsigned int Giocatore::getPunteggio() const
{
    return punteggio;
}

void Giocatore::setPunteggio(unsigned int value)
{
    punteggio = value;
}

QString Giocatore::getCarte() const
{
    return carte;
}

void Giocatore::setCarte(const QString &value)
{
    carte = value;
}

void Giocatore::aggiungi_carta(QChar carta)
{
    carte.append(carta);    // aggiungo la carta alla mano del giocatore
    qSort(carte.begin(),carte.end());   // ordino le carte del giocatore
}
