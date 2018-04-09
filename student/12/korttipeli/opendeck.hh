#ifndef OPENDECK_HH
#define OPENDECK_HH
#include <QFrame>


QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

#include <vector>
#include <iostream>
#include <QStackedLayout>

#include "card.hh"
class OpenDeck : public QFrame
{
public:
    OpenDeck(QWidget* parent = 0);
    void giveCards(std::vector<Card *> &cardVec);
public slots:
    void addCard(Card* card);
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent* event);
    void mousePressEvent(QMouseEvent *event);
private:
    QStackedLayout* layout_;  // Sisältää ne kortti-widgetit, jotka avopakassa on.
};

#endif // OPENDECK_HH
