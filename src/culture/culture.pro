QT -= gui

TEMPLATE = lib
DEFINES += CULTURE_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    culture.cpp \
    language.cpp

HEADERS += \
    culture_global.h \
    culture.h \
    language.h

DESTDIR = ../../bin

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
  notes.txt

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../bin/ -lgraph
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../bin/ -lgraph
else:unix: LIBS += -L$$OUT_PWD/../../bin/ -lgraph

INCLUDEPATH += $$PWD/../graph/graph
DEPENDPATH += $$PWD/../graph
