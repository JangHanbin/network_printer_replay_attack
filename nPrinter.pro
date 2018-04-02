TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lpcap
SOURCES += main.cpp \
    datamagician.cpp \
    jpcaplib.cpp \
    printdata.cpp

HEADERS += \
    datamagician.h \
    jpcaplib.h \
    printdata.h
