CONFIG -= qt


TEMPLATE = lib
DEFINES += GRAPH_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    class.cpp \
    cache/cache.cpp \
    cache/page.cpp \
    cache/cachemanager.cpp \
    config.cpp \
    entity.cpp \
    id/idscanner.cpp \
    inheritance.cpp \
    propdef.cpp \
    store/storemanager.cpp \
    tx/transactioncache.cpp \
    tx/transactionmanager.cpp \
    type/propertydef.cpp \
    wal/writeaheadlog.cpp \
    graph.cpp \
    id/idmanager.cpp \
    relation.cpp \
    store/store.cpp \
    store/file.cpp \
    storeable.cpp \
    transaction.cpp \
    type/base.cpp \
    type/registry.cpp \
    type/buffer.cpp \
    query/parser.cpp

HEADERS += \
    class.h \
    global.h \
    cache/cache.h \
    cache/page.h \
    cache/cachemanager.h \
    config.h \
    entity.h \
    graph.h \
    id/idmanager.h \
    id/idscanner.h \
    inheritance.h \
    propdef.h \
    relation.h \
    store/scanner.h \
    store/store.h \
    store/file.h \
    store/storemanager.h \
    storeable.h \
    transaction.h \
    tx/transactioncache.h \
    tx/transactionmanager.h \
    type/base.h \
    type/factory.h \
    type/propertydef.h \
    type/registry.h \
    type/buffer.h \
    type/errors.h \
    query/parser.h \
    wal/writeaheadlog.h


DESTDIR = ../../../bin
INCLUDEPATH += $$PWD/

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
