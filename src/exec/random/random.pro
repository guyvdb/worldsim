TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp


DESTDIR = ../../../bin

INCLUDEPATH += $$PWD/../../

unix|win32: LIBS += -L$$OUT_PWD/../../../bin/ -lnumbers
unix|win32: LIBS += -L$$OUT_PWD/../../../bin/ -lmap

