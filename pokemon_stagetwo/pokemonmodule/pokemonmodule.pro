#-------------------------------------------------
#
# Project created by QtCreator 2018-11-13T19:42:59
#
#-------------------------------------------------

QT       -= gui
QT      += network

TARGET = pokemonmodule
TEMPLATE = lib

DEFINES += POKEMONMODULE_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    highattack.cpp \
    ashe.cpp \
    pokemon.cpp \
    usr.cpp

HEADERS += \
        pokemonmodule_global.h \ 
    global.h \
    pokemon.h \
    ashe.h \
    highattack.h \
    pokemonsetting.h \
    usr.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}


