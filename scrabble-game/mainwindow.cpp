#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setGeometry(50,50,1100,750);

    // carico l'immagine di sfondo del form
    QPixmap bkgnd(":/images/F4F1DE.png");   // con ":" mi riferisco alle mie risorse (v. Resources e file qrc)
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    // setto i flag
    isPrimaLettera = true;
    isPrimoTurno = true;
    isOrizzontale = true;
    previous_x = -1;
    previous_y = -1;

    // setto le dimensioni
    //QRect dimensioni_campo(10,10,700,700);
    //QRect dimensioni_pannello(710,10,400,700);
    ui->gridLayoutWidget->setGeometry(10,10,700,700);
    ui->verticalLayoutWidget->setGeometry(750,10,300,450);
    //ui->campo_gridLayout->setGeometry(dimensioni_campo);
    //ui->verticalLayout->setGeometry(dimensioni_pannello);

    j.setWindowFlags ( Qt::CustomizeWindowHint | Qt::WindowTitleHint);   // nasconde la barra di windows che permette di ridurre/ridimensionare/chiudere la dialog
    // connetto i SIGNALS-SLOTS per l'acquisizione della lettera jolly
    QObject::connect(&j, SIGNAL(sendLetter(QChar)),
                     this, SLOT(receiveLetter(QChar)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::creaTabellone(Tabellone myTabellone)
{
    isPrimaLettera = true;              // se creo il tabellone, vuol dire che dovrò inserire la prima lettera
    isPrimoTurno = true;                // sistemo anche i flag
    previous_x = -1;
    previous_y = -1;
    // x e y usate per salvare le coordinate
    int x = 0;
    int y = 0;

    Legenda *l = new Legenda();         // dichiaro l'oggetto legenda che andrò ad utilizzare per le caselle

    // ciclo per le colonne
    for (auto element : myTabellone.getCampo())
    {
        // ciclo per le righe
        for (auto e : element)
        {
            CustomButton_casella *button = new CustomButton_casella();      // dichiaro il nuovo bottone che andrò a posizionare nel layout

            // setto le informazioni nel mio oggetto
            button->setCoord_x(x);      // coordinate
            button->setCoord_y(y);
            button->setCasella(e);      // tipo di casella
            button->setLettera(' ');    // lettera (all'inizio è vuota, quindi blank)
            button->setIsJolly(false);  // la casella non contiene un jolly
            button->setIsNew(false);    // setto la proprietà a falso, perchè non è presente nessuna nuova lettera

            button->setFixedSize(QSize(40,40));         // setto la dimensione dei bottoni

            // aggiungo la casella nel layout, secondo le coordinate x,y
            // NB: nel grid layout la Y è la riga, la X la colonna
            ui->campo_gridLayout->addWidget(button,button->getCoord_y(),button->getCoord_x());

            QString image_path = "";        // a seconda del tipo di casella carico un'immagine diversa
            switch(button->getCasella())
            {
                case (l->VUOTO):
                {
                    image_path = ":/images/F2CC8F.png";
                    break;
                }
                case (l->PAROLAx2):
                {
                    image_path = ":/images/2P.png";
                    break;
                }
                case (l->PAROLAx3):
                {
                    image_path = ":/images/3P.png";
                    break;
                }
                case (l->LETTERAx2):
                {
                    image_path = ":/images/2L.png";
                    break;
                }
                case (l->LETTERAx3):
                {
                    image_path = ":/images/3L.png";
                    break;
                }
            }
            setImageCasella(button,image_path);         // applico l'immagine al bottone

            // connetto i SIGNALS-SLOTS per gestire quando un bottone viene schiacciato
            QObject::connect(button, SIGNAL(clicked()),
                             button, SLOT(handle_clicked()));
            QObject::connect(button, SIGNAL(send_clicked()),
                             this, SLOT(receiveClickedButton()));

            // all'inizio non posso premere nessun bottone se non quello centrale
            if ((x == y) && (x == l->LUN_X/2))
                button->setEnabled(true);
            else
                button->setEnabled(false);

            button->show();         // mostro effettivamente il bottone
            x++;                    // incremento il contatore x
        }
        y++;                        // incremento il contatore y
        x = 0;                      // azzero il contatore x
    }
}

void MainWindow::receiveTabellone(Tabellone myTabellone)
{
    isPrimaLettera = true;              // se aggiorno il tabellone, vuol dire che dovrò inserire la prima lettera
    previous_x = -1;                    // sistemo anche i flag
    previous_y = -1;
    // x e y usate per le coordinate
    int x = 0;
    int y = 0;

    Legenda *l = new Legenda();         // dichiaro l'oggetto legenda che andrò ad utilizzare per le caselle

    // ciclo per le colonne
    for (auto element : myTabellone.getCampo())
    {
        // ciclo per le righe
        for (auto e : element)
        {
            CustomButton_casella *button = qobject_cast<CustomButton_casella*>(ui->campo_gridLayout->itemAtPosition(y,x)->widget());      // prendo il bottone che andrò ad aggiornare dal gridLayout, è necessario il cast

            // resetto le informazioni nel mio oggetto se necessario, ovvero se c'è una discordia tra il tabellone e ciò che viene visualizzato
            if ((myTabellone.getLettere()[y][x] != button->getLettera()) || (myTabellone.getJolly()[y][x] != button->getIsJolly()))
            {
                button->setLettera(myTabellone.getLettere()[y][x]);     // setto la lettera

                // nel caso in cui la casella sia vuota deve avere l'immagine giusta, che corrisponde alla casella
                if (myTabellone.getLettere()[y][x] == ' ')
                {
                    // a seconda del tipo di casella ricarico un'immagine diversa
                    QString image_path = "";
                    switch(e)
                    {
                        case (l->VUOTO):
                        {
                            image_path = ":/images/F2CC8F.png";
                            break;
                        }
                        case (l->PAROLAx2):
                        {
                            image_path = ":/images/2P.png";
                            break;
                        }
                        case (l->PAROLAx3):
                        {
                            image_path = ":/images/3P.png";
                            break;
                        }
                        case (l->LETTERAx2):
                        {
                            image_path = ":/images/2L.png";
                            break;
                        }
                        case (l->LETTERAx3):
                        {
                            image_path = ":/images/3L.png";
                            break;
                        }
                    }
                    setImageCasella(button,image_path);     // applico l'immagine al bottone
                }
                else    // caso in cui casella non sia vuota
                {
                    // a seconda della lettera carico un'immagine diversa
                    QString image_path = "";
                    if (myTabellone.getJolly()[y][x])   // se è un jolly carico l'immagine dello scarabeo
                        image_path = ":/images/Scrabble.png";
                    else
                    {
                        image_path = ":/images/";
                        image_path.push_back(myTabellone.getLettere()[y][x]);
                        image_path.push_back(".png");
                    }
                    setImageCasella(button,image_path);     // applico l'immagine al bottone
                }
            }

            // decido se può essere clicclato o no -> se è vicino ad un'altra lettera ed è vuoto, il bottone deve poter essere premuto, altrimenti no
            if ((myTabellone.isNear(y,x)) && (button->getLettera() == ' '))
                button->setEnabled(true);
            else
                button->setEnabled(false);
            if (myTabellone.getJolly()[y][x])   // se è un jolly
                button->setEnabled(true);       // posso cliccarlo per sostituirlo
            else
                button->setIsJolly(false);
            // setto la proprietà
            button->setIsNew(false);
            x++;
        }
        y++;
        x = 0;
    }

    isPrimoTurno = false;
}

void MainWindow::receiveGiocatore(Giocatore myPlayer)
{
    ui->nome_label->setText(myPlayer.getNome());        // setto label nome
    ui->punteggio_label->setText("Punteggio " + QString::number(myPlayer.getPunteggio()));      // setto label punteggio

    QString carte = myPlayer.getCarte();        // prendo le carte del giocatore
    // resetto la griglia
    QLayoutItem* item;
    while ( ( item = ui->carte_gridLayout->takeAt( 0 ) ) != NULL )
    {
        delete item->widget();
        delete item;
    }

    // per ogni carta del giocatore
    for (int x = 0; x < carte.length(); x++)
    {
        CustomButton_carta *button = new CustomButton_carta();              // creo il bottone che rappresenta la carta
        button->setFixedSize(QSize(70,70));             // setto la dimensione dei bottoni
        button->setLettera(carte[x]);                   // setto la lettera associata al bottone

        QString image_path = "";        // seleziono l'immagine da caricare
        if (carte[x] == '*')
            image_path = ":/images/Scrabble.png";
        else
            image_path = ":/images/" + carte[x] + ".png";
        setImageCarta(button,image_path);       // applico l'immagine al bottone

        // dispongo le carte su due righe, ognuna da 4 colonne
        if (x < 4)
            ui->carte_gridLayout->addWidget(button,0,x);
        else
            ui->carte_gridLayout->addWidget(button,1,x-4);
        button->setCheckable(true);         // setto le proprietà
        button->setAutoExclusive(true);

        button->show();         // mostro effettivamente il bottone
    }
    // creo un altro bottone nascosto, che utilizzo per disabilitare la selezione delle carte già giocate
    CustomButton_carta *temp = new CustomButton_carta();
    temp->setObjectName("hidden");
    temp->setCheckable(true);
    temp->setAutoExclusive(true);
    temp->setVisible(false);
    ui->carte_gridLayout->addWidget(temp);
}

void MainWindow::receiveClickedButton()
{
    CustomButton_casella* button_casella = qobject_cast<CustomButton_casella*>(sender());       // eseguo il cast dall'oggetto sender all'oggetto CustomButton_casella

    if (button_casella->getIsJolly())   // se la carta premuta è un jolly, vuol dire che il giocatore vuole prenderlo sostituendolo con una sua lettera
    {
        // verifico quale carta è stata selezionata
        for (int x = 0; x < ui->carte_gridLayout->count(); x++)
        {
            // prendo l'elemento, controllando che non sia la carta nascosta (utilizzata per la selezione nulla)
            CustomButton_carta *button_carta = qobject_cast<CustomButton_carta*>(ui->carte_gridLayout->itemAt(x)->widget());
            if (button_carta->objectName() != "hidden")
            {
                // appena trovo quale carta è stata selezionata
                if (button_carta->isChecked())
                {
                    if (button_carta->getLettera() == button_casella->getLettera()) // se la lettera coincide posso fare lo scambio
                    {
                        button_casella->setIsJolly(false);
                        button_carta->setLettera('*');

                        Legenda *l = new Legenda();
                        // converto il campo di gioco in un oggetto tabellone temporaneo
                        Tabellone tempTabellone = Tabellone();
                        vector<vector<QChar>> lettere_temp;
                        for (int y = 0; y < l->LUN_Y; y++)
                        {
                            vector<QChar> temp;
                            for (int x = 0; x < l->LUN_X; x++)
                            {
                                // scorro tutto il layout
                                CustomButton_casella *button_casella = qobject_cast<CustomButton_casella*>(ui->campo_gridLayout->itemAtPosition(y,x)->widget());
                                temp.push_back(button_casella->getLettera());
                                if (button_casella->getIsNew())     // se la lettera è stata inserita in questo turno
                                {
                                    tempTabellone.setNuovaLetteraValue(true,x,y);       // salvo l'informazione nel mio tabellone temporaneo
                                }
                                if (button_casella->getIsJolly())     // se la lettera è un jolly
                                {
                                    tempTabellone.setJollyValue(true,x,y);              // salvo l'informazione nel mio tabellone temporaneo
                                }
                            }
                            lettere_temp.push_back(temp);
                        }
                        tempTabellone.setLettere(lettere_temp);        // assegno le lettere presenti sul campo all'oggetto tabellone temporaneo

                        // recupero la nuova meno del giocatore
                        QString carte = "";
                        for (int i = 0; i < ui->carte_gridLayout->count(); i++)
                        {
                            CustomButton_carta *button_carta = qobject_cast<CustomButton_carta*>(ui->carte_gridLayout->itemAt(i)->widget());
                            if (button_carta->objectName() != "hidden")
                                carte.push_back(button_carta->getLettera());
                        }

                        button_casella->setIsJolly(true);  // ritorna alla posizione iniziale, altrimenti il ciclo di aggiornamento non vedrà il cambiamento

                        sendAggiornamento(tempTabellone,carte);       // mando il segnale per gestire la fine del turno
                    }
                    else        // altrimenti lo comunico
                    {
                        QMessageBox msgBox;
                        QString text = "Il Jolly non può essere preso, la sua lettera è: ";
                        text.push_back(button_casella->getLettera());
                        msgBox.setText(text);
                        msgBox.exec();
                    }
                }
            }
        }
    }
    else    // altrimenti è il normale posizionamento di una lettera su una casella
    {
        // verifico quale carta è stata selezionata
        for (int x = 0; x < ui->carte_gridLayout->count(); x++)
        {
            // prendo l'elemento, controllando che non sia la carta nascosta (utilizzata per la selezione nulla)
            CustomButton_carta *button_carta = qobject_cast<CustomButton_carta*>(ui->carte_gridLayout->itemAt(x)->widget());
            if (button_carta->objectName() != "hidden")
            {
                // appena trovo quale carta è stata selezionata
                if (button_carta->isChecked())
                {
                    // preparo il percorso dell'immagine da caricare sulla casella
                    QString image_path = ":/images/";
                    if (button_carta->getLettera() == '*')
                        image_path.push_back("Scrabble");
                    else
                        image_path.push_back(button_carta->getLettera());
                    image_path.push_back(".png");
                    setImageCasella(button_casella,image_path);         // applico l'immagine al bottone

                    image_path = ":/images/5D737E.png";         // preparo il percorso dell'immagine da caricare sulla carta utilizzata
                    setImageCarta(button_carta,image_path);     // applico l'immagine al bottone

                    if (button_carta->getLettera() == '*')
                    {
                        j.exec();       // eseguo la dialog per acquisire la lettera jolly
                        button_casella->setLettera(jollyLetter);     // setto la lettera sulla casella
                        button_casella->setIsJolly(true);
                    }
                    else
                    {
                        button_casella->setLettera(button_carta->getLettera());     // setto la lettera sulla casella
                        button_casella->setIsJolly(false);
                    }
                    button_casella->setEnabled(false);      // disabilito la casella
                    button_casella->setIsNew(true);         // salvo che il bottone è stato inserito in questo turno

                    button_carta->setLettera(' ');              // resetto la lettera sulla carta
                    button_carta->setEnabled(false);            // disabilito la carta

                    // ora gestisco il tabellone in modo da constringere il giocatore a inserire le lettere solo nelle caselle consentite
                    for (int i = 0; i < ui->campo_gridLayout->count(); ++i)
                    {
                        CustomButton_casella *my_button_casella = qobject_cast<CustomButton_casella*>(ui->campo_gridLayout->itemAt(i)->widget());
                        my_button_casella->setEnabled(false);       // prima disabilito tutti i bottoni
                    }

                    if (isPrimaLettera)     // se è la prima lettera del turno allora il giocatore può decidere se posizionare le lettere in orizzontale o in verticale
                    {
                        int my_x = button_casella->getCoord_x();
                        int my_y = button_casella->getCoord_y();
                        // modifico i flag
                        isPrimaLettera = false;
                        previous_x = my_x;
                        previous_y = my_y;

                        // poi abilito solo le caselle dove può posizionare una lettera
                        if ((firstUp(my_x,my_y) != 0))
                        {
                            CustomButton_casella *my_button_casella = qobject_cast<CustomButton_casella*>(ui->campo_gridLayout->itemAtPosition(my_y - firstUp(my_x,my_y),my_x)->widget());
                            my_button_casella->setEnabled(true);
                        }
                        if ((firstRight(my_x,my_y) != 0))
                        {
                            CustomButton_casella *my_button_casella = qobject_cast<CustomButton_casella*>(ui->campo_gridLayout->itemAtPosition(my_y,my_x + firstRight(my_x,my_y))->widget());
                            my_button_casella->setEnabled(true);
                        }
                        if ((firstDown(my_x,my_y) != 0))
                        {
                            CustomButton_casella *my_button_casella = qobject_cast<CustomButton_casella*>(ui->campo_gridLayout->itemAtPosition(my_y + firstDown(my_x,my_y),my_x)->widget());
                            my_button_casella->setEnabled(true);
                        }
                        if ((firstLeft(my_x,my_y) != 0))
                        {
                            CustomButton_casella *my_button_casella = qobject_cast<CustomButton_casella*>(ui->campo_gridLayout->itemAtPosition(my_y,my_x - firstLeft(my_x,my_y))->widget());
                            my_button_casella->setEnabled(true);
                        }
                    }
                    else    // altrimenti il giocatore può continuare ad inserire le lettere solo in orizzonatale o in verticale
                    {
                        int my_x = button_casella->getCoord_x();
                        int my_y = button_casella->getCoord_y();

                        // controllo se il giocatore sta inserendo la sua parola in orizzontale o verticale
                        if (my_y == previous_y)
                            isOrizzontale = true;
                        else
                            isOrizzontale = false;

                        if (isOrizzontale)  // nel caso in cui si stia muovendo in orizzontale, permetto al giocatore di posizionare le lettere solo a dx o a sx
                        {
                            if (firstRight(my_x,my_y) != 0)
                            {
                                CustomButton_casella *my_button_casella = qobject_cast<CustomButton_casella*>(ui->campo_gridLayout->itemAtPosition(my_y,my_x + firstRight(my_x,my_y))->widget());
                                my_button_casella->setEnabled(true);
                            }
                            if (firstLeft(my_x,my_y) != 0)
                            {
                                CustomButton_casella *my_button_casella = qobject_cast<CustomButton_casella*>(ui->campo_gridLayout->itemAtPosition(my_y,my_x - firstLeft(my_x,my_y))->widget());
                                my_button_casella->setEnabled(true);
                            }
                        }
                        else                // altrimenti solo in alto o in basso
                        {
                            if (firstUp(my_x,my_y) != 0)
                            {
                                CustomButton_casella *my_button_casella = qobject_cast<CustomButton_casella*>(ui->campo_gridLayout->itemAtPosition(my_y - firstUp(my_x,my_y),my_x)->widget());
                                my_button_casella->setEnabled(true);
                            }
                            if (firstDown(my_x,my_y) != 0)
                            {
                                CustomButton_casella *my_button_casella = qobject_cast<CustomButton_casella*>(ui->campo_gridLayout->itemAtPosition(my_y + firstDown(my_x,my_y),my_x)->widget());
                                my_button_casella->setEnabled(true);
                            }
                        }
                    }
                }
            }
            else
                button_carta->setChecked(true);     // sposto la selezione della carta sul mio hidden button, costringendo il giocatore a sceglierne un'altra
        }
    }

}

void MainWindow::receiveFine(Giocatore topPlayer)
{
    QMessageBox msgBox;
    msgBox.setText("VINCE IL " + topPlayer.getNome() + " CON UN PUNTEGGIO DI " + QString::number(topPlayer.getPunteggio()));
    msgBox.exec();
    this->close();
}

void MainWindow::receiveLetter(QChar letter)
{
    jollyLetter = letter;
}

void MainWindow::setImageCasella(CustomButton_casella *button, QString image_path)
{
    QPixmap bkgnd_button(image_path);
    bkgnd_button = bkgnd_button.scaled(button->size(), Qt::IgnoreAspectRatio);
    QPalette palette_button;
    palette_button.setBrush(QPalette::Button, bkgnd_button);
    button->setFlat(true);
    button->setAutoFillBackground(true);
    button->setPalette(palette_button);
}

void MainWindow::setImageCarta(CustomButton_carta *button, QString image_path)
{
    QPixmap bkgnd_button(image_path);
    bkgnd_button = bkgnd_button.scaled(button->size(), Qt::IgnoreAspectRatio);
    QPalette palette_button;
    palette_button.setBrush(QPalette::Button, bkgnd_button);
    button->setFlat(true);
    button->setAutoFillBackground(true);
    button->setPalette(palette_button);
}

void MainWindow::on_ripeti_pushButton_clicked()
{
    if (isPrimoTurno)
    {
        // resetto la griglia
        QLayoutItem* item;
        while ( ( item = ui->campo_gridLayout->takeAt( 0 ) ) != NULL )
        {
            delete item->widget();
            delete item;
        }

        sendRipetiPrimoTurno();
    }
    else
    {
        sendRipetiTurno();
    }
}

void MainWindow::on_fine_pushButton_clicked()
{
    Legenda *l = new Legenda();
    // converto il campo di gioco in un oggetto tabellone temporaneo che sarà convalidato
    Tabellone tempTabellone = Tabellone();
    vector<vector<QChar>> lettere_temp;
    for (int y = 0; y < l->LUN_Y; y++)
    {
        vector<QChar> temp;
        for (int x = 0; x < l->LUN_X; x++)
        {
            // scorro tutto il layout
            CustomButton_casella *button_casella = qobject_cast<CustomButton_casella*>(ui->campo_gridLayout->itemAtPosition(y,x)->widget());
            temp.push_back(button_casella->getLettera());
            if (button_casella->getIsNew())     // se la lettera è stata inserita in questo turno
                tempTabellone.setNuovaLetteraValue(true,x,y);       // salvo l'informazione nel mio tabellone temporaneo
            if (button_casella->getIsJolly())   // se la lettera è un jolly
                tempTabellone.setJollyValue(true,x,y);              // salvo l'informazione nel mio tabellone temporaneo
        }
        lettere_temp.push_back(temp);
    }
    tempTabellone.setLettere(lettere_temp);        // assegno le lettere presenti sul campo all'oggetto tabellone temporaneo

    sendFineTurno(tempTabellone);       // mando il segnale per gestire la fine del turno
}

void MainWindow::on_suggerimento_pushButton_clicked()
{
    sendRichiestaSuggerimento();
}

QChar MainWindow::getJollyLetter() const
{
    return jollyLetter;
}

void MainWindow::setJollyLetter(const QChar &value)
{
    jollyLetter = value;
}

int MainWindow::getPrevious_y() const
{
    return previous_y;
}

void MainWindow::setPrevious_y(int value)
{
    previous_y = value;
}

int MainWindow::getPrevious_x() const
{
    return previous_x;
}

void MainWindow::setPrevious_x(int value)
{
    previous_x = value;
}

bool MainWindow::getIsOrizzontale() const
{
    return isOrizzontale;
}

void MainWindow::setIsOrizzontale(bool value)
{
    isOrizzontale = value;
}

bool MainWindow::getIsPrimaLettera() const
{
    return isPrimaLettera;
}

void MainWindow::setIsPrimaLettera(bool value)
{
    isPrimaLettera = value;
}

int MainWindow::firstUp(int x, int y)
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
            CustomButton_casella *button_casella = qobject_cast<CustomButton_casella*>(ui->campo_gridLayout->itemAtPosition(temp,x)->widget());
            // controllo se la casella successiva è libera
            if (button_casella->getLettera() == ' ')
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

int MainWindow::firstRight(int x, int y)
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
            CustomButton_casella *button_casella = qobject_cast<CustomButton_casella*>(ui->campo_gridLayout->itemAtPosition(y,temp)->widget());
            // controllo se la casella successiva è libera
            if (button_casella->getLettera() == ' ')
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

int MainWindow::firstDown(int x, int y)
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
            CustomButton_casella *button_casella = qobject_cast<CustomButton_casella*>(ui->campo_gridLayout->itemAtPosition(temp,x)->widget());
            // controllo se la casella successiva è libera
            if (button_casella->getLettera() == ' ')
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

int MainWindow::firstLeft(int x, int y)
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
            CustomButton_casella *button_casella = qobject_cast<CustomButton_casella*>(ui->campo_gridLayout->itemAtPosition(y,temp)->widget());
            // controllo se la casella successiva è libera
            if (button_casella->getLettera() == ' ')
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
