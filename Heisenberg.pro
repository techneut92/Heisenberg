QT += core
QT += network
QT += websockets
QT += serialport
QT += concurrent
QT -= gui

TARGET = Heisenberg
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    hbwebserver.cpp \
    hbserialbluetooth.cpp \
    spider.cpp \
    hbtcpserver.cpp \
    hbtcpsocket.cpp \
    controller.cpp \
    hbcommandcenter.cpp

HEADERS += \
    hbwebserver.h \
    hbserialbluetooth.h \
    heisenberg.conf \
    spider.h \
    hbtcpsocket.h \
    hbtcpserver.h \
    controller.h \
    hbcommandcenter.h

