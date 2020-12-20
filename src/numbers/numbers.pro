CONFIG -= qt
TEMPLATE = lib
CONFIG += c++17
SOURCES += \
  bounds.cpp \
  line.cpp \
  point.cpp \
  random.cpp \
  rect.cpp \
  simplexnoise.cpp \
  triangle.cpp

HEADERS += \
    bounds.h \
    delaunator.h \
    line.h \
    point.h \
    poisson.h \
    random.h \
    rect.h \
    simplexnoise.h \
    triangle.h


DESTDIR = ../../bin

