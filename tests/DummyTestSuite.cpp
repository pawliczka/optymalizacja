#include "Dummy.hpp"
#include <gtest/gtest.h>

using namespace testing;

class DummyTestSuite : public Test {
public:
    Dummy sut;
};

TEST_F(DummyTestSuite, shouldReturnFiveAfterInitialization)
{
    ASSERT_EQ(sut.getP(), 5);
}

TEST_F(DummyTestSuite, shouldReturnFiveAfterInitializationFail)
{
    ASSERT_EQ(sut.getP(), 3);
}
