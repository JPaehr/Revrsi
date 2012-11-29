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
    interfaces/win_gui.cpp \
    interfaces/server_gui.cpp \
    interfaces/new_game_settings.cpp \
    interfaces/hilfsding.cpp \
    interfaces/client_gui.cpp \
    interfaces/dialog.cpp

HEADERS  += revrsi.h \
    FieldItem.h \
    TokenItem.h \
    Logic.h \
    interfaces/win_gui.h \
    interfaces/server_gui.h \
    interfaces/new_game_settings.h \
    interfaces/hilfsding.h \
    interfaces/client_gui.h \
    interfaces/dialog.h

FORMS    += revrsi.ui \
    interfaces/win_gui.ui \
    interfaces/server_gui.ui \
    interfaces/new_game_settings.ui \
    interfaces/hilfsding.ui \
    interfaces/client_gui.ui \
    interfaces/dialog.ui

OTHER_FILES += \
    feld.png \
    token4.png \
    token3.png \
    token2.png \
    token1.png \
    feld2.png \
    crown.png

RESOURCES += \
    res/resources.qrc \
