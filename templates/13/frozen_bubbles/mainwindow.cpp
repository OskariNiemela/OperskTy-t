#include "mainwindow.hh"

#include "gameengine.hh"

MainWindow::MainWindow(GameBoard& scene, QWidget* parent) :
    QMainWindow(parent),
    view_(this)
{
    view_.setScene(&scene);
    setCentralWidget(&view_);
    setMinimumHeight(HEIGHT*GRID_SIDE + GRID_SIDE);
    setMinimumWidth(WIDTH*GRID_SIDE + GRID_SIDE);
}
