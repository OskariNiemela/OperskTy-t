#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include <QGraphicsScene>
#include <QSequentialAnimationGroup>
#include <QPainter>

#include "bubble.hh"

#include <memory>

const int HEIGHT = 12;
const int WIDTH = 10;

// Size of the grid i.e. both width and height.
const int GRID_SIDE = 50;

class GameBoard : public QGraphicsScene
{
    Q_OBJECT

public:
    GameBoard(QObject* parent = nullptr);

    // Add a new bubble graphics in the given grid coordinates.
    void addBubble(int column, int row, std::shared_ptr<Bubble> bubble);

    // Remove a bubble graphics from the given grid coordinates.
    void removeBubble(int column, int row);

    // Show a splash animation from the start grid coordinates to
    // end grid coordinates.
    void animateSplash(int startX, int startY, int endX, int endY);

signals:
    // Emitted when user clicks a grid square.
    void mouseClick(int x, int y);

protected:
    // Draws the grid lines.
    virtual void drawBackground(QPainter* painter, QRectF const& rect) override;

    // Handler for mouse click events.
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    // Convert grid coordinates to scene position.
    QPoint gridToPoint(int column, int row) const;

    // Convert grid coordinates to scene position at the center of the grid square.
    QPoint gridToPointCenter(int column, int row) const;

    // Group (=list) of splash animation to run in sequence.
    QSequentialAnimationGroup animations_;
};

#endif // GAMEBOARD_HH
