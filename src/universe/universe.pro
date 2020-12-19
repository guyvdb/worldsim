CONFIG -= qt

TEMPLATE = lib
DEFINES += UNIVERSE_LIBRARY

CONFIG += c++11

SOURCES += \
    astronomicalobject.cpp \
    moon.cpp \
    planet.cpp \
    star.cpp \
    universe.cpp

HEADERS += \
    astronomicalobject.h \
    moon.h \
    planet.h \
    star.h \
    universe_global.h \
    universe.h


DESTDIR = ../../bin

unix|win32: LIBS += -L$$OUT_PWD/../../bin/ -lgraph

INCLUDEPATH += $$PWD/../graph
DEPENDPATH += $$PWD/../graph
