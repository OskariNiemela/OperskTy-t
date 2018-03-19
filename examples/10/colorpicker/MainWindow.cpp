#include "MainWindow.hh"

#include <QLabel>
#include <QSlider>
#include <QSpinBox>
#include <QGridLayout>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent):
QMainWindow(parent),
      redBox_(new QSpinBox(this)),
      greenBox_(new QSpinBox(this)),
      blueBox_(new QSpinBox(this)),
      colorLabel_(new QLabel(this))
{
    redBox_->setMinimum(0);
    redBox_->setMaximum(RGB_VALUE_MAX);

    greenBox_->setMinimum(0);
    greenBox_->setMaximum(RGB_VALUE_MAX);

    blueBox_->setMinimum(0);
    blueBox_->setMaximum(RGB_VALUE_MAX);

    QSlider* redSlider = new QSlider(Qt::Horizontal, this);
    redSlider->setMinimum(0);
    redSlider->setMaximum(RGB_VALUE_MAX);

    QSlider* greenSlider = new QSlider(Qt::Horizontal, this);
    greenSlider->setMinimum(0);
    greenSlider->setMaximum(RGB_VALUE_MAX);

    QSlider* blueSlider = new QSlider(Qt::Horizontal, this);
    blueSlider->setMinimum(0);
    blueSlider->setMaximum(RGB_VALUE_MAX);

    QWidget* central = new QWidget(this);
    QGridLayout* topLayout = new QGridLayout(central);
    topLayout->addWidget(new QLabel("Red:", this), 0, 0, 1, 1);
    topLayout->addWidget(redSlider, 0, 1, 1, 1);
    topLayout->addWidget(redBox_, 0, 2, 1, 1);

    topLayout->addWidget(new QLabel("Green:", this), 1, 0, 1, 1);
    topLayout->addWidget(greenSlider, 1, 1, 1, 1);
    topLayout->addWidget(greenBox_, 1, 2, 1, 1);

    topLayout->addWidget(new QLabel("Blue:", this), 2, 0, 1, 1);
    topLayout->addWidget(blueSlider, 2, 1, 1, 1);
    topLayout->addWidget(blueBox_, 2, 2, 1, 1);

    topLayout->addWidget(colorLabel_, 0, 3, 3, 1);

    setCentralWidget(central);

    connect(redSlider, SIGNAL(valueChanged(int)), redBox_, SLOT(setValue(int)));
    connect(redBox_, SIGNAL(valueChanged(int)), redSlider, SLOT(setValue(int)));

    connect(greenSlider, SIGNAL(valueChanged(int)), greenBox_, SLOT(setValue(int)));
    connect(greenBox_, SIGNAL(valueChanged(int)), greenSlider, SLOT(setValue(int)));

    connect(blueSlider, SIGNAL(valueChanged(int)), blueBox_, SLOT(setValue(int)));
    connect(blueBox_, SIGNAL(valueChanged(int)), blueSlider, SLOT(setValue(int)));

    connect(redBox_, SIGNAL(valueChanged(int)), this, SLOT(onColorChanged()));
    connect(greenBox_, SIGNAL(valueChanged(int)), this, SLOT(onColorChanged()));
    connect(blueBox_, SIGNAL(valueChanged(int)), this, SLOT(onColorChanged()));

    onColorChanged();
}

MainWindow::~MainWindow()
{}

void MainWindow::onColorChanged()
{
    QColor selectedColor(redBox_->value(), greenBox_->value(), blueBox_->value());

    QPixmap colorMap(64, 64);
    colorMap.fill(selectedColor);
    colorLabel_->setPixmap(colorMap);
}
