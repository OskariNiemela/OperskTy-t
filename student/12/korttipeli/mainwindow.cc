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
 * Notes:
 *      Assistants made the file originally I just made the
 *      one rule function.
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
    connect(deck_, &Deck::cardPicked, this, &MainWindow::addCards);

}

MainWindow::~MainWindow()
{

}

void MainWindow::addCards()
{
    Card* nu = nullptr;
    for(CardSlot* slot:slots_)
    {
        nu = deck_->pickCard();
        if(nu==nullptr)
        {
            break;
        }
        else
        {
            slot->addCard(nu);
        }

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
    QHBoxLayout* midRowLayout = new QHBoxLayout();
    frameLayout->addLayout(topRowLayout);
    frameLayout->addLayout(midRowLayout);
    frameLayout->addLayout(bottomRowLayout);

    // Luodaan pakkaolio.
    deck_ = new Deck(this);
    for(int i=0;i<7;i++)
    {
        CardSlot* bo = new CardSlot(&GameRules::checkWin,this);
        slots_.push_back(bo);
    }

    winLabel_ = new QLabel(this);

    winLabel_->setMinimumSize(100,50);
    winLabel_->setMaximumSize(100,50);

    // How many cards at most do we give a cardslot at the beginning
    int cards = 7;
    Card* boi = nullptr;
    for(CardSlot* go:slots_)
    {
        for(int i=0;i<cards;i++)
        {
            boi = deck_->pickCard();
            go->addCardClosed(boi);
        }
        cards--;
    }

    topRowLayout->addWidget(deck_);
    topRowLayout->addWidget(winLabel_);
    for(CardSlot* slot:slots_)
    {
        bottomRowLayout->addWidget(slot);
    }


    setCentralWidget(frame);
}
