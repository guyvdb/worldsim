CONFIG -= qt
TEMPLATE = lib
CONFIG += c++17
SOURCES += \
  bounds.cpp \
  line.cpp \
  random.cpp \
  rect.cpp \
  simplexnoise.cpp \
  triangle.cpp \
  vector.cpp

HEADERS += \
    bounds.h \
    delaunator.h \
    line.h \
    poisson.h \
    random.h \
    rect.h \
    simplexnoise.h \
    triangle.h \
    vector.h


DESTDIR = ../../bin

