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

QMAKE_CXXFLAGS+= -fopenmp
QMAKE_LFLAGS += -fopenmp

SOURCES += main.cpp \
    artificial_intelligence.cpp \
    target_window.cpp \
    images.cpp

CONFIG += c++11

RESOURCES += \
    browser_resources.qrc

HEADERS += \
    artificial_intelligence.h \
    target_window.h \
    data_types.h \
    images.h

DISTFILES += \
    CodeTrash
