include(../defaults.pri)

CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

TEMPLATE = app

SOURCES += main.cpp \
           DummyTestSuite.cpp

LIBS += -lgtest -L../src -loptymalizacja -lpthread
