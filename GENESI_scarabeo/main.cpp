#include "mainwindow.h"
#include "playersnumber_dialog.h"
#include "partita.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    playersNumber_Dialog myDialog;
    MainWindow w;
    Partita game;

    // connetto i SIGNALS-SLOTS per l'acquisizione del numero di giocatori dalla dialog
    QObject::connect(&myDialog, SIGNAL(sendPlayersNumber(int)),
                     &game, SLOT(receivePlayersNumber(int)));
    // connetto i SIGNALS-SLOTS per la creazione del layout in base al tabellone
    QObject::connect(&game, SIGNAL(creaTabellone(Tabellone)),
                     &w, SLOT(creaTabellone(Tabellone)));
    // connetto i SIGNALS-SLOTS per l'aggiornamento del layout in base al tabellone
    QObject::connect(&game, SIGNAL(sendTabellone(Tabellone)),
                     &w, SLOT(receiveTabellone(Tabellone)));
    // connetto i SIGNALS-SLOTS per l'aggiornamento del layout in base al tabellone
    QObject::connect(&game, SIGNAL(sendGiocatore(Giocatore)),
                     &w, SLOT(receiveGiocatore(Giocatore)));
    // connetto i SIGNALS-SLOTS per quando il giocatore vuole ripetere il turno
    QObject::connect(&w, SIGNAL(sendRipetiTurno()),
                     &game, SLOT(receiveRipetiTurno()));
    QObject::connect(&w, SIGNAL(sendRipetiPrimoTurno()),
                     &game, SLOT(receiveRipetiPrimoTurno()));
    // connetto i SIGNALS-SLOTS per quando il giocatore vuole finire il turno
    QObject::connect(&w, SIGNAL(sendFineTurno(Tabellone)),
                     &game, SLOT(receiveFineTurno(Tabellone)));
    // connetto i SIGNALS-SLOTS per quando finisce la partita
    QObject::connect(&game, SIGNAL(sendFine(Giocatore)),
                     &w, SLOT(receiveFine(Giocatore)));
    // connetto i SIGNALS-SLOTS per quando viene richiesto un suggerimento
    QObject::connect(&w, SIGNAL(sendRichiestaSuggerimento()),
                     &game, SLOT(receiveRichiestaSuggerimento()));
    // connetto i SIGNALS-SLOTS per quando viene richiesto un aggiornamento
    QObject::connect(&w, SIGNAL(sendAggiornamento(Tabellone,QString)),
                     &game, SLOT(receiveAggiornamento(Tabellone,QString)));

    // eseguo la dialog
    myDialog.setWindowFlags ( Qt::CustomizeWindowHint | Qt::WindowTitleHint);   // nasconde la barra di windows che permette di ridurre/ridimensionare/chiudere la dialog
    myDialog.exec();

    game.start();

    w.show();

    return a.exec();
}
