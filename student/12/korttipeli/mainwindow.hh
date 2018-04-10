#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include "deck.hh"
#include "opendeck.hh"
#include "gamerules.hh"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void resetDeck();

private:
    void setupLayout();

    // Talletetaan attribuuteiksi ne widgetit, joita saattaa tarvita käsitellä pelin aikana.
    // Ohjelmakoodipohjassa näitä ei käytetä mihinkään.
    Deck* deck_;
    OpenDeck* pickedCards_;
    OpenDeck* houseCards_;
};

#endif // MAINWINDOW_HH
