#-------------------------------------------------
#
# Project created by QtCreator 2016-10-10T21:50:21
#
#-------------------------------------------------

QT       += core gui webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AI
TEMPLATE = app

LIBS += -lcairo -lX11

SOURCES += main.cpp \
    artificial_intelligence.cpp \
    target_window.cpp

CONFIG += c++11

RESOURCES += \
    browser_resources.qrc

HEADERS += \
    artificial_intelligence.h \
    target_window.h

DISTFILES += \
    CodeTrash
