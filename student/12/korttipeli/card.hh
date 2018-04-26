/*
 * TIE-02200 Ohjelmoinnin Peruskurssi
 * Project: Korttipeli
 * Project Coder: Oskari Niemela
 * Student Number: 263440
 * File: card.hh
 *
 * Desc:
 *      header file for the card class
*/

#ifndef CARD_HH
#define CARD_HH

#include <QLabel>
#include <QFrame>

enum CardSuit {SPADE, CLUB, DIAMOND, HEART, SUIT_COUNT};

class Card : public QFrame
{
    Q_OBJECT

public:
    Card(CardSuit suit, unsigned value, QWidget *parent = 0);

    // For observing and modifying the internal state of the card
    bool isOpen();
    void allowOpen();

    // Used when stacking cards o

    // 1st param is the card we wish to stack, 2nd param whether or not
    // we want the widget borders to be adjusted.
    void stackCard(Card* card,bool adjustBorder=true);
    void removeStackedCards();

    // Returns the information of the card and all the cards ontop
    // (value,land,open)
    std::string getCardData();

    // When dragging a card we need the picture of it so we know
    // which one is being dragged
    QLabel* getCurrentSideLabel();

signals:
    // For resizing a cards borders when adding a card ontop of it
    void resized();

public slots:
    // More procedures we can do with the card
    void turn();
    void expand();
    void open();

protected:
    // Methdo for when the card is double clicked
    void mouseDoubleClickEvent(QMouseEvent* event);

private:
    // Helpful methods for the other methods to use
    void setupLayout();
    void setSuitPixmap();
    void setupBack();
    void setupFront();

    // The internal state of the card
    CardSuit suit_;
    unsigned value_;
    bool open_;
    bool canOpen_;

    // The front and back pictures for the card
    QPixmap suitPixmap_;
    QPixmap backPixmap_;

    // A pointer to the possible card stacked ontop of this one
    Card* stackedCard_;
};

#endif // CARD_HH
