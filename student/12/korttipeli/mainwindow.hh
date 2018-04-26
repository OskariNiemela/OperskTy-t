/*
 * TIE-02200 Ohjelmoinnin peruskurssi
 * Project: Korttipeli
 * File: gamerules.hh
 * Coder: Oskari Niemela
 * Student Number: 263440
 *
 * Desc:
 *      header file for the mainwindow which contains all the relevant widgets
 *      for the card game.
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
    // Refill the closed deck with the cards in the open deck.
    void refillDeck();


    // One of the lands has been completed and we need to keep track of how many
    // have been completed.
    void landComplete();
private:
    void setupLayout();

    // The player has correctly stacked the cards and so has won the game
    // disables the cardslots/deck and makes the win message come onto the screen
    void playerWin();


    // Save the widgets that we might need to access/manipulate
    // during the game as pointers
    Deck* deck_;
    OpenDeck* pickedCards_;
    std::vector<CardSlot*> slots_;
    std::vector<CardSlot*> winSlots_;

    // informs the player when theyve won.
    QLabel* winLabel_;

    // keeps track of how many land slots have been filled.
    int lands_;
};

#endif // MAINWINDOW_HH
