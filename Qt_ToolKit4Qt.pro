QT += core
QT -= gui

CONFIG += c++11

TARGET = Qt_ToolKit4Qt
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

HEADERS += \
    JsonTool/jsontool.h \
    JsonTool/baseobject.h \
    JsonTool/singleobject.h \
    TestScript/jsontooltest.h
