#include "splashanimation.hh"

SplashAnimation::SplashAnimation(GameBoard* scene, QPointF startPoint, QPointF endPoint):
    QVariantAnimation(0),
    scene_(scene),
    item_()
{
    scene_->addItem(&item_);

    // The animation runs for the given duration and moves the splash
    // smoothly from startpoint to endpoint.
    setDuration(2000);
    setKeyValueAt(0, QPointF(startPoint));
    setKeyValueAt(1, QPointF(endPoint));
}

SplashAnimation::~SplashAnimation()
{
    scene_->removeItem(&item_);
}

void SplashAnimation::updateCurrentValue(QVariant const& value)
{
    item_.setPos(value.toPointF());
}
