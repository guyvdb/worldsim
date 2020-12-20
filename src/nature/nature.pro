CONFIG -= qt
TEMPLATE = lib
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
    nature.h \
    planet/planet.h \
    species.h

DESTDIR = ../../bin

unix|win32: LIBS += -L$$OUT_PWD/../../bin/ -lgraph

INCLUDEPATH += $$PWD/../
#DEPENDPATH += $$PWD/../
