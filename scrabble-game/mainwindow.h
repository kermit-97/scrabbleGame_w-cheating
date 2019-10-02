#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "custombutton_carta.h"
#include "custombutton_casella.h"
#include "tabellone.h"
#include "giocatore.h"
#include "jolly_dialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // getters and setters
    bool getIsPrimaLettera() const;
    void setIsPrimaLettera(bool value);

    bool getIsOrizzontale() const;
    void setIsOrizzontale(bool value);

    int getPrevious_x() const;
    void setPrevious_x(int value);

    int getPrevious_y() const;
    void setPrevious_y(int value);

    QChar getJollyLetter() const;
    void setJollyLetter(const QChar &value);

public slots:
    void creaTabellone(Tabellone myTabellone);          // crea il tabellone di gioco con i bottoni
    void receiveTabellone(Tabellone myTabellone);       // aggiorna il tabellone di gioco
    void receiveGiocatore(Giocatore myPlayer);          // aggiorna i dati del giocatore di turno
    void receiveClickedButton();                        // gestisce quando viene premuta una casella
    void receiveFine(Giocatore topPlayer);              // gestisce la fine della partita, quindi comunica il vincitore
    void receiveLetter(QChar letter);                   // riceve la lettera per il jolly dall'apposita dialog

private slots:
    void on_ripeti_pushButton_clicked();                // quando viene premuto il bottone per ripetere il turno

    void on_fine_pushButton_clicked();                  // quando viene premuto il bottone per finire il turno

    void on_suggerimento_pushButton_clicked();          // quando viene premuto il bottone per vedere il suggerimento

signals:
    void sendRipetiTurno();                                         // manda il segnale quando il giocatore vuole ripetere il turno
    void sendRipetiPrimoTurno();                                    // manda il segnale quando il giocatore vuole ripetere il primo turno
    void sendFineTurno(Tabellone tempTabellone);                    // manda il segnale quanod il giocatore ha finito il turno
    void sendRichiestaSuggerimento();                               // manda il segnale per una richiesta di suggerimento
    void sendAggiornamento(Tabellone tempTabellone, QString carte); // manda un segnale di aggiornamento, solitamente quando viene preso un jolly in cambio di una lettera

private:
    Ui::MainWindow *ui;     // UI
    bool isPrimaLettera;    // indica se deve essere inserita la prima lettera del turno
    bool isPrimoTurno;      // indica se è il primo turno di una partita
    bool isOrizzontale;     // indica se il giocatore sta componendo una parola in verticale o in orizzontale nel suo turno
    int previous_x;         // indica le coordinate x_y della lettera inserita
    int previous_y;
    QChar jollyLetter;      // indica quale lettera è stata assegnata al jolly
    Jolly_Dialog j;         // dialog per i jolly

    void setImageCasella(CustomButton_casella *button,QString image_path);   // applica l'immagine sulla casella
    void setImageCarta(CustomButton_carta *button,QString image_path);       // applica l'immagine sulla carta
    int firstUp(int x, int y);              // ritorna la distanza della prima casella libera a destra/alto/basso/sinistra della casella x_y
    int firstRight(int x, int y);           // nel caso in cui ritorni 0, non ci sono caselle libere
    int firstDown(int x, int y);
    int firstLeft(int x, int y);

};

#endif // MAINWINDOW_H
