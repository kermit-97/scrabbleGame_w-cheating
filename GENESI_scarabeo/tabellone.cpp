#include "tabellone.h"

Tabellone::Tabellone()
{
    // inizializzo il mio tabellone
    Legenda *l = new Legenda();

    // il campo da gioco
    vector<vector<unsigned int>> campo_temp {{l->PAROLAx3,l->VUOTO,l->VUOTO,l->VUOTO,l->LETTERAx2,l->VUOTO,l->VUOTO,l->VUOTO,l->PAROLAx3,l->VUOTO,l->VUOTO,l->VUOTO,l->LETTERAx2,l->VUOTO,l->VUOTO,l->VUOTO,l->PAROLAx3},
                                        {l->VUOTO,l->PAROLAx2,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->LETTERAx3,l->VUOTO,l->VUOTO,l->VUOTO,l->LETTERAx3,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->PAROLAx2,l->VUOTO},
                                        {l->VUOTO,l->VUOTO,l->PAROLAx2,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->LETTERAx2,l->VUOTO,l->LETTERAx2,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->PAROLAx2,l->VUOTO,l->VUOTO},
                                        {l->VUOTO,l->VUOTO,l->VUOTO,l->PAROLAx2,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->LETTERAx2,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->PAROLAx2,l->VUOTO,l->VUOTO,l->VUOTO},
                                        {l->LETTERAx2,l->VUOTO,l->VUOTO,l->VUOTO,l->PAROLAx2,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->PAROLAx2,l->VUOTO,l->VUOTO,l->VUOTO,l->LETTERAx2},
                                        {l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->PAROLAx2,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->PAROLAx2,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO},
                                        {l->VUOTO,l->LETTERAx3,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->LETTERAx3,l->VUOTO,l->VUOTO,l->VUOTO,l->LETTERAx3,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->LETTERAx3,l->VUOTO},
                                        {l->VUOTO,l->VUOTO,l->LETTERAx2,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->LETTERAx2,l->VUOTO,l->LETTERAx2,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->LETTERAx2,l->VUOTO,l->VUOTO},
                                        {l->PAROLAx3,l->VUOTO,l->VUOTO,l->LETTERAx2,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->LETTERAx2,l->VUOTO,l->VUOTO,l->PAROLAx3},
                                        {l->VUOTO,l->VUOTO,l->LETTERAx2,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->LETTERAx2,l->VUOTO,l->LETTERAx2,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->LETTERAx2,l->VUOTO,l->VUOTO},
                                        {l->VUOTO,l->LETTERAx3,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->LETTERAx3,l->VUOTO,l->VUOTO,l->VUOTO,l->LETTERAx3,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->LETTERAx3,l->VUOTO},
                                        {l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->PAROLAx2,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->PAROLAx2,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO},
                                        {l->LETTERAx2,l->VUOTO,l->VUOTO,l->VUOTO,l->PAROLAx2,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->PAROLAx2,l->VUOTO,l->VUOTO,l->VUOTO,l->LETTERAx2},
                                        {l->VUOTO,l->VUOTO,l->VUOTO,l->PAROLAx2,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->LETTERAx2,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->PAROLAx2,l->VUOTO,l->VUOTO,l->VUOTO},
                                        {l->VUOTO,l->VUOTO,l->PAROLAx2,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->LETTERAx2,l->VUOTO,l->LETTERAx2,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->PAROLAx2,l->VUOTO,l->VUOTO},
                                        {l->VUOTO,l->PAROLAx2,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->LETTERAx3,l->VUOTO,l->VUOTO,l->VUOTO,l->LETTERAx3,l->VUOTO,l->VUOTO,l->VUOTO,l->VUOTO,l->PAROLAx2,l->VUOTO},
                                        {l->PAROLAx3,l->VUOTO,l->VUOTO,l->VUOTO,l->LETTERAx2,l->VUOTO,l->VUOTO,l->VUOTO,l->PAROLAx3,l->VUOTO,l->VUOTO,l->VUOTO,l->LETTERAx2,l->VUOTO,l->VUOTO,l->VUOTO,l->PAROLAx3}};
    // le lettere sul tabellone
    vector<vector<QChar>> lettere_temp;
    for (int y = 0; y < l->LUN_Y; y++)
    {
        vector<QChar> temp;
        for (int x = 0; x < l->LUN_X; x++)
        {
            temp.push_back(' ');    // utilizzo il blank in quanto non ci sono ancora lettere posizionate
        }
        lettere_temp.push_back(temp);
    }

    // e la matrice delle lettere appena inserite
    vector<vector<bool>> nuovaLettera_temp;
    for (int y = 0; y < l->LUN_Y; y++)
    {
        vector<bool> temp_2;
        for (int x = 0; x < l->LUN_X; x++)
        {
            temp_2.push_back(false);    // utilizzo il falso in quanto non ci sono ancora lettere posizionate
        }
        nuovaLettera_temp.push_back(temp_2);
    }

    // assegno
    campo = campo_temp;
    lettere = lettere_temp;
    nuovaLettera = nuovaLettera_temp;
    jolly = nuovaLettera_temp;      // così come nuovaLettera, la matrice dei jolly all'inizio sarà tutta falsa
}

int Tabellone::calcolaPunteggio()
{
    Legenda *l = new Legenda();
    int punteggio = 0;

    // per ogni cella controllo se da essa parte una parola, e nel caso la controllo e verifico se ne devo calcolare il punteggio
    for (int y = 0; y < l->LUN_Y; y++)
    {
        for (int x = 0; x < l->LUN_X; x++)
        {
            // controllo che la casella non sia vuota
            if (lettere[y][x] != ' ')
            {
                // controllo che sia l'inizio di una parola in orizzontale
                if ((firstLeft(x,y) == 1) && ((firstRight(x,y) > 1) || (firstRight(x,y) == 0)))
                {
                    QString parola;
                    int right;
                    bool thereIsAJolly = false;
                    bool test = false;          // se test è vero, allora il punteggio della parola sarà da calcolare
                    if (firstRight(x,y) == 0)   // se first right è uguale a 0 allora la parola termina alla fine del tabellone
                        right = l->LUN_X - x;
                    else
                        right = firstRight(x,y);
                    // ricavo tutta la parola
                    for (int i = x; i < x + right; i++)
                    {
                        parola.push_back(lettere[y][i]);
                        // se la lettera è appena stata inserita, vuol dire che la parola che si è formata è nuova
                        if (nuovaLettera[y][i])
                        {
                            test = true;    // di conseguenza ne devo calcolare il punteggio
                        }
                        if (jolly[y][i])    // controllo se ci sono dei jolly a formare la parola
                            thereIsAJolly = true;
                    }
                    // eventualmente calcolo il punteggio
                    if (test)
                    {
                        // variabili di controllo per moltiplicare il punteggio della parola
                        bool due_p = false;
                        bool tre_p = false;
                        // scorro ogni lettera
                        for (int i = 0; i < parola.length(); i++)
                        {
                            // controllo se c'è una casella speciale
                            switch ((campo[y][x+i])) {
                            case l->VUOTO:
                                punteggio += l->PUNTEGGIO[0 + parola.at(i).unicode()-'A'];
                                break;
                            case l->PAROLAx2:
                                punteggio += l->PUNTEGGIO[0 + parola.at(i).unicode()-'A'];
                                due_p = true;
                                break;
                            case l->PAROLAx3:
                                punteggio += l->PUNTEGGIO[0 + parola.at(i).unicode()-'A'];
                                tre_p = true;
                                break;
                            case l->LETTERAx2:
                                punteggio += l->PUNTEGGIO[0 + parola.at(i).unicode()-'A'] *2;
                                break;
                            case l->LETTERAx3:
                                punteggio += l->PUNTEGGIO[0 + parola.at(i).unicode()-'A'] *3;
                                break;
                            }
                        }
                        // eventulamente moltiplico il punteggio della parola
                        if (due_p)
                            punteggio = punteggio *2;
                        if (tre_p)
                            punteggio = punteggio *3;
                        // eventuali punteggi bonus legati alla lunghezza della parola
                        if (parola.length() == 6)
                            punteggio += 10;
                        if (parola.length() == 7)
                            punteggio += 30;
                        if (parola.length() == 8)
                            punteggio += 50;
                        if ((parola == "SCARABEO") || (parola == "SCARABEI"))
                            punteggio += 100;
                        if (!thereIsAJolly)     // se non sono stati usati jolly
                            punteggio += 10;
                    }
                }
                // controllo che sia l'inizio di una parola in verticale
                if  ((firstUp(x,y) == 1) && ((firstDown(x,y) > 1) || (firstDown(x,y) == 0)))
                {
                    QString parola;
                    int down;
                    bool thereIsAJolly = false;
                    bool test = false;      // se test è vero, allora il punteggio della parola sarà da calcolare
                    if (firstDown(x,y) == 0)
                        down = l->LUN_Y - y;
                    else
                        down = firstDown(x,y);
                    // ricavo tutta la parola
                    for (int i = y; i < y + down; i++)
                    {
                        parola.push_back(lettere[i][x]);
                        // se la lettera è appena stata inserita, vuol dire che la parola che si è formata è nuova
                        if (nuovaLettera[i][x])
                        {
                            test = true;    // di conseguenza ne devo calcolare il punteggio
                        }
                        if (jolly[i][x])    // controllo se ci sono dei jolly a formare la parola
                            thereIsAJolly = true;

                    }
                    // eventualmente calcolo il punteggio
                    if (test)
                    {
                        // variabili di controllo per moltiplicare il punteggio della parola
                        bool due_p = false;
                        bool tre_p = false;
                        // scorro ogni lettera
                        for (int i = 0; i < parola.length(); i++)
                        {
                            // controllo se c'è una casella speciale
                            switch ((campo[y+i][x])) {
                            case l->VUOTO:
                                punteggio += l->PUNTEGGIO[0 + parola.at(i).unicode()-'A'];
                                break;
                            case l->PAROLAx2:
                                punteggio += l->PUNTEGGIO[0 + parola.at(i).unicode()-'A'];
                                due_p = true;
                                break;
                            case l->PAROLAx3:
                                punteggio += l->PUNTEGGIO[0 + parola.at(i).unicode()-'A'];
                                tre_p = true;
                                break;
                            case l->LETTERAx2:
                                punteggio += l->PUNTEGGIO[0 + parola.at(i).unicode()-'A'] *2;
                                break;
                            case l->LETTERAx3:
                                punteggio += l->PUNTEGGIO[0 + parola.at(i).unicode()-'A'] *3;
                                break;
                            }
                        }
                        // eventulamente moltiplico il punteggio della parola
                        if (due_p)
                            punteggio = punteggio *2;
                        if (tre_p)
                            punteggio = punteggio *3;
                        // eventuali punteggi bonus legati alla lunghezza della parola
                        if (parola.length() == 6)
                            punteggio += 10;
                        if (parola.length() == 7)
                            punteggio += 30;
                        if (parola.length() == 8)
                            punteggio += 50;
                        if ((parola == "SCARABEO") || (parola == "SCARABEI"))
                            punteggio += 100;
                        if (!thereIsAJolly)     // se non sono stati usati jolly
                            punteggio += 10;
                    }
                }
            }
        }
    }

    return punteggio;
}

vector<vector<unsigned int> > Tabellone::getCampo() const
{
    return campo;
}

void Tabellone::setCampo(const vector<vector<unsigned int> > &value)
{
    campo = value;
}

vector<vector<QChar> > Tabellone::getLettere() const
{
    return lettere;
}

void Tabellone::setLettere(const vector<vector<QChar> > &value)
{
    lettere = value;
}

vector<vector<bool> > Tabellone::getNuovaLettera() const
{
    return nuovaLettera;
}

void Tabellone::setNuovaLettera(const vector<vector<bool> > &value)
{
    nuovaLettera = value;
}

vector<vector<bool> > Tabellone::getJolly() const
{
    return jolly;
}

void Tabellone::setJolly(const vector<vector<bool> > &value)
{
    jolly = value;
}

bool Tabellone::isNear(int x, int y)
{
    bool temp = false;
    Legenda *l = new Legenda();
    
    if (x != 0)
        if (lettere[x-1][y] != ' ' )
            temp = true;
    if (x != l->LUN_X-1)
        if (lettere[x+1][y] != ' ')
            temp = true;
    if (y != 0)
        if (lettere[x][y-1] != ' ')
            temp = true;
    if (y != l->LUN_Y-1)
        if (lettere[x][y+1] != ' ')
            temp = true;

    return temp;
}

int Tabellone::firstUp(int x, int y)
{
    int distanza = 0;
    int temp = 0;
    bool fine = false;

    temp = y - 1;
    while (!fine)
    {
        // controllo di non essere fuori dal campo
        if (temp != -1)
        {
            // controllo se la casella successiva è libera
            if (lettere[temp][x] == ' ')
            {
                fine = true;
            }
            else    // altrimenti controllo quella dopo
                temp--;
        }
        else    // se sono alla fine del campo, termino subito
            fine = true;
    }

    if (temp != -1)
        distanza = y - temp;    // la distanza la calcolo sottraendo la coordinata della casella di partenza con quella della casella trovata
    else
        distanza = 0;   // vuole dire che non ci sono caselle libere

    return distanza;
}

int Tabellone::firstRight(int x, int y)
{
    int distanza = 0;
    int temp = 0;
    bool fine = false;
    Legenda *l = new Legenda();

    temp = x + 1;
    while (!fine)
    {
        // controllo di non essere fuori dal campo
        if (temp != l->LUN_X)
        {
            // controllo se la casella successiva è libera
            if (lettere[y][temp] == ' ')
            {
                fine = true;
            }
            else    // altrimenti controllo quella dopo
                temp++;
        }
        else    // se sono alla fine del campo, termino subito
            fine = true;
    }

    if (temp != l->LUN_X)
        distanza = temp - x;    // la distanza la calcolo sottraendo la coordinata della casella trovata con quella della casella di partenza
    else
        distanza = 0;   // vuole dire che non ci sono caselle libere

    return distanza;
}

int Tabellone::firstDown(int x, int y)
{
    int distanza = 0;
    int temp = 0;
    bool fine = false;
    Legenda *l = new Legenda();

    temp = y + 1;
    while (!fine)
    {
        // controllo di non essere fuori dal campo
        if (temp != l->LUN_Y)
        {
            // controllo se la casella successiva è libera
            if (lettere[temp][x] == ' ')
            {
                fine = true;
            }
            else    // altrimenti controllo quella dopo
                temp++;
        }
        else    // se sono alla fine del campo, termino subito
            fine = true;
    }

    if (temp != l->LUN_Y)
        distanza = temp - y;    // la distanza la calcolo sottraendo la coordinata della casella trovata con quella della casella di partenza
    else
        distanza = 0;   // vuole dire che non ci sono caselle libere

    return distanza;
}

int Tabellone::firstLeft(int x, int y)
{
    int distanza = 0;
    int temp = 0;
    bool fine = false;

    temp = x - 1;
    while (!fine)
    {
        // controllo di non essere fuori dal campo
        if (temp != -1)
        {
            // controllo se la casella successiva è libera
            if (lettere[y][temp] == ' ')
            {
                fine = true;
            }
            else    // altrimenti controllo quella dopo
                temp--;
        }
        else    // se sono alla fine del campo, termino subito
            fine = true;
    }

    if (temp != -1)
        distanza = x - temp;    // la distanza la calcolo sottraendo la coordinata della casella di partenza con quella della casella trovata
    else
        distanza = 0;   // vuole dire che non ci sono caselle libere

    return distanza;
}

void Tabellone::setNuovaLetteraValue(bool value, int x, int y)
{
    nuovaLettera[y][x] = value;
}

void Tabellone::setLetteraValue(QChar value, int x, int y)
{
    lettere[y][x] = value;
}

void Tabellone::setJollyValue(bool value, int x, int y)
{
    jolly[y][x] = value;
}
