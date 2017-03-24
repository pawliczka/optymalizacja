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

