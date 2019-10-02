#-------------------------------------------------
#
# Project created by QtCreator 2017-01-10T17:45:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GENESI_scarabeo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    playersnumber_dialog.cpp \
    legenda.cpp \
    tabellone.cpp \
    dict.cpp \
    trie.cpp \
    mazzo.cpp \
    giocatore.cpp \
    custombutton_carta.cpp \
    custombutton_casella.cpp \
    partita.cpp \
    jolly_dialog.cpp

HEADERS  += mainwindow.h \
    playersnumber_dialog.h \
    legenda.h \
    tabellone.h \
    dict.h \
    trie.h \
    mazzo.h \
    giocatore.h \
    custombutton_carta.h \
    custombutton_casella.h \
    partita.h \
    jolly_dialog.h

FORMS    += mainwindow.ui \
    playersnumber_dialog.ui \
    jolly_dialog.ui

RESOURCES += \
    dictionary.qrc \
    images.qrc
