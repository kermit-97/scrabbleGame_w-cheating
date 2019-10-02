#ifndef MAZZO_H
#define MAZZO_H

#include <QString>
#include <QChar>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

class Mazzo
{
public:
    Mazzo();

    QChar pesca();          // restituisce la prima carta del mazzo
    int getNumeroCarte();   // restituisce il numero delle carte presenti nel mazzo
    void mescola();         // mescola le carte del mazzo in modo casuale

    // getters and setters
    QString getCarte() const;
    void setCarte(const QString &value);

    bool getFinito() const;
    void setFinito(bool value);

private:
    QString carte;      // carte nel mazzo
    bool finito;        // vero se non sono rimaste carte nel mazzo
};

#endif // MAZZO_H
