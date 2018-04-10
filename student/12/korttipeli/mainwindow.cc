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
    QHBoxLayout* midRowLayout = new QHBoxLayout();
    frameLayout->addLayout(topRowLayout);
    frameLayout->addLayout(midRowLayout);
    frameLayout->addLayout(bottomRowLayout);

    // Luodaan pakkaoliot.
    deck_ = new Deck(this);
    pickedCards_ = new OpenDeck(this);
    houseCards_ = new OpenDeck(this);

    Card* nu = deck_->pickCard();

    pickedCards_->addCard(nu);

    nu = deck_->pickCard();

    houseCards_->addCard(nu);

    // Lisätään yläriville suljettu ja avoin pakka...
    topRowLayout->addWidget(houseCards_);
    midRowLayout->addWidget(deck_);
    bottomRowLayout->addWidget(pickedCards_);



    setCentralWidget(frame);
}

void MainWindow::resetDeck()
{
    std::vector<Card*> newDeck;
    pickedCards_->giveCards(newDeck);
    deck_->takeCards(newDeck);
}
