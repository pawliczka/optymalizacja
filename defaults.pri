INCLUDEPATH += $$PWD/src
INCLUDEPATH += $$PWD/tests/mocks/
INCLUDEPATH += /usr/local/include
SRC_DIR = $$PWD
CONFIG += thread

QMAKE_CXXFLAGS += -std=c++14 -Wall -Wextra -pedantic
