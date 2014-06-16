#-------------------------------------------------
#
# Project created by QtCreator 2014-06-14T13:24:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Configurator_Ibeacon
TEMPLATE = app


SOURCES += main.cpp\
        configurator.cpp \
    generator_logic.cpp \
    generator_thread.cpp

HEADERS  += configurator.h \
    generator_logic.h \
    generator_thread.h

FORMS    += configurator.ui
