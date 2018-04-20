#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "gameboard.hh"

#include "bubble.hh"
#include <vector>
#include <memory>
#include <random>


class GameEngine : public QObject
{
    Q_OBJECT

public:

    GameEngine(GameBoard& gameBoard, int seed = 0);

    // Set up the board and the datastructures for a new game.
    void initialize();

    // For removing a bubble from the board.
    void removeBubble(int x, int y);

    // For getting a pointer to a bubble-object in certain coordinates.
    std::shared_ptr<Bubble> bubbleAt(int x, int y) const;

signals:
    // To be emitted when the qame is finished.
    void quitGame();

public slots:
    // TODO: Implement this method (and other methods as needed).
    void launchSplash(int clickX, int clixkY);

private:
    // The data model of the game board.
     std::vector< std::vector< std::shared_ptr<Bubble> > > board_;

    // Access to the graphical presentation of the game board.
    GameBoard& graphicalGameBoard_;

    // The amount of water that can be used during the game.
    int waterTank_;

    // Random number generator for initializing the board.
    std::default_random_engine randomEngine_;
};

#endif // GAMEENGINE_H
