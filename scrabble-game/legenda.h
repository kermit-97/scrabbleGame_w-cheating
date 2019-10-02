#ifndef LEGENDA_H
#define LEGENDA_H


class Legenda
{
public:
    Legenda();

    enum Constants
    {
        // caselle
        VUOTO = 0,
        PAROLAx2 = 1,
        PAROLAx3 = 2,
        LETTERAx2 = 3,
        LETTERAx3 = 4,

        // lunghezza campo
        LUN_X = 17,
        LUN_Y = 17,

        MANO_GIOCATORE = 8
    };
                             //A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q, R,S,T,U,V,W,X,Y,Z
    const int PUNTEGGIO[26] = {1,4,1,4,1,4,4,8,1,0,0,2,2,2,1,3,10,1,1,1,4,4,0,0,0,8};
};

#endif // LEGENDA_H
