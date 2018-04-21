#include "gameboard.hh"
#include "bubbleitem.hh"

#include <QPixmap>
#include <QGraphicsSceneMouseEvent>
#include <QPropertyAnimation>

#include <iostream>
#include <vector>
#include <string>

const std::vector<std::string> BUBBLE_FILE_NAMES = {"redbubble.png", "greenbubble.png", "bluebubble.png"};

BubbleItem::BubbleItem(std::shared_ptr<Bubble> bubble, Color color, QGraphicsItem* parent):
    QGraphicsPixmapItem(parent),
    color_(color),
    bubble_(bubble)
{
    updateGraphics();
}

void BubbleItem::updateGraphics()
{
    // Load the image and scale to correct size.
    QPixmap map(QString::fromStdString("://images/" + BUBBLE_FILE_NAMES.at(color_)));
    setPixmap(map.scaledToHeight(GRID_SIDE));
 }

void BubbleItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsPixmapItem::mousePressEvent(event);
    updateGraphics();
}
