#-------------------------------------------------
#
# Project created by QtCreator 2013-07-17T10:49:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG(debug, debug|release) {
    TARGET = zTextMated
} else {
    TARGET = zTextMate
}

TEMPLATE = app

SOURCES += \
    ../src/main.cpp\
    ../src/mainwindow.cpp

INCLUDEPATH += \
    ../include

HEADERS  += \
    ../include/mainwindow.h

FORMS    += \
    ../ui/mainwindow.ui

DESTDIR     = ../tmp/$$TARGET
OBJECTS_DIR = ../tmp/$$TARGET/obj
MOC_DIR     = ../tmp/$$TARGET/moc
UI_DIR      = ../tmp/$$TARGET/ui

DEPENDPATH *= $${INCLUDEPATH}
