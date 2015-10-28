#-------------------------------------------------
#
# Project created by QtCreator 2015-10-28T10:55:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = emit_signals
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    reciever.cpp

HEADERS  += mainwindow.h \
    reciever.h

FORMS    += mainwindow.ui \
    reciever.ui
