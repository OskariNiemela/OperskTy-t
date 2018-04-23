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
 *
 * Notes:
 *      Assistants made the file originally, I only
 *      added/changed some of the functions and function pointer
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

using CheckFunction = bool(*)(Card*, Card*,int&);

class CardSlot: public QFrame
{
    Q_OBJECT

public:
    // Rakentaja ja metodi, jolla slotiin voidaan lisätä kortti.
    CardSlot(CheckFunction checkFunction, QWidget* parent = 0);
    // Adds a card normally to the cardslot
    void addCard(Card* card,bool open=true);
    // Adds a card but keeps it face down.
    void addCardClosed(Card* card);

    // Itse toteutetut Qt:n widgetin raahaukseen liittyvät metodit.
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    void mousePressEvent(QMouseEvent *event);

signals:
    // Signals that the player has won
    void wins();

private:
    // Apumetodeita dropEventin käyttöön.
    void parseNewCards(std::list<Card*>& newCards, QStringList& newCardsData);
    void setupNewCards(std::list<Card*>& newCards);

    // Päällimmäisenä oleva kortti on talletettu attribuutiksi, koska se vaikuttaa
    // siihen, mitä tähän slotiin saa raahata. Muut kortit ovat vain tämän widgetin
    // lapsia, ja niihin päästään tarvittaessa käsiksi Qt:n parent-mekanismin avulla.
    Card* topCard_;
    Card* bottomCard_;
    bool adjust;
    // Pelisääntöfunktio, joka määrittelee, mitä kortteja tähän widgettiin saa raahata.
    CheckFunction function;
};

#endif // CARDSLOT_HH
