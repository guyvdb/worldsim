#CONFIG -= qt

TEMPLATE = lib
DEFINES += GRAPH_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    attribute.cpp \
    buffer.cpp \
    cache.cpp \
    cachemanager.cpp \
    cachepage.cpp \
    config.cpp \
    encoder.cpp \
    entity.cpp \
    entityencoder.cpp \
    file.cpp \
    graph.cpp \
    idmanager.cpp \
    log.cpp \
    properties.cpp \
    relation.cpp \
    relationencoder.cpp \
    schema.cpp \
    store.cpp \
    storeable.cpp \
    storemanager.cpp \
    transaction.cpp \
    transactionlog.cpp \
    transactionmanager.cpp \
    type.cpp

HEADERS += \
    attribute.h \
    buffer.h \
    cache.h \
    cachemanager.h \
    cachepage.h \
    config.h \
    encoder.h \
    entity.h \
    entityencoder.h \
    file.h \
    graph_global.h \
    graph.h \
    idaccumulator.h \
    idmanager.h \
    log.h \
    properties.h \
    relation.h \
    relationencoder.h \
    schema.h \
    store.h \
    storeable.h \
    storemanager.h \
    transaction.h \
    transactionlog.h \
    transactionmanager.h \
    type.h \
    types.h


DESTDIR = ../../bin

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
