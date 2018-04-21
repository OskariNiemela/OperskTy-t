#include "gameengine.hh"

#include <QMessageBox>
#include <QCoreApplication>
#include <QTime>

#include <thread>

GameEngine::GameEngine(GameBoard& gameBoard, int seed):
    QObject(0),
    board_(),
    graphicalGameBoard_(gameBoard),
    waterTank_(10)
{
    // Required for random number generation in initialization.
    if(seed == 0) {
        // If there was no seed value given as a parameter for the
        // constructor, use a seed value from the clock.
        randomEngine_.seed(time(NULL));
    } else {
        // Otherwise use the seed value given as a parameter.
        randomEngine_.seed(seed);
    }

    initialize();
}

void GameEngine::initialize()
{
    waterTank_ = 10;
    board_.clear();

    for(int y = 0; y < HEIGHT; ++y)
    {
        std::vector< std::shared_ptr<Bubble> > row;
        for(int x = 0; x < WIDTH; ++x)
        {
            std::shared_ptr<Bubble> newBubble = nullptr;

            // There will be bubbles only in the top 3/4 of the board only in the middle
            // (i.e. not in the first two and last two columns).
            if (y < HEIGHT*3/4 && x > 1 && x < WIDTH-2)
            {
                // Generate random numbers using the enumearation type defined in
                // file bubble.hh. The value COLOR_COUNT is used to represent no bubble.
                std::uniform_int_distribution<int> distribution(RED,COLOR_COUNT);

                // If you want no empty squares, change the initialization to:
                // std::uniform_int_distribution<int> distribution(RED,BLUE);

                Color color = static_cast<Color>(distribution(randomEngine_));
                if(color != COLOR_COUNT) {
                    newBubble = std::make_shared<Bubble>(x, y, color);
                }
            }
            row.push_back(newBubble);
        }
        board_.push_back(row);
    }

    graphicalGameBoard_.clear();
    for (int row = 0; row < HEIGHT; row++)
    {
        for (int column = 0; column < WIDTH; column++)
        {
            std::shared_ptr<Bubble> bubble = bubbleAt(column, row);
            if (bubble != nullptr)
            {
                graphicalGameBoard_.addBubble(column, row, bubble);
            }
        }
    }
}


void GameEngine::removeBubble(int x, int y)
{
    board_.at(y).at(x) = nullptr;
}

std::shared_ptr<Bubble> GameEngine::bubbleAt(int x, int y) const
{
    if (0 <= x and x < WIDTH and 0 <= y and y < HEIGHT){
        return board_.at(y).at(x);
    }
    else{
        return nullptr;
    }
}

void GameEngine::launchSplash(int clickX, int clickY)
{
    std::cout << "Click coordinates: x=" << clickX << " y=" << clickY << std::endl;
    const QPointF ANIMATION_START(WIDTH*GRID_SIDE/2, HEIGHT*GRID_SIDE);
    waterTank_--;



    if (waterTank_ <= 0 )
    {
        int messageBoxResult = 0;

        messageBoxResult = QMessageBox::question(0, "Oops!", "No more water. Try again?",
                                               QMessageBox::Yes, QMessageBox::No);

        if (messageBoxResult == QMessageBox::Yes)
        {
            initialize();
        }
        else
        {
            emit quitGame();
        }
    }
}
