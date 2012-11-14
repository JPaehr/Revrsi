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
    Logic.cpp

HEADERS  += revrsi.h \
    FieldItem.h \
    TokenItem.h

FORMS    += revrsi.ui

OTHER_FILES += \
    feld.png
