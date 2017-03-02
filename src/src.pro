include(../defaults.pri)

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += console
CONFIG -= app_bundle
CONFIG += c++14

TEMPLATE = lib

TARGET = optymalizacja

SOURCES += Dummy.cpp \
    mainwindow.cpp
HEADERS += Dummy.hpp \
    mainwindow.h

FORMS += \
    mainwindow.ui
