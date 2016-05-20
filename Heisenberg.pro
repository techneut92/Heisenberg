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
<<<<<<< HEAD
    hbserialbluetooth.cpp \
    spider.cpp \
    hbtcpserver.cpp

HEADERS += \
    hbwebserver.h \
    hbserialbluetooth.h \
    heisenberg.conf \
    spider.h \
    hbtcpserver.h
=======
    hbserialbluetooth.cpp

HEADERS += \
    hbwebserver.h \
    hbserialbluetooth.h
>>>>>>> 13af8eacecb29363582dbb4cb81cb96ea086df08

