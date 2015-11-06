#-------------------------------------------------
#
# Project created by QtCreator 2015-10-20T10:10:39
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets serialport network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BUS_PIS
TEMPLATE = app


SOURCES += main.cpp\
        busmain.cpp \
    camera.cpp \
    home.cpp \
    keyboard.cpp \
    player.cpp \
    prerecorded.cpp \
    reversecamera.cpp \
    route_selection.cpp \
    running_route.cpp \
    hid.cpp \
    mythread.cpp \
    ffmpegtask.cpp \
    struct.cpp \
    videowidget.cpp

HEADERS  += busmain.h \
    camera.h \
    home.h \
    keyboard.h \
    player.h \
    prerecorded.h \
    reversecamera.h \
    route_selection.h \
    running_route.h \
    hidapi.h \
    mythread.h \
    ffmpegtask.h \
    struct.h \
    videowidget.h \
    splashscreen.h

FORMS    += busmain.ui \
    camera.ui \
    home.ui \
    keyboard.ui \
    player.ui \
    prerecorded.ui \
    reversecamera.ui \
    route_selection.ui \
    running_route.ui

RESOURCES += \
    images.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib/x86_64-linux-gnu/release/ -ludev
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib/x86_64-linux-gnu/debug/ -ludev
else:unix: LIBS += -L$$PWD/../../lib/x86_64-linux-gnu/ -ludev

INCLUDEPATH += $$PWD/../../lib/x86_64-linux-gnu
DEPENDPATH += $$PWD/../../lib/x86_64-linux-gnu
