#-------------------------------------------------
#
# Project created by QtCreator 2015-09-10T16:09:24
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 10_sep_layouts
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    camera.cpp \
    phone.cpp \
    bus.cpp \
    video.cpp \
    videowidget.cpp

HEADERS  += mainwindow.h \
    camera.h \
    phone.h \
    bus.h \
    video.h \
    videowidget.h

FORMS    += mainwindow.ui \
    camera.ui \
    phone.ui \
    bus.ui \
    video.ui \
    videowidget.ui
