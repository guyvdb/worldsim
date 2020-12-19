CONFIG -= qt

TEMPLATE = lib
DEFINES += MAP_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    map.cpp \
    planetgenerator.cpp \
    util/plane.cpp

HEADERS += \
    map_global.h \
    map.h \
    planetgenerator.h \
    util/plane.h


DESTDIR = ../../../bin

unix|win32: LIBS += -L$$OUT_PWD/../../../bin/ -lmath


INCLUDEPATH += $$PWD/../../math
DEPENDPATH += $$PWD/../../math
