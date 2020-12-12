CONFIG -= qt

TEMPLATE = lib
DEFINES += GRAPH_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    attribute.cpp \
    buffer.cpp \
    cache/cache.cpp \
    cache/cachemanager.cpp \
    config.cpp \
    decoder.cpp \
    entity.cpp \     \
    wal/writeaheadlog.cpp
    graph.cpp \
    idmanager.cpp \
    log.cpp \
    page.cpp \
    relation.cpp \
    store/store.cpp \
    store/storemanager.cpp \
    store/file.cpp \
    storeable.cpp \
    tx/transaction.cpp \
    tx/transactioncache.cpp \
    tx/transactionmanager.cpp \
    type/base.cpp \
    type/heirachy.cpp \
    type/propertydef.cpp \
    type/registry.cpp \
    type/type.cpp \
    query/parser.cpp

HEADERS += \
    attribute.h \
    buffer.h \
    cache/cache.h \
    cache/cachemanager.h \
    config.h \
    decoder.h \
    entity.h \
    graph_global.h \
    graph.h \
    grapherrors.h \
    idmanager.h \
    log.h \
    page.h \
    relation.h \
    store/scanner.h \
    store/store.h \
    store/storemanager.h \
    store/file.h \
    storeable.h \
    tx/transaction.h \
    tx/transactioncache.h \
    tx/transactionmanager.h \
    type/base.h \
    type/heirachy.h \
    type/propertydef.h \
    type/registry.h \
    type/type.h \
    query/parser.h \
    wal/writeaheadlog.h


DESTDIR = ../../bin

INCLUDEPATH += $$PWD/graph

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
