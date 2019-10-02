#include "mazzo.h"

Mazzo::Mazzo()
{
    finito = false;
    // NB: gli asterischi equivalgono ai jolly
    carte =  "AAAAAAAAAAAAEEEEEEEEEEEEIIIIIIIIIIIIOOOOOOOOOOOOUUUUCCCCCCCRRRRRRRSSSSSSSTTTTTTTLLLLLLMMMMMMNNNNNNBBBBDDDDFFFFGGGGPPPPVVVVHHQQZZ**";
}

QString Mazzo::getCarte() const
{
    return carte;
}

void Mazzo::setCarte(const QString &value)
{
    carte = value;
}

bool Mazzo::getFinito() const
{
    return finito;
}

void Mazzo::setFinito(bool value)
{
    finito = value;
}

QChar Mazzo::pesca()
{
    QChar prima = carte.at(0);      // prendo la prima carta
    carte = carte.remove(0,1);      // la rimuovo dal mazzo
    if (carte.length() == 0)        // se non ci sono più carte il mazzo è finito
        finito = true;
    return prima;                   // la restituisco
}

int Mazzo::getNumeroCarte()
{
    return carte.length();
}

void Mazzo::mescola()
{
    int n1,n2;
    QChar temp;
    srand (time(NULL));

    // ciclo per mescolare
    for (int x = 0; x < carte.length() * 2; x++)
    {
        // genero gli indici da scambiare
        n1 = rand() % carte.length();
        n2 = rand() % carte.length();

        // scambio
        temp = carte[n1];
        carte[n1] = carte[n2];
        carte[n2] = temp;
    }

}
