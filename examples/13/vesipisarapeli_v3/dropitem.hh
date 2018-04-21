#ifndef DROPITEM_H
#define DROPITEM_H

#include <QGraphicsPixmapItem>

#include "drop.hh"

class DropItem : public QGraphicsPixmapItem
{
public:
    DropItem(std::shared_ptr<Drop> drop, unsigned int size, QGraphicsItem* parent);

    // Update the image of the drop.
    void updateGraphics();

private:
    // The image size of the drop image. The size is used for both width and height.
    unsigned int size_;

    // Pointer to the represented drop object.
    std::shared_ptr<Drop> drop_;
};

#endif // DROPITEM_H
