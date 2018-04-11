#ifndef OPENDECK_HH
#define OPENDECK_HH
#include <QFrame>

unsigned const MAX_SCORE = 21;

enum Control {Player,House};

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

    Q_OBJECT

public:
    OpenDeck(Control control, QWidget* parent = 0);
    void giveCards(std::vector<Card *> &cardVec);
    void resetScore();
    unsigned giveScore();
public slots:
    void addCard(Card* card);
signals:
    void scoreChange(unsigned cardScore);
    void lose(bool player);
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent* event);
    void mousePressEvent(QMouseEvent *event);
private:
    QStackedLayout* layout_;  // Sisältää ne kortti-widgetit, jotka avopakassa on.
    Control isPlayer;
    unsigned score;
};

#endif // OPENDECK_HH
