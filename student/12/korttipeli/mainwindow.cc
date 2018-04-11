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
    connect(startGame_, SIGNAL(clicked(bool)),this,SLOT(newGame()));
    connect(stay_, SIGNAL(clicked(bool)),this, SLOT(checkWin()));
    connect(pickedCards_,&OpenDeck::scoreChange, this,&MainWindow::scorePlayer);
    connect(pickedCards_,&OpenDeck::lose,this,&MainWindow::checkWin);
    connect(houseCards_,&OpenDeck::scoreChange,this,&MainWindow::scoreHouse);
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
    pickedCards_ = new OpenDeck(Player,this);
    houseCards_ = new OpenDeck(House,this);

    stay_ = new QPushButton(this);
    startGame_ = new QPushButton(this);
    playerPoints_ = new QLabel(this);
    housePoints_ = new QLabel(this);

    deck_->setEnabled(false);
    stay_->setEnabled(false);

    // Lisätään yläriville suljettu ja avoin pakka...
    topRowLayout->addWidget(houseCards_);
    topRowLayout->addWidget(housePoints_);
    midRowLayout->addWidget(deck_);
    midRowLayout->addWidget(stay_);
    midRowLayout->addWidget(startGame_);
    bottomRowLayout->addWidget(pickedCards_);
    bottomRowLayout->addWidget(playerPoints_);

    setCentralWidget(frame);
}

void MainWindow::resetDeck()
{
    std::vector<Card*> newDeck;
    pickedCards_->giveCards(newDeck);
    houseCards_->giveCards(newDeck);
    deck_->takeCards(newDeck);
}

void MainWindow::newGame()
{

    resetDeck();

    playerPoints_->setText("0");
    housePoints_->setText("0");
    pickedCards_->resetScore();
    houseCards_->resetScore();

    Card* nu = deck_->pickCard();

    pickedCards_->addCard(nu);

    nu = deck_->pickCard();

    houseCards_->addCard(nu);

    deck_->setEnabled(true);
    stay_->setEnabled(true);
    startGame_->setEnabled(false);

}

void MainWindow::scorePlayer(unsigned score)
{
    playerPoints_->setText(QString::number(score));
}

void MainWindow::scoreHouse(unsigned score)
{
    housePoints_->setText(QString::number(score));
}

void MainWindow::playerLose()
{
    playerPoints_->setText("House Wins");
}

void MainWindow::houseLose()
{
    playerPoints_->setText("Player Wins");
}
void MainWindow::checkWin()
{
    stay_->setEnabled(false);
    startGame_->setEnabled(true);
    deck_->setEnabled(false);

    unsigned playerScore = pickedCards_->giveScore();

    if(playerScore>MAX_SCORE)
    {
        playerLose();
        return;
    }

    unsigned houseScore = houseCards_->giveScore();
    Card* nu = deck_->pickCard();
    while((houseScore<19)&&(houseScore<playerScore))
    {
        houseCards_->addCard(nu);
        houseScore = houseCards_->giveScore();
    }

    if(houseScore>MAX_SCORE)
    {
        houseLose();
        return;
    }

    if(playerScore>houseScore)
    {
        houseLose();
    }
    else
    {
        playerLose();
    }

}
