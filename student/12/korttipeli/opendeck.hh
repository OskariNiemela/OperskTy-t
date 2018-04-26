/*
 * TIE-02200 Ohjelmoinnin peruskurssi
 * Project: Korttipeli
 * File: gamerules.hh
 * Coder: Oskari Niemela
 * Student Number: 263440
 *
 * Desc:
 *      header file for the opendeck class,
 *
*/

#ifndef OPENDECK_HH
#define OPENDECK_HH
#include <QFrame>

unsigned const MAX_SCORE = 21;


QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

#include <vector>
#include <iostream>
#include <QStackedLayout>

#include "card.hh"
class OpenDeck : public QFrame
{

    Q_OBJECT

public:
    OpenDeck(QWidget* parent = 0);
    void giveCards(std::vector<Card *> &cardVec);

public slots:
    void addCard(Card* card);

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent* event);
    void mousePressEvent(QMouseEvent *event);
private:
    QStackedLayout* layout_;  // Contains the card widgets that this deck contains.

};

#endif // OPENDECK_HH
