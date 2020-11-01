TEMPLATE = app
QT += gui

CONFIG += c++17


HEADERS += catch2.hpp \
  utils.h

SOURCES +=  catch2.cpp \
            graph/bytebuffer.cpp \
            graph/entity.cpp \
            graph/idmanager.cpp \
            graph/log.cpp \
            graph/store.cpp \
            utils.cpp

DESTDIR =../../bin

unix|win32: LIBS += -L$$OUT_PWD/../../bin/ -lgraph

INCLUDEPATH += $$PWD/../graph
DEPENDPATH += $$PWD/../graph
