#include "dropitem.hh"

#include <QPixmap>

#include "splash.hh"
#include <vector>

#include <QGraphicsSceneMouseEvent>
#include <QPropertyAnimation>

#include <iostream>
#include <vector>

const std::vector<std::string> images = {
    "images/vesipisara1.png",
    "images/vesipisara2.png",
    "images/vesipisara3.png",
    "images/vesipisara4.png"
};

DropItem::DropItem(std::shared_ptr<Drop> drop, unsigned int size, QGraphicsItem* parent):
    QGraphicsPixmapItem(parent),
    drop_(drop),
    size_(size)
{
    updateGraphics();
}

void DropItem::updateGraphics()
{
    int level = drop_->waterAmount();

    // Load the image and scale to correct size.
    QPixmap map(QString::fromStdString(images.at(level-1)));
    setPixmap(map.scaledToHeight(size_));
 }
