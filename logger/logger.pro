#-------------------------------------------------
#
# Project created by QtCreator 2017-11-13T15:28:07
#
#-------------------------------------------------
include(../logger_global.pri)

QT       -= gui

TARGET = $$PLATFORM_LOGGER_LIB_NAME
TEMPLATE = lib
CONFIG += staticlib c++11 debug_and_release build_all

DESTDIR = $$PLATFORM_LOGGER_LIB_DIR
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += moonlogger.h \
    loggingfile.h \
    loggingconfiguration.h \
    loggermanager.h \
    loggingpolicy.h \
    loggingpolicyimpl.h \
    loggingdefine.h

SOURCES += $$PWD/moonlogger.cpp \
    loggingfile.cpp \
    loggermanager.cpp \
    loggingpolicyimpl.cpp \
    loggingpolicy.cpp

