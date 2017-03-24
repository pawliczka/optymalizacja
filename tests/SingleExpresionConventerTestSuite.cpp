#include "SingleExpresionConventer.hpp"
#include <gmock/gmock.h>

class SingleExpresionConventerTestSuite : public testing::Test
{
public:
    SingleExpresionConventerTestSuite() {}
    SingleExpresionConventer sut;
};

TEST_F( SingleExpresionConventerTestSuite, shouldReturnZeroZeroPairWhenReceiveEmptyString )
{
    std::string expresion = "";
    auto result = sut.convert( expresion );
    ASSERT_EQ( result, std::make_pair( 0, 0 ) );
}

TEST_F( SingleExpresionConventerTestSuite, shouldReturnZeroZeroPairWhenReceiveEmptyStringwithSpaces )
{
    std::string expresion = "   ";
    auto result = sut.convert( expresion );
    ASSERT_EQ( result, std::make_pair( 0, 0 ) );
}

TEST_F( SingleExpresionConventerTestSuite, shouldReturnOneZeroPairWhenReceive1String )
{
    std::string expresion = "1";
    auto result = sut.convert( expresion );
    ASSERT_EQ( result, std::make_pair( 1, 0 ) );
}

TEST_F( SingleExpresionConventerTestSuite, shouldReturnOneZeroPairWhenReceive1StringWithSpace )
{
    std::string expresion = " 1";
    auto result = sut.convert( expresion );
    ASSERT_EQ( result, std::make_pair( 1, 0 ) );
}

TEST_F( SingleExpresionConventerTestSuite, shouldReturnOneOnePairWhenReceiveX1StringWithSpace )
{
    std::string expresion = " x1";
    auto result = sut.convert( expresion );
    ASSERT_EQ( result, std::make_pair( 1, 1 ) );
}

TEST_F( SingleExpresionConventerTestSuite, shouldReturnThreeTwoPairWhenReceive3X2String )
{
    std::string expresion = " 3x2";
    auto result = sut.convert( expresion );
    ASSERT_EQ( result, std::make_pair( 3, 2 ) );
}

TEST_F( SingleExpresionConventerTestSuite, shouldReturnMinusThreeTenPairWhenReceiveMinus3x10String )
{
    std::string expresion = " -3x10";
    auto result = sut.convert( expresion );
    ASSERT_EQ( result, std::make_pair( -3, 10 ) );
}

TEST_F( SingleExpresionConventerTestSuite, shouldReturnMinusFiftyThreeTenPairWhenReceiveMinus53x10String )
{
    std::string expresion = " -53x10 ";
    auto result = sut.convert( expresion );
    ASSERT_EQ( result, std::make_pair( -53, 10 ) );
}
