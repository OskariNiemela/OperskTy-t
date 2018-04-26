/*
 * TIE-02200 Ohjelmoinnin peruskurssi
 * Project: Korttipeli
 * File: opendeck.cc
 * Coder: Oskari Niemela
 * Student Number: 263440
 *
 * Desc:
 *      Contains code for the opendeck class that we use as the deck
 *      you drag cards from to the cardslots.
 *
*/

#include "opendeck.hh"

#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QPainter>
#include <QLabel>

OpenDeck::OpenDeck( QWidget *parent):
    QFrame(parent),
    layout_(new QStackedLayout(this))
{
    //setAcceptDrops(true);
    setMinimumSize(180, 260);
    setMaximumSize(180,260);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setLayout(layout_);
}

void OpenDeck::giveCards(std::vector<Card*> &cardVec)
{
    Card *card = static_cast<Card*>(layout_->currentWidget());
    while(card!=nullptr)
    {
        cardVec.push_back(card);
        layout_->removeWidget(layout_->currentWidget());
        layout_->setCurrentIndex(layout_->count()-1);

        card = static_cast<Card*>(layout_->currentWidget());
    }
}

void OpenDeck::addCard(Card *card)
{
    layout()->addWidget(card);
    layout_->setCurrentWidget(card);
    card->open();
}

void OpenDeck::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("image/card") && event->source() != this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
    } else {
        event->ignore();
    }
}

void OpenDeck::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("image/card") && event->source() != this) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void OpenDeck::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("image/card") ) {
        QByteArray itemData = event->mimeData()->data("image/card");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);
        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;

        auto deck =  static_cast<QFrame*>(event->source());
        auto layout = static_cast<QStackedLayout*> (deck->layout());
        QWidget* card = layout->currentWidget();
        layout_->addWidget(card);
        layout_->setCurrentWidget(card);
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

// Is executed when the open deck is clicked/when dragging cards
void OpenDeck::mousePressEvent(QMouseEvent *event)
{

    // Take the card thats ontop of our layout and point a pointer to it
    Card *card = static_cast<Card*>(layout_->currentWidget());

    // We cant drag anything from an empty deck
    if (card == nullptr){
        return;
    }

    // take the image of the card into pixmap
    QPixmap pixmap = *card->getCurrentSideLabel()->pixmap();

    // create a MimeData object which will contain all the data of the card
    // this will be provided to the slot were dragging the cards into.
    QMimeData *mimeData = new QMimeData;
    mimeData->setText(QString::fromStdString(card->getCardData()));

    // Create a drag object which will actually do the draggging motion
    // it will be provided with the picture of the card and its data
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos() - card->pos());

    // Put the picture of the card were dragging into grayscale for the duration
    // of the drag.
    QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
    painter.end();
    card->getCurrentSideLabel()->setPixmap(tempPixmap);

    // Begin the dragging and see if its successful

    if (drag->exec( Qt::MoveAction) == Qt::MoveAction) {
        // This will be executed if the drag was successful
        card->getCurrentSideLabel()->setPixmap(pixmap);
        layout_->removeWidget(layout_->currentWidget());
        layout_->setCurrentIndex(layout_->count()-1);
        card->setAttribute(Qt::WA_DeleteOnClose);
        card->close();

    } else {
        // If the drag was unsuccessful
        card->show();
        card->getCurrentSideLabel()->setPixmap(pixmap);
    }
}
