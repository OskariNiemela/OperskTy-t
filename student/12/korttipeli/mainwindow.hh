#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include "deck.hh"
#include "opendeck.hh"
#include "gamerules.hh"
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void resetDeck();
    void newGame();
    void scorePlayer(unsigned score);
    void scoreHouse(unsigned score);
    void checkWin();
    void playerLose();
    void houseLose();

private:
    void setupLayout();


    // Talletetaan attribuuteiksi ne widgetit, joita saattaa tarvita käsitellä pelin aikana.
    // Ohjelmakoodipohjassa näitä ei käytetä mihinkään.
    Deck* deck_;
    OpenDeck* pickedCards_;
    OpenDeck* houseCards_;

    QPushButton* startGame_;
    QPushButton* stay_;
    QLabel* playerPoints_;
    QLabel* housePoints_;
};

#endif // MAINWINDOW_HH
