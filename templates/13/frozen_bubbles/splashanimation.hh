#ifndef SPLASHANIMATION_H
#define SPLASHANIMATION_H

#include <QVariantAnimation>

#include "gameboard.hh"
#include "splashitem.hh"

class SplashAnimation : public QVariantAnimation
{
public:
    // The constructor.
    SplashAnimation(GameBoard* scene, QPointF startPoint, QPointF endPoint);

    // The destructor.
    ~SplashAnimation();

    // Updates the splash movement.
    void updateCurrentValue(QVariant const& value) override;

private:
    // The scene where the animation takes place.
    GameBoard* scene_;

    // The item to use for the animation.
    SplashItem item_;
};

#endif // SPLASHANIMATION_H
