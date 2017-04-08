include(../defaults.pri)

CONFIG += console
CONFIG -= app_bundle
CONFIG += c++14

TEMPLATE = app

SOURCES += main.cpp \
    EquationConventerTestSuite.cpp \
    TermConverterTestSuite.cpp \
    EquationTestSuite.cpp

HEADERS += \
    mocks/EquationConventerMock.hpp \
    mocks/TermConverterMock.hpp \
    mocks/EquationMock.hpp

LIBS += -lgmock -L../src -loptymalizacja -lpthread
