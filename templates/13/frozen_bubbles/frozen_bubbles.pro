TEMPLATE = app
CONFIG += c++11 qt
QT += core widgets
CONFIG -= app_bundle


SOURCES += main.cpp \
    bubble.cpp \
    mainwindow.cpp \
    bubbleitem.cpp \
    gameengine.cpp \
    splashanimation.cpp \
    splashitem.cpp \
    gameboard.cpp

HEADERS += \
    bubble.hh \
    mainwindow.hh \
    bubbleitem.hh \
    gameengine.hh \
    splashanimation.hh \
    splashitem.hh \
    gameboard.hh

RESOURCES += \
    images.qrc
