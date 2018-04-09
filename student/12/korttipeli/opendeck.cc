#include "opendeck.hh"

#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QPainter>
#include <QLabel>

OpenDeck::OpenDeck(QWidget *parent):
    QFrame(parent),
    layout_(new QStackedLayout(this))
{
    //setAcceptDrops(true);
    setMinimumSize(180, 260);
    setMaximumSize(180, 260);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setLayout(layout_);
}

void OpenDeck::addCard(Card *card)
{
    layout()->addWidget(card);
    layout_->setCurrentWidget(card);
    card->turn();

}



void OpenDeck::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("image/card") && event->source() != this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
    } else {
        event->ignore();
    }
}

void OpenDeck::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("image/card") && event->source() != this) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void OpenDeck::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("image/card") ) {
        QByteArray itemData = event->mimeData()->data("image/card");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);
        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;

        auto deck =  static_cast<QFrame*>(event->source());
        auto layout = static_cast<QStackedLayout*> (deck->layout());
        QWidget* card = layout->currentWidget();
        layout_->addWidget(card);
        layout_->setCurrentWidget(card);
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

// Suoritetaan, kun avoimen pakan päällimmäinen kortti raahataan jonnekin.
void OpenDeck::mousePressEvent(QMouseEvent *event)
{
    // 1) Metodin alkuosa suoritetaan, kun avopakkaa klikataan.

    // Otetaan pakan sisältämä kortti osoittimen päähän.
    Card *card = static_cast<Card*>(layout_->currentWidget());

    // Tyhjästä pakasta ei voi raahata, eli lopetetaan.
    if (card == nullptr){
        return;
    }

    // Otetaan raahattavan kortin kuva valmiiksi muuttujaan pixmap.
    QPixmap pixmap = *card->getCurrentSideLabel()->pixmap();

    // Luodaan mimeData-olio, jonka avulla raahattavan kortin tiedot (=merkkijono)
    // välitetään sinne, minne kortti raahataan.
    QMimeData *mimeData = new QMimeData;
    mimeData->setText(QString::fromStdString(card->getCardData()));

    // Luodaan drag-olio, jonka avulla raahaaminen tapahtuu. Drag-oliolle annetaan
    // raahauksen aikana näytettävä kuva, sekä tiedot raahattavasta oliosta.
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos() - card->pos());  // Se kohta raahattavasta kuvasta, jonka pitää osua kohteeseen.

    // Asetetaan harmautettu korttikuva väliaikaiseksi korttikuvaksi raahaamisen ajaksi.
    QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
    painter.end();
    card->getCurrentSideLabel()->setPixmap(tempPixmap);

    // 2) Aloitetaan raahaus ja tarkastellaa onnistuiko.

    if (drag->exec( Qt::MoveAction) == Qt::MoveAction) {
        // Tämä suoritetaan, jos raahaus onnistui.
        card->getCurrentSideLabel()->setPixmap(pixmap);
        layout_->removeWidget(layout_->currentWidget());
        layout_->setCurrentIndex(layout_->count()-1);
        card->setAttribute(Qt::WA_DeleteOnClose);
        card->close();

    } else {
        // Tämä suoritetaan, jos raahaus epäonnistui.
        card->show();
        card->getCurrentSideLabel()->setPixmap(pixmap);
    }
}
