#include "gameboard.hh"
#include "gameengine.hh"
#include "bubble.hh"
#include "bubbleitem.hh"
#include "splashanimation.hh"

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QCoreApplication>
#include <QTime>

#include <QMessageBox>

#include <iostream>

GameBoard::GameBoard(QObject* parent):
    QGraphicsScene(parent),
    animations_()
{
    // The scene where items can be drawn starts from coordinate 0,0
    // and the width and height are set to KOKO*GRID_SIDE.
    setSceneRect(0, 0, WIDTH*GRID_SIDE, HEIGHT*GRID_SIDE);
}

void GameBoard::addBubble(int column, int row, std::shared_ptr<Bubble> bubble)
{
    // Create a new graphical item and add it to the scene so it will be drawn.
    BubbleItem* item = new BubbleItem(bubble, bubble->getColor(), 0);
    addItem(item);

    // Set the correct position within the scene.
    QPointF position = gridToPoint(column, row);
    item->setPos(position);
}

void GameBoard::removeBubble(int column, int row)
{
    QPointF scenePoint = gridToPointCenter(column, row);

    // Find the item at the given point and remove it.
    QGraphicsItem* clickedItem = itemAt(scenePoint, QTransform());

    if (clickedItem != 0) {
        removeItem(clickedItem);
        delete clickedItem;
    }
}

void GameBoard::animateSplash(int startX, int startY, int endX, int endY)
{
    QPoint startPoint (startX, startY);
    QPoint endPoint (endX, endY);

    SplashAnimation* animation = new SplashAnimation(this, startPoint, endPoint);

    animations_.addAnimation(animation);
    animations_.start();
    // Animations are executed in the event loop, so process events until
    // the animations are finished.
    while (animations_.state() == QAbstractAnimation::Running)
    {
         QCoreApplication::processEvents(QEventLoop::AllEvents);
    }

    animations_.clear();
}


void GameBoard::drawBackground(QPainter* painter, QRectF const& rect)
{
    Q_UNUSED(rect);
    QColor backGroundColor(225, 225, 225);

    painter->save();
    painter->setPen( QPen(Qt::darkGray,1) );
    painter->setBrush(QBrush());
    painter->drawRect(sceneRect());
    painter->restore();

    // Draw gridlines for the game area.
    // REMOVE THE COMMENT IF YOU WANT TO USE THE GRID FOR DEBUGGING!
    /*
    for (int row = 0; row < HEIGHT; row++)
    {
        for (int column = 0; column < WIDTH; column++)
        {
            QRectF square(column*GRID_SIDE, row*GRID_SIDE, GRID_SIDE, GRID_SIDE);
            painter->fillRect(square, backGroundColor);
            painter->drawRect(square);
        }
    }
    */
}

void GameBoard::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsScene::mousePressEvent(event);

    QPoint clickPosition = event->scenePos().toPoint();

    if (0 <= clickPosition.x() and clickPosition.x() <= GRID_SIDE*WIDTH and
        0 <= clickPosition.y() and clickPosition.y() <= GRID_SIDE*HEIGHT)
    {
        // Only accept new mouse clicks when animations are not running.
        if (animations_.state() != QAbstractAnimation::Running)
        {
            emit mouseClick(clickPosition.x(), clickPosition.y());
        }
    }
}

QPoint GameBoard::gridToPoint(int column, int row) const
{
    return QPoint(GRID_SIDE*column, GRID_SIDE*row);
}

QPoint GameBoard::gridToPointCenter(int column, int row) const
{
    int x = column * GRID_SIDE + GRID_SIDE/2;
    int y = row * GRID_SIDE + GRID_SIDE/2;
    return QPoint(x, y);
}
