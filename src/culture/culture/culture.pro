QT -= qt

TEMPLATE = lib
DEFINES += CULTURE_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    culture.cpp \
    food/food.cpp \
    language.cpp \
    organisation/organisation.cpp

HEADERS += \
    culture_global.h \
    culture.h \
    food/food.h \
    language.h \
    organisation/organisation.h

DESTDIR = ../../bin

DISTFILES += \
  notes.txt

unix|win32: LIBS += -L$$OUT_PWD/../../bin/ -lgraph

INCLUDEPATH += $$PWD/../../graph
DEPENDPATH += $$PWD/../../graph
