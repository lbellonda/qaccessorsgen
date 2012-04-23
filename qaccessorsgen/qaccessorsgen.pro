#-------------------------------------------------
#
# Project created by QtCreator 2011-10-30T19:01:40
#
#-------------------------------------------------

QT       += core

QT       -= gui


unix:LIBS += -lqaccessorsgenlib
unix:LIBS += -L../qaccessorsgenlib
win32:LIBS += libqaccessorgenlib.lib

INCLUDEPATH += ../qaccessorsgenlib

TARGET = qaccessorsgen
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp
