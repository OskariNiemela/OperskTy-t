/*
 * TIE-02200 Ohjelmoinnin peruskurssi
 * Project: Korttipeli
 * File: gamerules.hh
 * Coder: Oskari Niemela
 * Student Number: 263440
 *
 * Desc:
 *
*/

#include "deck.hh"

#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QPainter>
#include <QLabel>

Deck::Deck(QWidget *parent) : QFrame(parent)
{
    setMinimumSize(180, 260);
    setMaximumSize(180, 260);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    for (int suit = SPADE; suit != SUIT_COUNT; ++suit){

        for (unsigned value = 1; value <= 13; ++value){
            auto card = new Card(static_cast<CardSuit>(suit), value, this);
            int xOffset = (this->width() - card->width()) / 2;
            int yOffset = (this->height() - card->height()) / 2;
            card->move(xOffset, yOffset);
            cards_.push_back(card);
        }
    }
    std::random_shuffle(cards_.begin(),cards_.end());
}

Card* Deck::pickCard()
{
    if (cards_.empty()){
        return nullptr;
    } else {
        Card* card = cards_.back();
        cards_.pop_back();
        return card;
    }
}

void Deck::getCards(std::vector<Card *> &cards)
{
    for(Card* card:cards)
      {
          card->setParent(this);
          int xOffset = (this->width() - card->width()) / 2;
          int yOffset = (this->height() - card->height()) / 2;
          cards_.push_back(card);
          card->move(xOffset, yOffset);
          card->turn();
          card->show();
      }

}


// If the deck is clicked
void Deck::mousePressEvent(QMouseEvent *event)
{
    // the program cant crash when clicking an empty deck
    if (cards_.empty()){
        // send out the signal to refill the deck if possible
        emit refillDeck();
        return;
    }

    Card* card = cards_.back();
    cards_.pop_back();

    if(!card)
    {
        return;
    }

    // Inform the opendeck that we've picked a card
    emit cardPicked(card);

    // Accept the clicking event
    event->accept();
}

