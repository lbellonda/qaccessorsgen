#-------------------------------------------------
#
# Project created by QtCreator 2011-10-30T19:01:40
#
#-------------------------------------------------

QT       += core

QT       -= gui

#LIBS += -L../qaccessorsgenlib/libqaccessorgenlib
unix:LIBS += -lqaccessorsgenlib
#unix:LIBS += -l /home/lbell/devel/qaccessorsgen/build/qaccessorsgenlib/qaccessorgenlib
unix:LIBS += -L../qaccessorsgenlib
win32:LIBS += libqaccessorgenlib.lib

INCLUDEPATH += ../qaccessorsgenlib

TARGET = qaccessorsgen
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp
