QT       += core gui widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui


DESTDIR = ../../../bin

DEPENDPATH += $$PWD/../../
INCLUDEPATH += $$PWD/../../

unix|win32: LIBS += -L$$OUT_PWD/../../../bin/ -lnumbers
unix|win32: LIBS += -L$$OUT_PWD/../../../bin/ -lmap

