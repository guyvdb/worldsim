QT -= qt
TEMPLATE = lib
CONFIG += c++17

SOURCES += \
    culture.cpp \
    food/food.cpp \
    language.cpp \
    organisation/organisation.cpp

HEADERS += \
    culture.h \
    food/food.h \
    language.h \
    organisation/organisation.h


DISTFILES += \
  notes.txt

DESTDIR = ../../bin

unix|win32: LIBS += -L$$OUT_PWD/../../bin/ -lgraph

INCLUDEPATH += $$PWD/../
#DEPENDPATH += $$PWD/../../
