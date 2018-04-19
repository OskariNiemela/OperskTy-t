/*
 * TIE-02200 Ohjelmoinnin peruskurssi
 * Project: Korttipeli
 * File: gamerules.hh
 * Coder: Oskari Niemela
 * Student Number: 263440
 *
 * Desc:
 *
 * Notes:
 *      Assistants made the file originally I just made the
 *      one rule function.
*/
#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include "deck.hh"
#include "opendeck.hh"
#include "gamerules.hh"
#include "cardslot.hh"
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    // The player has correctly stacked the cards and so has won the game
    // disables the cardslots/deck and makes the win message come onto the screen
    void playerWin();
    //Add cards to all the different cardslots
    void addCards();
private:
    void setupLayout();

    // Talletetaan attribuuteiksi ne widgetit, joita saattaa tarvita käsitellä pelin aikana.
    // Ohjelmakoodipohjassa näitä ei käytetä mihinkään.
    Deck* deck_;
    std::vector<CardSlot*> slots_;

    QLabel* winLabel_;
};

#endif // MAINWINDOW_HH
