#ifndef PLAYERSNUMBER_DIALOG_H
#define PLAYERSNUMBER_DIALOG_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class playersNumber_Dialog;
}

class playersNumber_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit playersNumber_Dialog(QWidget *parent = 0);
    ~playersNumber_Dialog();

private:
    Ui::playersNumber_Dialog *ui;

signals:
    void sendPlayersNumber(int number);     // manda il numero di giocatori alla mainwindow

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
};

#endif // PLAYERSNUMBER_DIALOG_H
