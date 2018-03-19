#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QSpinBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:

    // The constructor.
    MainWindow(QWidget *parent = 0);

    // The destructor.
    virtual ~MainWindow();

private slots:
    // Changes the shown color when RGB-value has been changed.
    void onColorChanged();

private:
    // Color RGB-value selectors.
    QSpinBox* redBox_;
    QSpinBox* greenBox_;
    QSpinBox* blueBox_;

    // Label for showing the selected color.
    QLabel* colorLabel_;

    const int RGB_VALUE_MAX = 255;

    // No copying and no assignment.
    MainWindow(MainWindow const& other) = delete;
    MainWindow &operator=(MainWindow const& other) = delete;
};

#endif // MAINWINDOW_H
