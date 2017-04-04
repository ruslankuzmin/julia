#-------------------------------------------------
#
# Project created by QtCreator 2016-10-10T21:50:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webenginewidgets

TARGET = AI
TEMPLATE = app

SOURCES += main.cpp \
    artificial_intelligence.cpp

#Добавление возможностей стандарта C++ 11
CONFIG += c++11

RESOURCES += \
    browser_resources.qrc

HEADERS += \
    artificial_intelligence.h
