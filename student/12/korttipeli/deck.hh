/*
 * TIE-02200 Ohjelmoinnin Peruskurssi
 * Project: Korttipeli
 * Project Coder: Oskari Niemela
 * Student Number: 263440
 * File; deck.hh
 *
 * Desc:
 *      header file for the deck class which houses all the unpicked cards.
*/

#ifndef DECK_HH
#define DECK_HH

#include <vector>
#include <QFrame>
#include "card.hh"
#include <random>

class Deck : public QFrame
{
    Q_OBJECT

public:
    Deck(QWidget *parent = 0);

    // You can pick the top card of the deck.
    Card* pickCard();

    // Take back the cards that are in the vector of cards
    void getCards(std::vector<Card *> &cards);

signals:
    // The signal that is sent when a card is picked.
    void cardPicked(Card*);
    // send the signal to refill the deck from the cards that are in the opendeck
    void refillDeck();

protected:
    // A method pertaining to the clicking of the deck
    void mousePressEvent(QMouseEvent *event);

private:
    // The cards in the deck
    std::vector<Card*> cards_;
};

#endif // DECK_HH
