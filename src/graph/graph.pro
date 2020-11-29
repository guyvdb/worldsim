CONFIG -= qt

TEMPLATE = lib
DEFINES += GRAPH_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    graph/attribute.cpp \
    graph/buffer.cpp \
    graph/cache.cpp \
    graph/cachemanager.cpp \
    graph/cachepage.cpp \
    graph/config.cpp \
    graph/encoder.cpp \
    graph/entity.cpp \
    graph/entityencoder.cpp \
    graph/file.cpp \
    graph/graph.cpp \
    graph/idmanager.cpp \
    graph/log.cpp \
    graph/properties.cpp \
    graph/relation.cpp \
    graph/relationencoder.cpp \
    graph/schema.cpp \
    graph/store.cpp \
    graph/storeable.cpp \
    graph/storemanager.cpp \
    graph/transaction.cpp \
    graph/transactionlog.cpp \
    graph/transactionmanager.cpp \
    graph/type.cpp

HEADERS += \
    graph/attribute.h \
    graph/buffer.h \
    graph/cache.h \
    graph/cachemanager.h \
    graph/cachepage.h \
    graph/config.h \
    graph/encoder.h \
    graph/entity.h \
    graph/entityencoder.h \
    graph/file.h \
    graph/graph_global.h \
    graph/graph.h \
    graph/idaccumulator.h \
    graph/idmanager.h \
    graph/log.h \
    graph/properties.h \
    graph/relation.h \
    graph/relationencoder.h \
    graph/schema.h \
    graph/store.h \
    graph/storeable.h \
    graph/storemanager.h \
    graph/transaction.h \
    graph/transactionlog.h \
    graph/transactionmanager.h \
    graph/type.h \
    graph/types.h


DESTDIR = ../../bin

INCLUDEPATH += $$PWD/graph

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
