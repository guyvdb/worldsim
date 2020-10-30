#CONFIG -= qt

TEMPLATE = lib
DEFINES += GRAPH_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bytebuffer.cpp \
    cache.cpp \
    cachemanager.cpp \
    cachepage.cpp \
    config.cpp \
    entity.cpp \
    entitytype.cpp \
    graph.cpp \
    idmanager.cpp \
    log.cpp \
    properties.cpp \
    relation.cpp \
    relationtype.cpp \
    schema.cpp \
    store.cpp \
    storeable.cpp \
    storemanager.cpp \
    transactionmanager.cpp \
    tx.cpp

HEADERS += \
    bytebuffer.h \
    cache.h \
    cachemanager.h \
    cachepage.h \
    config.h \
    entity.h \
    entitytype.h \
    gerror.h \
    gid.h \
    graph_global.h \
    graph.h \
    idmanager.h \
    log.h \
    properties.h \
    relation.h \
    relationtype.h \
    schema.h \
    store.h \
    storeable.h \
    storemanager.h \
    transactionmanager.h \
    tx.h \
    types.h


DESTDIR = ../../bin

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
