#include "partita.h"

Partita::Partita(QObject *parent) : QObject(parent)
{
    // setto il primo giocatore come attuale
    currentPlayer = 0;
    // mescolo il mazzo
    myDeck.mescola();
}

int Partita::getPlayersNumber() const
{
    return playersNumber;
}

void Partita::setPlayersNumber(int value)
{
    playersNumber = value;
}

Tabellone Partita::getMyTabellone() const
{
    return myTabellone;
}

void Partita::setMyTabellone(const Tabellone &value)
{
    myTabellone = value;
}

Mazzo Partita::getMyDeck() const
{
    return myDeck;
}

void Partita::setMyDeck(const Mazzo &value)
{
    myDeck = value;
}

vector<Giocatore> Partita::getMyPlayers() const
{
    return myPlayers;
}

void Partita::setMyPlayers(const vector<Giocatore> &value)
{
    myPlayers = value;
}

void Partita::prossimoGiocatore()
{
    // controllo se sono l'ultimo giocatore
    if (currentPlayer == playersNumber-1)
        currentPlayer = 0;      // l'attuale diventa il primo
    else
        currentPlayer ++;       // l'attuale diventa il prossimo
}

void Partita::start()
{
    // segnalo di creare il tabellone
    creaTabellone(myTabellone);
    // segnalo il giocatore attuale
    sendGiocatore(myPlayers[currentPlayer]);
}

void Partita::gestisciCarte()
{
    QString mano = myPlayers[currentPlayer].getCarte();
    // controllo ogni cella del tabellone
    for (int y = 0; y < l.LUN_Y; y++)
    {
        for (int x = 0; x < l.LUN_X; x++)
        {
            // controllo se la lettera è nuova
            if (myTabellone.getNuovaLettera()[y][x])
            {
                if (myTabellone.getJolly()[y][x])        // controllo se è un jolly
                    mano.remove(mano.indexOf('*'),1);    // e la rimuovo
                else
                    mano.remove(mano.indexOf(myTabellone.getLettere()[y][x]),1);    // e la rimuovo
            }
        }
    }
    myPlayers[currentPlayer].setCarte(mano);    // sistemo le carte in mano al giocatore
    while (!(myDeck.getFinito()) && (myPlayers[currentPlayer].getCarte().length() < l.MANO_GIOCATORE))  // se il mazzo non è finito e il giocatore non ha abbastanza carte
        myPlayers[currentPlayer].aggiungi_carta(myDeck.pesca());    // allora il giocatore pesca una carta
}

void Partita::receivePlayersNumber(int number)
{
    // salvo il numero di giocatori ricevuto dalla dialog
    playersNumber = number;

    // preparo i giocatori
    for (int x = 0; x < playersNumber; x++)
    {
        Giocatore player;       // dichiaro l'oggetto
        player.setNome("Giocatore " + QString::number(x+1));        // setto il nome

        for (int y = 0; y < l.MANO_GIOCATORE; y++ )
            player.aggiungi_carta(myDeck.pesca());      // aggiungo le carte

        myPlayers.push_back(player);        // salvo l'oggetto nel vettore
    }
}

void Partita::receiveRipetiTurno()
{
    sendTabellone(myTabellone);
    sendGiocatore(myPlayers[currentPlayer]);
}

void Partita::receiveRipetiPrimoTurno()
{
    creaTabellone(myTabellone);
    sendGiocatore(myPlayers[currentPlayer]);
}

void Partita::receiveFineTurno(Tabellone tempTabellone)
{
    if (convalida(tempTabellone,true))       // se il tabellone è valido
    {
        myTabellone.setLettere(tempTabellone.getLettere());     // salvo le nuove lettere inserite nel turno
        myTabellone.setNuovaLettera(tempTabellone.getNuovaLettera());       // e quelle che sono state inserite in questo turno
        myTabellone.setJolly(tempTabellone.getJolly());         // e i jolly
        myPlayers[currentPlayer].setPunteggio(myPlayers[currentPlayer].getPunteggio() + myTabellone.calcolaPunteggio());        // calcolo il punteggio
        gestisciCarte();                            // gestisce la mano del giocatore alla fine del turno
        // controllo vittoria
        if (myDeck.getFinito() && (myPlayers[currentPlayer].getCarte().length() == 0))
        {
            vittoria();
        }
        else
        {
            prossimoGiocatore();                        // il turno passa al prossimo giocatore
            sendTabellone(myTabellone);                 // restituisco il tabellone
            sendGiocatore(myPlayers[currentPlayer]);    // restituisco il giocatore di turno
        }
    }
    else        // altrimento se non è valido
    {
        sendTabellone(myTabellone);                 // restituisco il tabellone iniziale
        sendGiocatore(myPlayers[currentPlayer]);    // restituisco il giocatore di turno
    }
}

void Partita::receiveRichiestaSuggerimento()
{
    calcolaSuggerimento();
}

void Partita::receiveAggiornamento(Tabellone tempTabellone, QString carte)
{
    myTabellone.setLettere(tempTabellone.getLettere());     // salvo le nuove lettere inserite nel turno
    myTabellone.setNuovaLettera(tempTabellone.getNuovaLettera());       // e quelle che sono state inserite in questo turno
    myTabellone.setJolly(tempTabellone.getJolly());         // e i jolly
    myPlayers[currentPlayer].setCarte(carte);

    sendTabellone(myTabellone);
    sendGiocatore(myPlayers[currentPlayer]);
}

bool Partita::convalida(Tabellone tempTabellone, bool avvisa)
{
    bool test = true;

    // per ogni cella controllo se da essa parte una parola, e nel caso la controllo
    for (int y = 0; y < l.LUN_Y; y++)
    {
        for (int x = 0; x < l.LUN_X; x++)
        {
            // controllo che la casella non sia vuota
            if (tempTabellone.getLettere()[y][x] != ' ')
            {
                // controllo che sia l'inizio di una parola in orizzontale
                if ((tempTabellone.firstLeft(x,y) == 1) && ((tempTabellone.firstRight(x,y) > 1) || (tempTabellone.firstRight(x,y) == 0)))
                {
                    QString parola;
                    QString parola_reverse;
                    int right;

                    if (tempTabellone.firstRight(x,y) == 0)
                        right = l.LUN_X - x;
                    else
                        right = tempTabellone.firstRight(x,y);
                    // ricavo tutta la parola
                    for (int i = x; i < x + right; i++)
                    {
                        parola.push_back(tempTabellone.getLettere()[y][i]);
                        parola_reverse.push_front(tempTabellone.getLettere()[y][i]);
                    }
                    if (parola.length() > 3)        // IL PROGRAMMA RICHIEDE DI CONTROLLARE LA VALIDITà DELLE PAROLE MAGGIORI DI 3
                    {
                        // controllo che sia una parola valida in un senso o nell'altro
                        if (!(myDictionary.contains(parola.toStdString())) && !(myDictionary.contains(parola_reverse.toStdString())))
                        {
                            test = false;
                            if (avvisa)
                            {
                                QMessageBox msgBox;
                                msgBox.setText("La parola '" + parola + "' o '" + parola_reverse + "' non è contenuta nel dizionario.");
                                msgBox.exec();
                            }
                        }
                    }
                }
                // controllo che sia l'inizio di una parola in orizzontale
                if  ((tempTabellone.firstUp(x,y) == 1) && ((tempTabellone.firstDown(x,y) > 1) || (tempTabellone.firstDown(x,y) == 0)))
                {
                    QString parola;
                    QString parola_reverse;
                    int down;

                    if (tempTabellone.firstDown(x,y) == 0)
                        down = l.LUN_Y - y;
                    else
                        down = tempTabellone.firstDown(x,y);
                    // ricavo tutta la parola
                    for (int i = y; i < y + down; i++)
                    {
                        parola.push_back(tempTabellone.getLettere()[i][x]);
                        parola_reverse.push_front(tempTabellone.getLettere()[i][x]);
                    }
                    if (parola.length() > 3)        // IL PROGRAMMA RICHIEDE DI CONTROLLARE LA VALIDITà DELLE PAROLE MAGGIORI DI 3
                    {
                        // controllo che sia una parola valida in un senso o nell'altro
                        if (!(myDictionary.contains(parola.toStdString())) && !(myDictionary.contains(parola_reverse.toStdString())))
                        {
                            test = false;
                            if (avvisa)
                            {
                                QMessageBox msgBox;
                                msgBox.setText("La parola '" + parola + "' o '" + parola_reverse + "' non è contenuta nel dizionario.");
                                msgBox.exec();
                            }
                        }
                    }
                }
            }
        }
    }

    return test;
}

void Partita::vittoria()
{
    Legenda* l = new Legenda();
    // aggiungo al giocatore che ha finito i punteggi delle carte degli altri
    for (int i = 0; i < playersNumber; i++)
    {
        if (i != currentPlayer)
        {
            for (int x = 0; x < myPlayers[i].getCarte().length(); x++)   // per ogni lettera in mano agli altri giovatori
                if (myPlayers[i].getCarte().at(x) != '*')   // punteggio del Jolly non pervenuto, lo salto dal calcolo
                    myPlayers[currentPlayer].setPunteggio(myPlayers[currentPlayer].getPunteggio() + l->PUNTEGGIO[0 +  myPlayers[i].getCarte().at(x).unicode()-'A']);    // sommo il punteggio relativo al giocatore che ha terminato la partita
        }
    }
    int topPlayer = 0;  // parto dal primo giocatore
    for (int i = 1; i < playersNumber; i++)
    {
        if (myPlayers[topPlayer].getPunteggio() < myPlayers[i].getPunteggio())
            topPlayer = i;  // se trovo un giocatore migliore allora aggiorno l'indice
    }

    sendFine(myPlayers[topPlayer]);
}

void Partita::calcolaSuggerimento()
{
    // preparo i flag e le variabili
    int riga = -1;
    int colonna = -1;
    int punteggio = 0;
    string parola = "";
    QMessageBox msgBox;
    string msg_text;

    // CONTROLLO IN ORIZZONTALE
    for (int r = 0; r < Legenda::LUN_Y; r++)
    {
        bool test = false;
        for(int c = 0; c < Legenda::LUN_X; c++)     // controllo che ci sia almeno una lettera sulla riga
        {
            if (myTabellone.getLettere()[r][c] != ' ' )
                test = true;
        }
        if (test)   // se non c'è nemmeno una lettera sulla riga, non controllo il suggerimento su di essa
        {
            string temp_rack = myPlayers[currentPlayer].getCarte().toStdString();    // recupero la mano del giocatore
            string rack;

            // elimino i jolly dal calcolo del suggerimento
            for (size_t i = 0; i < temp_rack.length(); i++)
                if (temp_rack.at(i) != '*')
                    rack.push_back(temp_rack.at(i));

            for (int c = 0; c < Legenda::LUN_X; c++)            // scorro tutta la riga
                if (myTabellone.getLettere()[r][c] != ' ')          // appena trovo una lettera
                    rack += myTabellone.getLettere()[r][c].toLatin1();   // la aggiungo al rack

            // coppia di valori,
            // char -> carattere preso dal rack
            // int -> contatore occorrenze del carattere
            // int -> indica se la lettera deve essere in una posizione
            unordered_map<char, int> choice;
            for(size_t i = 0; i < rack.length(); i++){      // scorro il rack
                if(choice.find(rack[i]) == choice.end())    // caso carattere nuovo
                    choice[toupper(rack[i])] = 0;           // viene inserito e inizializzato a 0
                choice[toupper(rack[i])]++;                 // altrimenti incremento il contatore relativo al carattere
            }

            vector<string> parole_trovate;   // contiene la coppia parola trovata/punteggio
            string word;
            constructWords(choice, word, parole_trovate);  // cerco tutte le parole possibili

            for(auto it = parole_trovate.begin(); it != parole_trovate.end(); it++) // scorro tutte le parole trovate
            {
                if (it->length() < 4)     // le parole di lunghezza inferiore a 4 non vengono considerate
                    continue;
                if (!(it->length() > Legenda::LUN_X))         // controllo che non sia una parola troppo lunga
                {
                    for (size_t c = 0; c < (Legenda::LUN_X - it->length()); c++)      // per ogni parola, provo a posizionarla in ogni cella della riga
                    {
                        test = true;
                        bool flag = false;
                        bool flag2 = false;
                        bool flag3 = true;
                        string mano = myPlayers[currentPlayer].getCarte().toStdString();
                        for (size_t i = 0; i < it->length(); i++)     // controllo la posizione di ogni lettera sul tabellone
                        {
                            if ((it->at(i) != myTabellone.getLettere()[r][c+i]) && (myTabellone.getLettere()[r][c+i] != ' ')) // se c'è un'incongruenza
                                test = false;       // allora la parola non è da calcolare
                            if(it->at(i) == myTabellone.getLettere()[r][c+i])   // controllo che si intrecci con almeno una lettera già presente sul tabellone
                                flag = true;
                            if (test && (myTabellone.getLettere()[r][c+i] == ' '))  // controllo che sia stata posizionata almeno una lettera dalla mano del giocatore
                                flag2 = true;
                            if (test && ((myTabellone.getLettere()[r][c+i] == ' ') && (mano.find(it->at(i)) == string::npos)))   // controllo che le lettere posizionate siano prese solo dalla mano del giocatore
                                flag3 = false;
                            else if ((myTabellone.getLettere()[r][c+i] == ' ') && (mano.find(it->at(i)) != string::npos))
                                mano.erase(mano.find(it->at(i)));
                        }
                        if (test && flag && flag2 && flag3)   // se posso procedere controllo il punteggio effettivo della parola
                        {
                            Tabellone tempTabellone = Tabellone();      // creo un tabellone temporaneo
                            tempTabellone.setLettere(myTabellone.getLettere());     // sulla base di quello attuale
                            for (size_t i = 0; i < it->length(); i++)   // aggiungo la nuova parola
                            {
                                if (myTabellone.getLettere()[r][c+i] == ' ')
                                {
                                    tempTabellone.setLetteraValue(it->at(i),c+i,r);
                                    tempTabellone.setNuovaLetteraValue(true,c+i,r);
                                }
                            }
                            if (convalida(tempTabellone,false))       // se è tutto OK
                            {
                                if(tempTabellone.calcolaPunteggio() > punteggio)    // controllo se il punteggio è maggiore di quello precedente
                                {
                                    punteggio = tempTabellone.calcolaPunteggio();
                                    parola = *it;
                                    colonna = c;
                                    riga = r;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // comunico il risultato
    msgBox.setWindowTitle("ORIZZONTALE");
    if (parola != "")
        msg_text = " parola trovata: " + parola + "\n punteggio: " + to_string(punteggio) + "\n riga: " + to_string(riga) + "\n colonna: " + to_string(colonna);
    else
        msg_text = "Nessun suggerimento ORIZZONTALE maggiore di 3 trovato";
    QString prova = QString::fromStdString(msg_text);
    msgBox.setText(prova);
    msgBox.exec();

    // CONTROLLO IN VERTICALE
    parola = "";
    riga = -1;
    colonna = -1;
    punteggio = 0;
    for (int c = 0; c < Legenda::LUN_X; c++)
    {
        bool test = false;
        for(int r = 0; r < Legenda::LUN_X; r++)     // controllo che ci sia almeno una lettera sulla colonna
        {
            if (myTabellone.getLettere()[r][c] != ' ' )
                test = true;
        }
        if (test)   // se non c'è nemmeno una lettera sulla colonna, non controllo il suggerimento su di essa
        {
            string temp_rack = myPlayers[currentPlayer].getCarte().toStdString();    // recupero la mano del giocatore
            string rack;

            // elimino i jolly dal calcolo del suggerimento
            for (size_t i = 0; i < temp_rack.length(); i++)
                if (temp_rack.at(i) != '*')
                    rack.push_back(temp_rack.at(i));

            for (int r = 0; r < Legenda::LUN_Y; r++)            // scorro tutta la colonna
                if (myTabellone.getLettere()[r][c] != ' ')          // appena trovo una lettera
                    rack += myTabellone.getLettere()[r][c].toLatin1();   // la aggiungo al rack

            // coppia di valori,
            // char -> carattere preso dal rack
            // int -> contatore occorrenze del carattere
            // int -> indica se la lettera deve essere in una posizione
            unordered_map<char, int> choice;
            for(size_t i = 0; i < rack.length(); i++){      // scorro il rack
                if(choice.find(rack[i]) == choice.end())    // caso carattere nuovo
                    choice[toupper(rack[i])] = 0;           // viene inserito e inizializzato a 0
                choice[toupper(rack[i])]++;                 // altrimenti incremento il contatore relativo al carattere
            }

            vector<string> parole_trovate;   // contiene la coppia parola trovata/punteggio
            string word;
            constructWords(choice, word, parole_trovate);  // cerco tutte le parole possibili

            for(auto it = parole_trovate.begin(); it != parole_trovate.end(); it++) // scorro tutte le parole trovate
            {
                if (it->length() < 3)     // le parole di lunghezza inferiore a 3 non vengono considerate
                    continue;
                if (!(it->length() > Legenda::LUN_Y))         // controllo che non sia una parola troppo lunga
                {
                    for (size_t r = 0; r < (Legenda::LUN_Y - it->length()); r++)      // per ogni parola, provo a posizionarla in ogni cella della colonna
                    {
                        test = true;
                        bool flag = false;
                        bool flag2 = false;
                        bool flag3 = true;
                        string mano = myPlayers[currentPlayer].getCarte().toStdString();
                        for (size_t i = 0; i < it->length(); i++)     // controllo la posizione di ogni lettera sul tabellone
                        {
                            if ((it->at(i) != myTabellone.getLettere()[r+i][c]) && (myTabellone.getLettere()[r+i][c] != ' ')) // se c'è un'incongruenza
                                test = false;       // allora la parola non è da calcolare
                            if(it->at(i) == myTabellone.getLettere()[r+i][c])   // controllo che si intrecci con almeno una lettera già presente sul tabellone
                                flag = true;
                            if (test && (myTabellone.getLettere()[r+i][c] == ' '))  // controllo che sia stata posizionata almeno una lettera dalla mano del giocatore
                                flag2 = true;
                            if (test && ((myTabellone.getLettere()[r+i][c] == ' ') && (mano.find(it->at(i)) == string::npos)))   // controllo che le lettere posizionate siano prese solo dalla mano del giocatore
                                flag3 = false;
                            else if ((myTabellone.getLettere()[r+i][c] == ' ') && (mano.find(it->at(i)) != string::npos))
                                mano.erase(mano.find(it->at(i)));
                        }
                        if (test && flag && flag2 && flag3)   // se posso procedere controllo il punteggio effettivo della parola
                        {
                            Tabellone tempTabellone = Tabellone();      // creo un tabellone temporaneo
                            tempTabellone.setLettere(myTabellone.getLettere());     // sulla base di quello attuale
                            for (size_t i = 0; i < it->length(); i++)   // aggiungo la nuova parola
                            {
                                if (myTabellone.getLettere()[r+i][c] == ' ')
                                {
                                    tempTabellone.setLetteraValue(it->at(i),c,r+i);
                                    tempTabellone.setNuovaLetteraValue(true,c,r+i);
                                }
                            }
                            if (convalida(tempTabellone,false))       // se è tutto OK
                            {
                                if(tempTabellone.calcolaPunteggio() > punteggio)    // controllo se il punteggio è maggiore di quello precedente
                                {
                                    punteggio = tempTabellone.calcolaPunteggio();
                                    parola = *it;
                                    colonna = c;
                                    riga = r;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // comunico il risultato
    msgBox.setWindowTitle("VERTICALE");
    if (parola != "")
        msg_text = " parola trovata: " + parola + "\n punteggio: " + to_string(punteggio) + "\n riga: " + to_string(riga) + "\n colonna: " + to_string(colonna);
    else
        msg_text = "Nessun suggerimento VERTICALE maggiore di 3 trovato";
    prova = QString::fromStdString(msg_text);
    msgBox.setText(prova);
    msgBox.exec();
}

void Partita::constructWords(unordered_map<char, int> &choice, string &curWord, vector<string > &words)
{
    for(auto it = choice.begin(); it != choice.end(); it++){
        if(it->second <= 0)     // se il contatore delle occorrenze del carattere è minore o uguale a 0 allora uso l'istruzione continue
            continue;           // mi permette di saltare direttamente al prossimo ciclo, senza uscirne (a meno che non sia vera la condizione di uscita)

        curWord += it->first;   // alla mia parola corrente aggiungo il carattere a cui sto puntando
        it->second--;           // decremento il contatore delle occorrenze in quanto ho utilizzato il carattere
        if(myDictionary.contains(curWord))          // controllo che il dizioario contenga effettivamente la parola corrente
            words.push_back(curWord);     // e nel caso lo aggiungo al vettore delle mie parole con il relativo punteggio
        if (!(myDictionary.noSuccessor(curWord)))     // se da quella parola non ci sono più successori è inutile continuare a controllare le combinazioni
            constructWords(choice, curWord, words);               // chiamata ricorsiva per poter controllare ogni possibile combinazione con le mie lettere

        choice[curWord.back()]++;   // incremento il contatore delle occorrenze dell'ultimo carattere utilizzato, per riportare la situazione all'inizio
        curWord.pop_back();         // tolgo l'ultimo carattere dalla parola corrente, per riportare la situazione all'inizio
    }
}
