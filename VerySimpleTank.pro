#-------------------------------------------------
#
# Project created by QtCreator 2015-01-20T18:13:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VerySimpleTank
TEMPLATE = app

INCLUDEPATH += "C:/Assimp-3.1.1/include"
LIBS += "C:/Assimp-3.1.1/libs/libassimp.dll"

QMAKE_LFLAGS += -static -static-libgcc


SOURCES += main.cpp\
        Dialog.cpp \
    Scene.cpp \
    MeshLoader.cpp \
    Tank.cpp

HEADERS  += Dialog.h \
    Scene.h \
    MeshLoader.h \
    Tank.h

FORMS    += Dialog.ui

RESOURCES += \
    Shaders.qrc
