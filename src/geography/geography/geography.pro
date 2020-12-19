CONFIG -= qt

TEMPLATE = lib
DEFINES += GEOGRAPHY_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

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

INCLUDEPATH += $$PWD/../graph
DEPENDPATH += $$PWD/../graph



