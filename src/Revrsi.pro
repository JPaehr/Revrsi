#-------------------------------------------------
#
# Project created by QtCreator 2012-11-08T10:58:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Revrsi
TEMPLATE = app

CONFIG += console

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
    net/client/client_thread.cpp \
    net/server/subServer.cpp \
    AI/ai_thread.cpp \
    interfaces/ai_settings.cpp \
    AI/ai_code.cpp \
    AI/ki_logic.cpp

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
    net/server/server_thread.h \
    net/client/client_thread.h \
    net/server/subServer.h \
    AI/ai_thread.h \
    interfaces/ai_settings.h \
    AI/ai_code.h \
    AI/ki_logic.h

FORMS    += revrsi.ui \
    interfaces/win_gui.ui \
    interfaces/server_gui.ui \
    interfaces/new_game_settings.ui \
    interfaces/client_gui.ui \
    interfaces/ai_settings.ui

RESOURCES += \
    res/resources.qrc \
