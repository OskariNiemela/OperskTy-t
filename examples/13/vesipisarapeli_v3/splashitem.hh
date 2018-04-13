#ifndef SPLASHITEM_H
#define SPLASHITEM_H

#include <QGraphicsPixmapItem>

class SplashItem : public QGraphicsPixmapItem
{
public:
    SplashItem(int startX, int startY, int endX, int endY);
};

#endif // SPLASHITEM_H
