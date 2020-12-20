CONFIG -= gui
TEMPLATE = lib
CONFIG += c++17

SOURCES += \
    geogenerator.cpp \
    georenderer.cpp \
    map.cpp

HEADERS += \
    geogenerator.h \
    georenderer.h \
    map.h


DESTDIR = ../../bin


unix|win32: LIBS += -L$$OUT_PWD/../../bin/ -lnumbers


INCLUDEPATH += $$PWD/../
#DEPENDPATH += $$PWD/../../numbers
