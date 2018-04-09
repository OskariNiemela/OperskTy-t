#ifndef DECK_HH
#define DECK_HH

#include <vector>
#include <QFrame>
#include "card.hh"
#include <random>
#include <iostream>
#include <string>

class Deck : public QFrame
{
    Q_OBJECT

public:
    Deck(QWidget *parent = 0);

    // Korttipakasta voi nostaa päällimmäisen kortin.
    Card* pickCard();

    // TODO: Lisää tähän uusia toimintoja, joita korttipakalle voi suorittaa.
    void takeCards(std::vector<std::string>& cards);



signals:
    // Signaali, jonka pakka lähettää, kun kortti nostetaan.
    void cardPicked(Card* card);
    void fillDeck();

protected:
    // Itse toteutettu Qt:n widgetin klikkaamiseen liittyvä metodi.
    void mousePressEvent(QMouseEvent *event);

private:
    // Korttipakan sisältämät kortit.
    std::vector<Card*> cards_;
    std::vector<std::string> split(std::string user_string, char separator,bool ignore_empty = true);
};

#endif // DECK_HH
