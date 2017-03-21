#include "Dummy.hpp"
#include <gmock/gmock.h>

class DummyTestSuite : public testing::Test {
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
