TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lpcap
LIBS += -ltins
LIBS += -lpthread
LIBS += -lglog

SOURCES += main.cpp \
    datamagician.cpp \
    jpcaplib.cpp \
    printdata.cpp \
    hostdetector.cpp \
    spoofer.cpp

HEADERS += \
    datamagician.h \
    jpcaplib.h \
    printdata.h \
    hostdetector.h \
    spoofer.h
