include(../defaults.pri)

CONFIG += console
CONFIG -= app_bundle
CONFIG += c++14

TEMPLATE = app

SOURCES += main.cpp \
    EquationConventerTestSuite.cpp \
    TermConverterTestSuite.cpp \
    EquationTestSuite.cpp \
    EquationManagerTestSuite.cpp \
    SimplexTestSuite.cpp

HEADERS += \
    mocks/EquationConventerMock.hpp \
    mocks/TermConverterMock.hpp \
    mocks/EquationManagerMock.hpp

LIBS += -lgmock -L../src -loptymalizacja -lpthread
