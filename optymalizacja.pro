INCLUDEPATH += $$PWD\src
INCLUDEPATH += C:\boost

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += thread
CONFIG -= console
CONFIG -= app_bundle
#CONFIG += c++11
CONFIG += static
QMAKE_LFLAGS += -static-libgcc -static-libstdc++

QMAKE_CXXFLAGS += -std=c++14

#QMAKE_LFLAGS += -static -static-libgcc
#QMAKE_CFLAGS_RELEASE -= -O2
#QMAKE_CFLAGS_RELEASE += -Os -momit-leaf-frame-pointer
#DEFINES += QT_STATIC_BUILD

TARGET = optymalizacja

SOURCES += \
    src\main.cpp \
    src\MainWindow.cpp \
    src\EquationConventer.cpp \
    src\TermConverter.cpp \
    src\Equation.cpp \
    src\EquationManager.cpp \
    src\Controler.cpp \
    src\Simplex.cpp \
    src\SimplexTable.cpp \
    src\LinearProblem.cpp \
    src\LinearProblemSolution.cpp \
    src\BranchAndBoundTreeDisplayer.cpp \
    src\BranchAndBoundSolver.cpp \
    src\NodeOfSolution.cpp

HEADERS += \
    src\MainWindow.hpp \
    src\EquationConventer.hpp \
    src\IEquationConventer.hpp \
    src\ITermConverter.hpp \
    src\TermConverter.hpp \
    src\Equation.hpp \
    src\ComparisonOperator.hpp \
    src\EquationManager.hpp \
    src\Controler.hpp \
    src\IEquationManager.hpp \
    src\SimplexTable.hpp \
    src\Simplex.hpp \
    src\LinearProblemCase.hpp \
    src\LinearProblem.hpp \
    src\SimplexStatus.hpp \
    src\LinearProblemSolution.hpp \
    src\BranchAndBoundTreeDisplayer.hpp \
    src\BranchAndBoundSolver.hpp \
    src\NodeOfSolution.hpp

FORMS += \
    src\mainwindow.ui \
    src\branchandboundtreedisplayer.ui

RESOURCES += \
    res\res.qrc

win32:RC_ICONS += res\calculator.ico
