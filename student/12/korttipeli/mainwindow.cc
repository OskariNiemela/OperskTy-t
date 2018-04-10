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
    connect(deck_, &Deck::fillDeck, this, &MainWindow::resetDeck);
}

MainWindow::~MainWindow()
{
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

    // Luodaan pakkaoliot.
    deck_ = new Deck(this);
    pickedCards_ = new OpenDeck(this);

    // Lisätään yläriville suljettu ja avoin pakka...
    topRowLayout->addWidget(deck_);
    topRowLayout->addWidget(pickedCards_);

    Card* nu = deck_->pickCard();
    // ... ja alariville yksi cardslot.
    CardSlot* slot1 = new CardSlot(&GameRules::checkIfSameSuit,true,this);
    slot1->addCard(nu);

    nu = deck_->pickCard();

    CardSlot* slot2 = new CardSlot(&GameRules::checkIfSameSuit,false,this);

    slot2->addCard(nu);

    bottomRowLayout->addWidget(slot1);
    bottomRowLayout->addWidget(slot2);
    bottomRowLayout->addWidget(new CardSlot(&GameRules::checkIfHeart,true, this));
    bottomRowLayout->addWidget(new CardSlot(&GameRules::checkIfHeart,true, this));
    bottomRowLayout->addWidget(new CardSlot(&GameRules::checkIfHeart,true, this));

    setCentralWidget(frame);
}

void MainWindow::resetDeck()
{
    std::vector<Card*> newDeck;
    pickedCards_->giveCards(newDeck);
    deck_->takeCards(newDeck);
}
