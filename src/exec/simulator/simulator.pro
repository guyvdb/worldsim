QT       += core gui widgets
CONFIG += c++17

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h \
    ui_mainwindow.h

FORMS += \
    mainwindow.ui

DESTDIR =../../../bin

INCLUDEPATH += $$PWD/../../


unix|win32: LIBS += -L$$OUT_PWD/../../../bin/ -lgraph
unix|win32: LIBS += -L$$OUT_PWD/../../../bin/ -lculture
unix|win32: LIBS += -L$$OUT_PWD/../../../bin/ -lmap
unix|win32: LIBS += -L$$OUT_PWD/../../../bin/ -lnumbers



