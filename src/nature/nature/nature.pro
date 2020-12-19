CONFIG -= qt

TEMPLATE = lib
DEFINES += NATURE_LIBRARY

CONFIG += c++17

SOURCES += \
    ecosystem/ecosystem.cpp \
    fauna/animal.cpp \
    flora/flora.cpp \
    nature.cpp \
    planet/planet.cpp \
    species.cpp

HEADERS += \
    ecosystem/ecosystem.h \
    fauna/animal.h \
    flora/flora.h \
    nature_global.h \
    nature.h \
    planet/planet.h \
    species.h

DESTDIR = ../../bin

unix|win32: LIBS += -L$$OUT_PWD/../../bin/ -lgraph

INCLUDEPATH += $$PWD/../../graph
DEPENDPATH += $$PWD/../../graph
