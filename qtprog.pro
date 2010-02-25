TARGET      = MaeRemote
HEADERS += mousewindow.h \
    scroll.h \
    client.h \
    engine.h \
    sensordata.h \
    serverdata.h \
    connectionwindow.h
SOURCES += main.cpp \
    mousewindow.cpp \
    scroll.cpp \
    client.cpp \
    engine.cpp \
    serverdata.cpp \
    connectionwindow.cpp
FORMS += mousewindow.ui \
    connectionwindow.ui
QT += network
LEXSOURCES  += #LEXS#
YACCSOURCES += #YACCS#

INCLUDEPATH +=
LIBS        +=
DEFINES     +=

# All generated files goes same directory
OBJECTS_DIR = build
MOC_DIR     = build
UI_DIR      = build

DESTDIR     = build
TEMPLATE    = app
DEPENDPATH  +=
VPATH       += src/gui uis
CONFIG      += debug
QT=core gui network

INSTALLS    += target
target.path  = /opt/maeremote/bin

INSTALLS    += desktop
desktop.path  = /usr/share/applications/hildon
desktop.files  = data/maeremote.desktop

INSTALLS    += service
service.path  = /usr/share/dbus-1/services
service.files  = data/maeremote.service

INSTALLS    += icon64
icon64.path  = /usr/share/icons/hicolor/64x64/apps
icon64.files  = data/64x64/maeremote.png

#
# Targets for debian source and binary package creation
#
debian-src.commands = dpkg-buildpackage -S -r -us -uc -d
debian-bin.commands = dpkg-buildpackage -b -r -uc -d
debian-all.depends = debian-src debian-bin

#
# Clean all but Makefile
#
compiler_clean.commands = -$(DEL_FILE) $(TARGET)

QMAKE_EXTRA_TARGETS += debian-all debian-src debian-bin compiler_clean
