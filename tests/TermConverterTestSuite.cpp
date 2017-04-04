#include "TermConverter.hpp"
#include <gmock/gmock.h>

class TermConverterTestSuite : public testing::Test
{
public:
    TermConverterTestSuite() {}
    TermConverter sut;
};

TEST_F(TermConverterTestSuite, shouldReturnZeroZeroPairWhenReceiveEmptyString)
{
    auto result = sut.convert("");
    ASSERT_EQ(result, std::make_pair(0, 0));
}

TEST_F(TermConverterTestSuite, shouldReturnZeroZeroPairWhenReceiveEmptyStringwithSpaces)
{
    auto result = sut.convert("   ");
    ASSERT_EQ(result, std::make_pair(0, 0));
}

TEST_F(TermConverterTestSuite, shouldReturnOneZeroPairWhenReceive1String)
{
    auto result = sut.convert("1");
    ASSERT_EQ(result, std::make_pair(1, 0));
}

TEST_F(TermConverterTestSuite, shouldReturnOneZeroPairWhenReceive1StringWithSpace)
{
    auto result = sut.convert(" 1");
    ASSERT_EQ(result, std::make_pair(1, 0));
}

TEST_F(TermConverterTestSuite, shouldReturnOneOnePairWhenReceiveX1StringWithSpace)
{
    auto result = sut.convert(" x1");
    ASSERT_EQ(result, std::make_pair(1, 1));
}

TEST_F(TermConverterTestSuite, shouldReturnThreeTwoPairWhenReceive3X2String)
{
    auto result = sut.convert(" 3x2");
    ASSERT_EQ(result, std::make_pair(3, 2));
}

TEST_F(TermConverterTestSuite, shouldReturnMinusThreeTenPairWhenReceiveMinus3x10String)
{
    auto result = sut.convert(" -3x10");
    ASSERT_EQ(result, std::make_pair(-3, 10));
}

TEST_F(TermConverterTestSuite, shouldReturnMinusFiftyThreeTenPairWhenReceiveMinus53x10String)
{
    auto result = sut.convert(" -53x10 ");
    ASSERT_EQ(result, std::make_pair(-53, 10));
}
