TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp


DESTDIR = ../../bin

unix|win32: LIBS += -L$$OUT_PWD/../../bin/ -lmath

INCLUDEPATH += $$PWD/../math
DEPENDPATH += $$PWD/../math


unix|win32: LIBS += -L$$OUT_PWD/../../bin/ -lmap

INCLUDEPATH += $$PWD/../map
DEPENDPATH += $$PWD/../map
