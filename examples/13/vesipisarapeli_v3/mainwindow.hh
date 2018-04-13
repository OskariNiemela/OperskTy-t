#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>

#include "gameboard.hh"
#include "gameengine.hh"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(GameBoard &scene, QWidget* parent = nullptr);

private:
    QGraphicsView view_;
};

#endif // MAINWINDOW_H
