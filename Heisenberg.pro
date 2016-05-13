QT += core
QT += network
QT += websockets
QT += serialport
QT -= gui

TARGET = Heisenberg
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    hbwebserver.cpp \
    hbserialbluetooth.cpp

HEADERS += \
    hbwebserver.h \
    hbserialbluetooth.h

