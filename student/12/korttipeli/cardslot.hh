/*
 * TIE-02200 Ohjelmoinnin Peruskurssi
 * Project: Korttipeli
 * Project Coder: Oskari Niemela
 * Student Number: 263440
 * File: cardslot.hh
 *
 * Desc:
 *      Contains declaration of the CardSlot class
 *      and a declaration of a function pointer.
 *      CardSlots hold cards that are dragged into them,
 *      if the cardslot only takes one card at a time it means
 *      that it is a land cardslot which wants all the cards from
 *      a certain land from 1->13 in order.
*/

#ifndef CARDSLOT_HH
#define CARDSLOT_HH

#include "gamerules.hh"
#include "card.hh"

#include <list>
#include <string>
#include <QFrame>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

using CheckFunction = bool(*)(std::string,std::string,int&);

class CardSlot: public QFrame
{
    Q_OBJECT

public:

    CardSlot(CheckFunction checkFunction, QWidget* parent = 0, bool adjustable = true, bool oneAtATime=false);
    // Adds a card normally to the cardslot, 1st param is the card we need to add
    // 2nd param is whether to open the card that were adding.
    void addCard(Card* card,bool open=true);

    // Methods pertaingin to the dragging of cards
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    void mousePressEvent(QMouseEvent *event);

signals:
    // Signals that this stack is filled
    void wins();

private:
    // Helpful methods for the dragging events
    void parseNewCards(std::list<Card*>& newCards, QStringList& newCardsData);
    void setupNewCards(std::list<Card*>& newCards);

    // The topcard
    Card* topCard_;
    // Whether or not to adjust the borders when resizing window.
    bool adjust_;
    // Whether or not this cardslot only takes one card at a time.
    bool oneCard_;
    // Function that defines the rule with which cards can be added to the slot
    CheckFunction function;
};

#endif // CARDSLOT_HH
