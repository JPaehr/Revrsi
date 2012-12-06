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
    interfaces/client_gui.cpp \
    player.cpp \
    animation/anim_test.cpp \
    net/server/server_thread.cpp \
    net/server/server.cpp \
    net/socket.cpp \
    net/client/client.cpp \
    net/server/superserver.cpp \
    net/client/client_thread.cpp

HEADERS  += revrsi.h \
    FieldItem.h \
    TokenItem.h \
    Logic.h \
    interfaces/win_gui.h \
    interfaces/server_gui.h \
    interfaces/new_game_settings.h \
    interfaces/client_gui.h \
    player.h \
    animation/anim_test.h \
    net/server/server_thread.h \
    net/server/server.h \
    net/socket.h \
    net/client/client.h \
    net/server/superserver.h \
    net/server/server_thread.h \
    net/client/client_thread.h

FORMS    += revrsi.ui \
    interfaces/win_gui.ui \
    interfaces/server_gui.ui \
    interfaces/new_game_settings.ui \
    interfaces/client_gui.ui

RESOURCES += \
    res/resources.qrc \
