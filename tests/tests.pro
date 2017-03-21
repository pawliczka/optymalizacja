include(../defaults.pri)

CONFIG += console
CONFIG -= app_bundle
CONFIG += c++14

TEMPLATE = app

SOURCES += main.cpp \
           DummyTestSuite.cpp

LIBS += -lgmock -L../src -loptymalizacja -lpthread
