#-------------------------------------------------
#
# Project created by QtCreator 2011-10-30T19:03:20
#
#-------------------------------------------------

QT       -= gui

TARGET = qaccessorsgenlib
TEMPLATE = lib
CONFIG += staticlib

#DEFINES += QACCESSORSGENLIB_LIBRARY
DEFINES += QACCESSORSGENLIB_STATICLIBRARY

SOURCES += qaccessorsgenerator.cpp \
    qaccessorsgeneratorspropertyinfo.cpp \
    qaccessorsgeneratorsinputparameters.cpp \
    qaccessorsgeneratorsoutput.cpp \
    qaccessorsgeneratorsresult.cpp \
    workinginfo.cpp

HEADERS += qaccessorsgenerator.h\
        qaccessorsgenlib_global.h \
    qaccessorsgeneratorspropertyinfo.h \
    qaccessorsgeneratorsinputparameters.h \
    qaccessorsgeneratorsoutput.h \
    qaccessorsgeneratorsresult.h \
    workinginfo.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}












