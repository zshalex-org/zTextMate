#-------------------------------------------------
#
# Project created by QtCreator 2013-07-17T11:34:43
#
#-------------------------------------------------

QT       += widgets xml testlib

CONFIG(debug, debug|release) {
    TARGET = testd
} else {
    TARGET = test
}

CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    ../src/test/testmain.cpp \

INCLUDEPATH += \
    ../include \
    ../include/qtest-plus

LIBS += ../lib/libqtest-plus.dylib

include(../pro/zTextMate.pri)
include(test.pri)

DESTDIR     = ../tmp/$$TARGET
OBJECTS_DIR = ../tmp/$$TARGET/obj
MOC_DIR     = ../tmp/$$TARGET/moc
UI_DIR      = ../tmp/$$TARGET/ui

DEPENDPATH *= $${INCLUDEPATH}
