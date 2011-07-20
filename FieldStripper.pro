# -------------------------------------------------
# Project created by QtCreator 2009-11-11T18:05:16
# -------------------------------------------------
QT       += core gui
QMAKE_CXXFLAGS += -std=c++0x

TARGET = FieldStripper
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    PreviewHighlighter.cc \
    SearchFields.cc \
    FieldStripper.cc
OTHER_FILES += dada.txt

HEADERS += \
    mainwindow.h \
    PreviewHighlighter.h \
    SearchFields.h \
    FieldStripper.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    resources.qrc

RC_FILE = app.rc
