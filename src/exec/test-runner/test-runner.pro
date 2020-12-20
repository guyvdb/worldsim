TEMPLATE = app
QT += gui
CONFIG += c++17


HEADERS += catch2.hpp \
  utils.h

SOURCES +=  catch2.cpp \
            graph/bytebuffer.cpp \
            graph/cache.cpp \
            graph/entity.cpp \
            graph/file.cpp \
            graph/graph.cpp \
            graph/idmanager.cpp \
            graph/log.cpp \
            graph/store.cpp \
            graph/storemanager.cpp \
            graph/transactionlog.cpp \
            utils.cpp

DESTDIR =../../../bin

INCLUDEPATH += $$PWD/../../


unix|win32: LIBS += -L$$OUT_PWD/../../../bin/ -lgraph


