/*
 * TIE-02200 Ohjelmoinnin peruskurssi
 * Project: Korttipeli
 * File: gamerules.hh
 * Coder: Oskari Niemela
 * Student Number: 263440
 *
 * Desc:
 *      Contains the code for the CardSlot class
 *
*/

#include "cardslot.hh"

#include <iostream>
#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QPainter>


CardSlot::CardSlot(CheckFunction checkFunction, QWidget *parent, bool adjustable, bool oneAtATime):
    QFrame(parent), topCard_(nullptr),adjust_(adjustable), oneCard_(oneAtATime),function(checkFunction)
{
    // Allow for things to be dropped into this widget
    setAcceptDrops(true);
    setMinimumSize(180, 260);
    if(adjust_)
    {
        setMaximumWidth(180);

    }
    else
    {
        setMaximumSize(180,260);
    }

    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);

}

// Add a card into the widget
void CardSlot::addCard(Card *card, bool open)
{
    if (topCard_ == nullptr){
        card->setParent(this);
    }
    else {
        topCard_->stackCard(card,adjust_);
    }
    if(open)
    {
        card->open();
    }

    topCard_= card;
    card->show();
    card->allowOpen();

}

// Is executed when something is dragged ontop of this slot
void CardSlot::dragEnterEvent(QDragEnterEvent *event)
{

    if (event->mimeData()->hasFormat("text/plain")) {
        event->setDropAction(Qt::MoveAction);
        event->accept();

    } else {
        event->ignore();
    }
}

// Is executed when something is dragged while already inside
// the slot
void CardSlot::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("text/plain")) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        event->ignore();
    }
}

// Executed when something is dropped into this slot
void CardSlot::dropEvent(QDropEvent *event)
{
    // Check that the format of the information the event contains is valid
    // and that the source of the dragging isnt this slot.
    if (event->mimeData()->hasFormat("text/plain") && event->source() != this ) {

        // Request information about the cards being dropped
        QStringList newCardsData = event->mimeData()->text().split(";");

        // If we only accept one card then check if there are more than one cards being dragged into this slot
        if((newCardsData.size()>1)&&(oneCard_))
        {
            event->ignore();
            return;
        }

        // get the info from the cards already in the slot
        QStringList existingCardsData;
        if (topCard_ != nullptr){
            existingCardsData = QString::fromStdString(topCard_->getCardData()).split(";");
        } else {
            existingCardsData.append("");
        }

        int topVal=0;
        if(function(existingCardsData.back().toStdString(), newCardsData.back().toStdString(),topVal)){
            // if the drop is valid
            std::list<Card*> newCards;
            parseNewCards(newCards, newCardsData);
            setupNewCards(newCards);
            event->acceptProposedAction();
            if((oneCard_)&&(topVal==13))
            {
                emit wins();
                this->setEnabled(false);

            }
        }
        else
        {
            event->ignore();
        }

    } else {
        event->ignore();
    }
}

// Executed when clicking the cardslot
void CardSlot::mousePressEvent(QMouseEvent *event)
{

    // Stops the program from crashing when clicking an empty slot
    if (!childAt(event->pos()) || topCard_ == nullptr){
        return;
    }

    // Take the card that was clicked and point a pointer to it
    Card* card = dynamic_cast<Card*>(childAt(event->pos())->parent());
    if (!card){
        return;  // If no card was found do nothing.
    }
    if (!card->isOpen()){
        return;  // If the card is closed do nothing.
    }

    // Save the picture of the card
    QPixmap pixmap = *card->getCurrentSideLabel()->pixmap();

    // Make an object to store the card data
    QMimeData *mimeData = new QMimeData;
    mimeData->setText(QString::fromStdString(card->getCardData()));

    // Create a drag event which will be provided with the card info and picture
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);

    drag->setHotSpot(QPoint(pixmap.width()/2, pixmap.height()/2));


    QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
    painter.end();
    card->getCurrentSideLabel()->setPixmap(tempPixmap);


    if (drag->exec( Qt::MoveAction) == Qt::MoveAction) {
        //If the drag was successful
        card->getCurrentSideLabel()->setPixmap(pixmap);

        if (card->parent() == this){
            // If the dragged card was the bottom one
            topCard_ = nullptr;
        } else {
            // Remove the cards that were dragged off
            topCard_ = static_cast<Card*>(card->parent());
            topCard_->removeStackedCards();
        }
        // delete the card that was dragged and any children it may have had
        card->setParent(nullptr);
        card->setAttribute(Qt::WA_DeleteOnClose);
        card->close();

    } else {
        // If the dragging failed
        card->getCurrentSideLabel()->setPixmap(pixmap);
        card->show();
    }
}

// Parses the new card data into actual cards
void CardSlot::parseNewCards(std::list<Card *> &newCards, QStringList &newCardsData)
{
    // Parse the data and create cards corrresponding to the data
    for (QString cardData: newCardsData){
        QStringList splitted =  cardData.remove(";").split(",");
        if(splitted.isEmpty()){
            break;
        }
        QString value = splitted.at(0);
        QString suit = splitted.at(1);
        QString open = splitted.at(2);
        Card* card = new Card(static_cast<CardSuit> (suit.toUInt()), value.toUInt(), this);
        newCards.push_front(card);
        card->show();
        if (open.toInt()){
            card->turn();
        }
    }
}

// Sets the newcards in their correct positions
void CardSlot::setupNewCards(std::list<Card *> &newCards)
{

    // If were adding one card into an empty slot
    if (topCard_ == nullptr && newCards.size() == 1) {
        topCard_ = newCards.front();
    }

    // If were adding more than one card into an empty slot
    else if(topCard_ == nullptr && newCards.size() > 1) {
        topCard_ = newCards.front();
        newCards.pop_front();
        for (auto card: newCards){
            topCard_->stackCard(card,adjust_);
            topCard_  = card;
            card->show();
        }
    }

    // If were adding cards into a slot with cards present
    else if(topCard_ != nullptr){
        for (auto card: newCards){
            topCard_->stackCard(card,adjust_);
            topCard_  = card;
            card->show();
        }
    }

}




