CONFIG -= gui
TEMPLATE = lib
CONFIG += c++17

SOURCES += \
    geogenerator.cpp \
    geometry.cpp \
    heatmapgradient.cpp \
    heatmaprenderer.cpp \
    map.cpp \
    renderer.cpp

HEADERS += \
    geogenerator.h \
    geometry.h \
    heatmapgradient.h \
    heatmaprenderer.h \
    map.h \
    renderer.h \
    spartialindex.h


DESTDIR = ../../bin


unix|win32: LIBS += -L$$OUT_PWD/../../bin/ -lnumbers

DEPENDPATH += $$PWD/../
INCLUDEPATH += $$PWD/../
#DEPENDPATH += $$PWD/../../numbers
