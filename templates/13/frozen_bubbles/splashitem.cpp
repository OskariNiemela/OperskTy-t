#include "splashitem.hh"
#include "gameboard.hh"

SplashItem::SplashItem(): QGraphicsPixmapItem(0)
{
    const int SPLASH_SIZE = GRID_SIDE;

    QPixmap pixmap("://images/bluesplash.png");
    setPixmap(pixmap.scaledToHeight(SPLASH_SIZE));

    // Offset the image evenly around its centerpoint.
    setOffset(-SPLASH_SIZE/2, -SPLASH_SIZE/2);

    // Rotate the image according to the travel direction.
    // The original image travels from left to right.
    setRotation(270);
}
