QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h \
    ui_mainwindow.h

FORMS += \
    mainwindow.ui

DESTDIR =../../bin

INCLUDEPATH += $$PWD/../graph
DEPENDPATH += $$PWD/../graph
unix|win32: LIBS += -L$$OUT_PWD/../../bin/ -lgraph

INCLUDEPATH += $$PWD/../culture
DEPENDPATH += $$PWD/../culture
unix|win32: LIBS += -L$$OUT_PWD/../culture/ -lculture


INCLUDEPATH += $$PWD/../map
DEPENDPATH += $$PWD/../map
unix|win32: LIBS += -L$$OUT_PWD/../map/ -lmap
