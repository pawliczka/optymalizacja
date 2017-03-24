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
    auto result = sut.convert( "" );
    ASSERT_EQ( result, std::make_pair( 0, 0 ) );
}

TEST_F( SingleExpresionConventerTestSuite, shouldReturnZeroZeroPairWhenReceiveEmptyStringwithSpaces )
{
    auto result = sut.convert( "   " );
    ASSERT_EQ( result, std::make_pair( 0, 0 ) );
}

TEST_F( SingleExpresionConventerTestSuite, shouldReturnOneZeroPairWhenReceive1String )
{
    auto result = sut.convert( "1" );
    ASSERT_EQ( result, std::make_pair( 1, 0 ) );
}

TEST_F( SingleExpresionConventerTestSuite, shouldReturnOneZeroPairWhenReceive1StringWithSpace )
{
    auto result = sut.convert( " 1" );
    ASSERT_EQ( result, std::make_pair( 1, 0 ) );
}

TEST_F( SingleExpresionConventerTestSuite, shouldReturnOneOnePairWhenReceiveX1StringWithSpace )
{
    auto result = sut.convert( " x1" );
    ASSERT_EQ( result, std::make_pair( 1, 1 ) );
}

TEST_F( SingleExpresionConventerTestSuite, shouldReturnThreeTwoPairWhenReceive3X2String )
{
    auto result = sut.convert( " 3x2" );
    ASSERT_EQ( result, std::make_pair( 3, 2 ) );
}

TEST_F( SingleExpresionConventerTestSuite, shouldReturnMinusThreeTenPairWhenReceiveMinus3x10String )
{
    auto result = sut.convert( " -3x10" );
    ASSERT_EQ( result, std::make_pair( -3, 10 ) );
}

TEST_F( SingleExpresionConventerTestSuite, shouldReturnMinusFiftyThreeTenPairWhenReceiveMinus53x10String )
{
    auto result = sut.convert( " -53x10 " );
    ASSERT_EQ( result, std::make_pair( -53, 10 ) );
}
