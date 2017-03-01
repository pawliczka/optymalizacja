#include "Dummy.hpp"
#include <gtest/gtest.h>

using namespace testing;

class DummyTestSuite : public Test {
public:
    Dummy sut;
};

TEST_F(DummyTestSuite, shouldReturn5AfterInicjalization)
{
    ASSERT_EQ(sut.getP(), 5);
}

TEST_F(DummyTestSuite, shouldReturn5AfterInicjalizationFail)
{
    ASSERT_EQ(sut.getP(), 3);
}
