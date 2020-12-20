QT += quick

CONFIG += c++11

SOURCES += \
        bridge.cpp \
        main.cpp \
        mapcanvas.cpp

HEADERS += \
  bridge.h \
  mapcanvas.h

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

DESTDIR =../../../bin

unix|win32: LIBS += -L$$OUT_PWD/../../../bin/ -lgraph
unix|win32: LIBS += -L$$OUT_PWD/../../../bin/ -lnumbers


INCLUDEPATH += $$PWD/../../
#DEPENDPATH += $$PWD/../graph

