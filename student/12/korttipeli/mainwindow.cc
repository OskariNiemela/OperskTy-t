/*
 * TIE-02200 Ohjelmoinnin peruskurssi
 * Project: Korttipeli
 * File: gamerules.hh
 * Coder: Oskari Niemela
 * Student Number: 263440
 *
 * Desc:
 *      Contains the code for building the MainWindow
 *      plus some methods used for distributing cards
 *      and doing the things we need to do when we win.
 *
*/

#include <QFrame>
#include <QHBoxLayout>

#include "mainwindow.hh"
#include "cardslot.hh"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    setupLayout();
    connect(deck_, &Deck::cardPicked, pickedCards_, &OpenDeck::addCard);
    connect(deck_,&Deck::refillDeck,this,&MainWindow::refillDeck);
    for(CardSlot* slot:winSlots_)
    {
        connect(slot,&CardSlot::wins,this,&MainWindow::landComplete);
    }

}

MainWindow::~MainWindow()
{
    for(CardSlot* slot:slots_)
    {
        delete slot;
    }

    for(CardSlot* winSlot:winSlots_)
    {
        delete winSlot;
    }

    delete winLabel_;
    delete pickedCards_;
    delete deck_;
}

void MainWindow::playerWin()
{
    // Disable the cardslots and the closed/open deck
    for(CardSlot* slot:slots_)
    {
        slot->setEnabled(false);
    }

    for(CardSlot* winSlot:winSlots_)
    {
        winSlot->setEnabled(false);
    }
    pickedCards_->setEnabled(false);
    deck_->setEnabled(false);

    winLabel_->setText("YOU WIN");

}

void MainWindow::refillDeck()
{
    std::vector<Card*> cards;
    pickedCards_->giveCards(cards);

    deck_->getCards(cards);

}

void MainWindow::landComplete()
{
       lands_++;

       if(lands_>=4)
       {
           playerWin();
       }
}

void MainWindow::setupLayout()
{
    // Pääikkunan isoimpana rakenteena on frame, joka sisältää...
    QFrame* frame = new QFrame;
    QVBoxLayout* frameLayout = new QVBoxLayout(frame);

    // ... alarivin ja ylärivin.
    QHBoxLayout* bottomRowLayout = new QHBoxLayout();
    QHBoxLayout* topRowLayout = new QHBoxLayout();
    frameLayout->addLayout(topRowLayout);
    frameLayout->addLayout(bottomRowLayout);

    // Luodaan pakkaolio.
    deck_ = new Deck(this);

    for(int i=0;i<7;i++)
    {
        CardSlot* cardSlot = new CardSlot(&GameRules::checkDiffColour,this);
        slots_.push_back(cardSlot);
    }


    pickedCards_ = new OpenDeck(this);


    for(int i=0;i<4;i++)
    {
        CardSlot* winSlot = new CardSlot(&GameRules::checkSameLandPlus,this,false,true);
        winSlots_.push_back(winSlot);
    }

    winLabel_ = new QLabel(this);

    winLabel_->setMinimumSize(100,50);
    winLabel_->setMaximumSize(100,50);

    // How many cards at most do we give a cardslot at the beginning
    int cards = 7;
    Card* card = nullptr;
    for(CardSlot* slot:slots_)
    {
        for(int i=0;i<cards;i++)
        {
            card = deck_->pickCard();
            slot->addCard(card,false);
        }
        cards--;
    }

    topRowLayout->addWidget(deck_);
    topRowLayout->addWidget(pickedCards_);

    topRowLayout->addWidget(winLabel_);

    for(CardSlot* slot:winSlots_)
    {
        topRowLayout->addWidget(slot);
    }

    for(CardSlot* slot:slots_)
    {
        bottomRowLayout->addWidget(slot);
    }

    lands_ = 0;
    setCentralWidget(frame);
}
