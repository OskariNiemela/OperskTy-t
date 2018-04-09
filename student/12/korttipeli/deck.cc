#include "deck.hh"

#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QPainter>
#include <QLabel>

std::vector<std::string> Deck::split(std::string user_string, char separator,bool ignore_empty)
{
    std::size_t separator_index = user_string.find(separator);
    std::vector<std::string> separated;
    if(separator_index == std::string::npos)
    {
        separated.push_back(user_string);
        return separated;
    }

    while(separator_index!=std::string::npos)
    {
        int substr_length = static_cast<int>(separator_index);
        if(substr_length == 0){
            if(not ignore_empty)
            {
                separated.push_back(user_string.substr(0,substr_length));
            }
        }else
        {
            separated.push_back(user_string.substr(0,substr_length));
        }
        substr_length++;
        user_string.erase(0,substr_length);
        separator_index = user_string.find(separator);

    }
    separated.push_back(user_string);
    return separated ;
}



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

void Deck::takeCards(std::vector<Card*> &cards)
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

// Suoritetaan, kun pakkaa klikataan.
void Deck::mousePressEvent(QMouseEvent *event)
{
    // Ohjelma ei saa kaatua tyhjän pakan klikkaukseen.
    if (cards_.empty()){
        fillDeck();
        return;
    }

    // Otetaan osoittimen päähän pakan päällimmäinen kortti ja poistetaan se pakasta.
    Card* card = cards_.back();
    cards_.pop_back();

    // Ohjelma ei saa kaatua, jos korttia ei olekaan.
    if (!card){
        return;
    }

    // Ilmoitetaan, että pakasta otettiin kortti.
    emit cardPicked(card);

    // Hyväksytään klikkaus, koska se käsitellään aina tässä metodissa.
    event->accept();
}

