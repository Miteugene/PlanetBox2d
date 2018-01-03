#-------------------------------------------------
#
# Project created by QtCreator 2017-12-26T11:37:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PlanetBox2d
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        widget.cpp \
    circle.cpp \
    groundrect.cpp \
    scene.cpp

HEADERS += \
        widget.h \
    Box2D/Box2D.h \
    circle.h \
    groundrect.h \
    scene.h \
    functions.h



FORMS += \
        widget.ui

unix:!macx|win32: LIBS += -L$$PWD/./ -lBox2D

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/./Box2D.lib
else:unix:!macx|win32-g++: PRE_TARGETDEPS += $$PWD/./libBox2D.a
