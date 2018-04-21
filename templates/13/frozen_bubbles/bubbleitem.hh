#ifndef BUBBLEITEM_H
#define BUBBLEITEM_H

#include <QGraphicsPixmapItem>

#include "bubble.hh"

class BubbleItem : public QGraphicsPixmapItem
{
public:
    BubbleItem(std::shared_ptr<Bubble> bubble, Color color, QGraphicsItem* parent);

    // Update the image of the bubble.
    void updateGraphics();

protected:
    // Handler for mouse click events.
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    Color color_;

    // Pointer to the represented bubble object.
    std::shared_ptr<Bubble> bubble_;
};

#endif // BUBBLEITEM_H
