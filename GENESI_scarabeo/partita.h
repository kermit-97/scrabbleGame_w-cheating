#ifndef PARTITA_H
#define PARTITA_H

#include <QObject>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include "dict.h"
#include "giocatore.h"
#include "legenda.h"
#include "mazzo.h"
#include "tabellone.h"

using namespace std;

class Partita : public QObject          // eredito la classe QObject per poter utilizzare i SIGNALS-SLOTS
{
    Q_OBJECT
public:
    explicit Partita(QObject *parent = 0);

    void start();                   // manda i signals alla mainwindow, necessari per far iniziare la partita
    void gestisciCarte();           // gestisce la mano del giocatore attuale
    void prossimoGiocatore();       // setta il prossimo giocatore come giocatore attuale
    bool convalida(Tabellone tempTabellone, bool avvisa);       // ritorna vero se il tabellone passato è valido
    void vittoria();                // calcola gli ultimi punti del giocatore e determina il vincitore
    void calcolaSuggerimento();     // calcola la parola con il miglior punteggio con l'attuale situazione del tabellone
    // choice: lettere disponibili con relativa frequenza
    // curWord: la parola che si sta creando in modo ricorsivo
    // words: l'insieme delle parole valide trovate
    void constructWords(unordered_map<char, int>& choice, string& curWord, vector<string >& words);    // costruisce tutte le parole possibili

    // getters and setters
    int getPlayersNumber() const;
    void setPlayersNumber(int value);

    Tabellone getMyTabellone() const;
    void setMyTabellone(const Tabellone &value);

    Mazzo getMyDeck() const;
    void setMyDeck(const Mazzo &value);

    vector<Giocatore> getMyPlayers() const;
    void setMyPlayers(const vector<Giocatore> &value);

signals:
    void creaTabellone(Tabellone myTabellone);      // manda un segnale alla mainwindow per creare il tabellone sul layout
    void sendTabellone(Tabellone myTabellone);      // manda un segnale alla mainwindow per aggiornarae il tabellone sul layout
    void sendGiocatore(Giocatore myPlayer);         // manda un segnale alla mainwindow per aggiornarae i dati del giocatore sul layout
    void sendFine(Giocatore myPlayer);              // manda un segnale alla mainwindow per finire la partita

public slots:
    void receivePlayersNumber(int number);      // riceve il numero di giocatori dalla dialog
    void receiveRipetiTurno();                  // riceve che il giocatore vuole ripetere il turno
    void receiveRipetiPrimoTurno();             // riceve che il giocatore vuole ripetere il primo turno
    void receiveFineTurno(Tabellone tempTabellone);     // riceve che il giocatore ha finito il turno
    void receiveRichiestaSuggerimento();        // riceve una richiesta per il calcolo del suggerimento
    void receiveAggiornamento(Tabellone tempTabellone, QString carte);  // riceve un aggiornamento, solitamente in seguito allo scambio di una lettera con un jolly

private:
    vector<Giocatore> myPlayers;                // vettore dei giocatori della partita
    Mazzo myDeck;                               // mazzo utilizzalato nella partita
    Tabellone myTabellone;                      // tabellone di gioco utilizzato nella partita
    Legenda l;                                  // legenda utilizzata
    int playersNumber;                          // numero di giocatori della partita
    int currentPlayer;                          // indica il giocatore di turno
    Dict myDictionary = Dict("E:/loren/Documents/Qt Projects/GENESI_scarabeo/dictionary/italian.txt");     // dizionario utilizzato nella partita
    //Dict *myDictionary = new Dict(":/dictionary/italian.txt");
    //Dict *myDictionary = new Dict("C:/Users/Elena/Documents/QT_projects/GENESI_scarabeo/dictionary/italian.txt");

};

#endif // PARTITA_H
