TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    token.cpp \
    att.cpp \
    txttoken.cpp \
    xyz.cpp

HEADERS += \
    token.h \
    att.h \
    txttoken.h \
    xyz.h

DISTFILES += \
    quelle.txt \
    mediathek.xml
