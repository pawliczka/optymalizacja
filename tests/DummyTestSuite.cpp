#include <gtest/gtest.h>
#include "Dummy.hpp"

using namespace testing;

class DummyTestSuite : public Test
{
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
