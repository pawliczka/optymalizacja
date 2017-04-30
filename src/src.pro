include(../defaults.pri)

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += console
CONFIG -= app_bundle
CONFIG += c++14

TEMPLATE = lib

TARGET = optymalizacja

SOURCES += \
    mainwindow.cpp \
    EquationConventer.cpp \
    TermConverter.cpp \
    Equation.cpp \
    EquationManager.cpp \
    Controler.cpp \
    simplex.cpp \
    simplex_table.cpp \
    linprog.cpp

HEADERS += \
    mainwindow.h \
    EquationConventer.hpp \
    IEquationConventer.hpp \
    ITermConverter.hpp \
    TermConverter.hpp \
    Equation.hpp \
    ComparisonOperator.hpp \
    EquationManager.hpp \
    Controler.hpp \
    IEquationManager.hpp \
    simplex.hpp \
    simplex_table.hpp \
    linprog.hpp

FORMS += \
    mainwindow.ui

RESOURCES += \
    ../res/res.qrc
