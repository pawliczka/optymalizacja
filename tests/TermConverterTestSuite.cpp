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
    ASSERT_EQ(result, std::make_pair(float(0.0), 0));
}

TEST_F(TermConverterTestSuite, shouldReturnMinusOneZeroPairWhenReceiveMinusOne)
{
    auto result = sut.convert("-1");
    ASSERT_EQ(result, std::make_pair(float(-1), 0));
}

TEST_F(TermConverterTestSuite, shouldReturnMinusSevenZeroPairWhenReceiveMinusSeven)
{
    auto result = sut.convert("-7");
    ASSERT_EQ(result, std::make_pair(float(-7), 0));
}

TEST_F(TermConverterTestSuite, shouldReturnZeroZeroPairWhenReceiveEmptyStringwithSpaces)
{
    auto result = sut.convert("   ");
    ASSERT_EQ(result, std::make_pair(float(0), 0));
}

TEST_F(TermConverterTestSuite, shouldReturnOneZeroPairWhenReceive1String)
{
    auto result = sut.convert("1");
    ASSERT_EQ(result, std::make_pair(float(1), 0));
}

TEST_F(TermConverterTestSuite, shouldReturnOneZeroPairWhenReceive1StringWithSpace)
{
    auto result = sut.convert(" 1");
    ASSERT_EQ(result, std::make_pair(float(1), 0));
}

TEST_F(TermConverterTestSuite, shouldReturnOneOnePairWhenReceiveX1StringWithSpace)
{
    auto result = sut.convert(" x1");
    ASSERT_EQ(result, std::make_pair(float(1), 1));
}

TEST_F(TermConverterTestSuite, shouldReturnThreeTwoPairWhenReceive3X2String)
{
    auto result = sut.convert(" 3x2");
    ASSERT_EQ(result, std::make_pair(float(3), 2));
}

TEST_F(TermConverterTestSuite, shouldReturnMinusThreeTenPairWhenReceiveMinus3x10String)
{
    auto result = sut.convert(" -3x10");
    ASSERT_EQ(result, std::make_pair(float(-3), 10));
}

TEST_F(TermConverterTestSuite, shouldReturnMinusOneTenPairWhenReceiveMinus1x10String)
{
    auto result = sut.convert(" -x10");
    ASSERT_EQ(result, std::make_pair(float(-1), 10));
}

TEST_F(TermConverterTestSuite, shouldReturnPlusOneTenPairWhenReceiveMinus1x10String)
{
    auto result = sut.convert(" +x10 ");
    ASSERT_EQ(result, std::make_pair(float(1), 10));
}

TEST_F(TermConverterTestSuite, shouldReturnMinusFiftyThreeTenPairWhenReceiveMinus53x10String)
{
    auto result = sut.convert(" -53x10 ");
    ASSERT_EQ(result, std::make_pair(float(-53), 10));
}

TEST_F(TermConverterTestSuite, shouldConvertFloat)
{
    auto result = sut.convert(" -1.134 ");
    ASSERT_EQ(result, std::make_pair(float(-1.134), 0));
}

TEST_F(TermConverterTestSuite, shouldConvertFloat1)
{
    auto result = sut.convert(" 1.134 ");
    ASSERT_EQ(result, std::make_pair(float(1.134), 0));
}

TEST_F(TermConverterTestSuite, shouldConvertFloat2)
{
    auto result = sut.convert(" 0.134 ");
    ASSERT_EQ(result, std::make_pair(float(0.134), 0));
}

TEST_F(TermConverterTestSuite, shouldConvertFloat3)
{
    auto result = sut.convert(" -0.134 ");
    ASSERT_EQ(result, std::make_pair(float(-0.134), 0));
}

TEST_F(TermConverterTestSuite, shouldConvertFloat4)
{
    auto result = sut.convert(" 1.134x2 ");
    ASSERT_EQ(result, std::make_pair(float(1.134), 2));
}

TEST_F(TermConverterTestSuite, shouldConvertFloat5)
{
    auto result = sut.convert(" -1.134x2 ");
    ASSERT_EQ(result, std::make_pair(float(-1.134), 2));
}

TEST_F(TermConverterTestSuite, shouldConvertFloat6)
{
    auto result = sut.convert(" -0.134x2 ");
    ASSERT_EQ(result, std::make_pair(float(-0.134), 2));
}


TEST_F(TermConverterTestSuite, shouldConvertFloat7)
{
    auto result = sut.convert(" 0.134x2 ");
    ASSERT_EQ(result, std::make_pair(float(0.134), 2));
}
