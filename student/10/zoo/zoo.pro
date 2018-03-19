TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    animal.cpp \
    bird.cpp \
    owl.cpp \ 
    giraffe.cpp \
    cockatoo.cpp \
    mammal.cpp

HEADERS += \
    animal.hh \
    bird.hh \
    owl.hh \ 
    giraffe.hh \
    cockatoo.hh \
    mammal.hh
