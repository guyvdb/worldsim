TEMPLATE = app
QT += gui

CONFIG += c++17


HEADERS += catch2.hpp \
  utils.h

SOURCES +=  catch2.cpp \
            graph/bytebuffer.cpp \
            graph/idstore.cpp \
            graph/log.cpp \
            graph/thing.cpp \
            utils.cpp

DESTDIR =../../bin

unix|win32: LIBS += -L$$OUT_PWD/../../bin/ -lgraph

INCLUDEPATH += $$PWD/../graph
DEPENDPATH += $$PWD/../graph
