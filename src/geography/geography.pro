CONFIG -= qt
TEMPLATE = lib
CONFIG += c++17
SOURCES += \
    biome/biome.cpp \
    geography.cpp

HEADERS += \
    biome/biome.h \
    geography_global.h \
    geography.h

DISTFILES += \
  notes.txt


DESTDIR = ../../bin

unix|win32: LIBS += -L$$OUT_PWD/../../bin/ -lgraph

INCLUDEPATH += $$PWD/../
#DEPENDPATH += $$PWD/../



