# -------------------------------------------------
# Project created by QtCreator 2010-02-15T17:19:57
# -------------------------------------------------
QT += network
TARGET = MaeRemote
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    scroll.cpp \
    client.cpp \
    engine.cpp
HEADERS += mainwindow.h \
    scroll.h \
    client.h \
    engine.h \
    sensordata.h
FORMS += mainwindow.ui
