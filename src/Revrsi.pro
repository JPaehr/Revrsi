#-------------------------------------------------
#
# Project created by QtCreator 2012-11-08T10:58:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Revrsi
TEMPLATE = app


SOURCES += main.cpp\
        revrsi.cpp \
    FieldItem.cpp \
    TokenItem.cpp \
    Logic.cpp \
    new_game_settings.cpp

HEADERS  += revrsi.h \
    FieldItem.h \
    TokenItem.h \
    Logic.h \
    new_game_settings.h

FORMS    += revrsi.ui \
    new_game_settings.ui

OTHER_FILES += \
    feld.png \
    token4.png \
    token3.png \
    token2.png \
    token1.png \
    feld2.png
