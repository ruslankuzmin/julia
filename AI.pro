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

QMAKE_CXXFLAGS+= -fopenmp `pkg-config --cflags openal`
QMAKE_LFLAGS += -fopenmp `pkg-config --libs openal`

SOURCES += main.cpp \
    artificial_intelligence.cpp \
    target_window.cpp \
    images.cpp \
    worker.cpp \
    neural_networks/convolutional_nn.cpp \
    target_sound.cpp

CONFIG += c++11

RESOURCES += \
    browser_resources.qrc

HEADERS += \
    artificial_intelligence.h \
    target_window.h \
    data_types.h \
    images.h \
    worker.h \
    neural_networks/convolutional_nn.h \
    target_sound.h

DISTFILES += \
    CodeTrash \
    TODO \
    README.md
