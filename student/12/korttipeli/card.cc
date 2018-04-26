/*
 * TIE-02200 Ohjelmoinnin Peruskurssi
 * Project: Korttipeli
 * Project Coder: Oskari Niemela
 * Student Number: 263440
 * File: card.cc
 *
 * Desc:
 *      Contains all the code for the Card class.
 *
*/

#include <QPainter>
#include <QMouseEvent>
#include <QSizePolicy>
#include "card.hh"

unsigned const FRONT_INDEX = 1;
unsigned const BACK_INDEX = 0;
unsigned const CARD_WIDTH = 177;
unsigned const CARD_HEIGHT = 249;
unsigned const DEFAULT_STACK_OFFSET = 35;
QColor const CARD_FRONT_COLOR = QColor(250,239,168,255);
QSize const SUIT_PIXMAP_SIZE = QSize(30,30);

Card::Card(CardSuit suit, unsigned value, QWidget *parent) :
    QFrame(parent),
    suit_(suit),
    value_(value),
    open_(false),
    canOpen_(false),
    backPixmap_(":/cards/card-back-177x249.png"),
    stackedCard_(nullptr)
{
    setBaseSize(CARD_WIDTH, CARD_HEIGHT);
    setMinimumSize(CARD_WIDTH, CARD_HEIGHT);
    setMaximumWidth(CARD_WIDTH);
    QSizePolicy policy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    setSizePolicy(policy);
    setupLayout();

}

bool Card::isOpen()
{
    return open_;
}

void Card::allowOpen()
{
    canOpen_ = true;
}

void Card::stackCard(Card *card, bool adjustBorder)
{
    card->setParent(this);

    //if we adjust the border, then tweak the position of the card
    // were about to stack and also expand our borders
    if (adjustBorder)
    {
        card->move(0, DEFAULT_STACK_OFFSET);
        stackedCard_ = card;
        connect(stackedCard_, &Card::resized, this, &Card::expand);
        expand();
    }
    else
    {
        // return the stacked cards position back to normal
        card->move(0,0);
        stackedCard_ = card;
    }

}

void Card::removeStackedCards()
{
    stackedCard_ = nullptr;
}

std::string Card::getCardData()
{
    std::string rVal;
    if(stackedCard_ != nullptr) {
        rVal += stackedCard_->getCardData() + ";";
    }
    rVal += std::to_string(value_) +
            "," +
            std::to_string(suit_) +
            "," +
            std::to_string(open_)
            ;
    return rVal;
}

QLabel* Card::getCurrentSideLabel()
{
    if (open_){
        return findChild<QLabel*>(QString ("front"));
    } else {
        return findChild<QLabel*>(QString ("back"));
    }
}

// Turn the card around
void Card::turn()
{
    open_ = !open_;
    if (open_){
        findChild<QLabel*>(QString ("front"))->show();
        findChild<QLabel*>(QString ("back"))->hide();
    } else {
        findChild<QLabel*>(QString ("front"))->hide();
        findChild<QLabel*>(QString ("back"))->show();
    }
}

// increase the size of the drawing border
void Card::expand()
{
    setGeometry(x(), y(), width(), height() + DEFAULT_STACK_OFFSET);
    emit resized();
}

// Open the card face up.
void Card::open()
{
    open_ = true;
    findChild<QLabel*>(QString ("front"))->show();
    findChild<QLabel*>(QString ("back"))->hide();
}

// Executed when the card is double clicked
void Card::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(canOpen_&&(stackedCard_==nullptr)){
        turn();
        event->accept();
    }
    else {
        event->ignore();
    }
}

void Card::setupLayout()
{
    setSuitPixmap();
    setupBack();
    setupFront();
}

// Set the correct land picture so it may be used in drawing the card
void Card::setSuitPixmap()
{
    switch (suit_) {
    case SPADE:
        suitPixmap_ = QPixmap(":/cards/spade-300px.png").scaled(SUIT_PIXMAP_SIZE, Qt::KeepAspectRatio);
        break;
    case CLUB:
        suitPixmap_ = QPixmap(":/cards/club-300px.png").scaled(SUIT_PIXMAP_SIZE, Qt::KeepAspectRatio);
        break;
    case DIAMOND:
        suitPixmap_ = QPixmap(":/cards/diamond-300px.png").scaled(SUIT_PIXMAP_SIZE, Qt::KeepAspectRatio);
        break;
    case HEART:
        suitPixmap_ = QPixmap(":/cards/heart-300px.png").scaled(SUIT_PIXMAP_SIZE, Qt::KeepAspectRatio);
        break;
    default:
        break;
    }
}

// Draws the back of the card
void Card::setupBack()
{
    // Create a QLabel object which will house the picture of the back of the card
    QLabel* backImage = new QLabel(this);
    backImage->setObjectName("back");
    backImage->setPixmap(backPixmap_);
    backImage->show();
}

// Draws the front of the card
void Card::setupFront()
{
    // Create a new QLabel object
    QLabel* frontImage = new QLabel(this);
    frontImage->setObjectName("front");

    // Create a new QPixmap object and start drawing the front of the card
    QPixmap frontPixmap(backPixmap_.size());
    frontPixmap.fill(Qt::transparent);
    QPainter painter (&frontPixmap);

    // Draw the base of the card, a rectangle with rounded edges
    QPainterPath path;
    path.addRoundedRect(QRectF(1, 1, frontPixmap.width()-1, frontPixmap.height()-2),
                        15, 15, Qt::RelativeSize);
    painter.fillPath(path, CARD_FRONT_COLOR);
    painter.drawPath(path);

    // Draw the value of the card and its suit
    painter.setPen(QPen(Qt::black));
    QFont font = painter.font();
    font.setPixelSize(suitPixmap_.height());
    painter.setFont(font);
    painter.drawPixmap(frontPixmap.width()/2-suitPixmap_.width(), 5,
                       suitPixmap_, 0, 0, 0, 0);
    painter.drawPixmap(frontPixmap.width()/2-suitPixmap_.width()/2,
                       frontPixmap.height()-suitPixmap_.height()*1.2,
                       suitPixmap_,0,0,0,0);
    painter.drawText(frontPixmap.width()/2, 0, suitPixmap_.width() + 5,
                     suitPixmap_.height() + 5, Qt::AlignCenter, QString::number(value_));

    // Set the picture we drew to be displayed on the frontimage QLabel
    frontImage->setPixmap(frontPixmap);
    frontImage->hide();
}
