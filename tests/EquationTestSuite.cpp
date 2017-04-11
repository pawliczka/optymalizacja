#include "Equation.hpp"
#include <gmock/gmock.h>

class EquationTestSuite : public testing::Test
{
public:
    EquationTestSuite() {}
    Equation sut;
};

TEST_F(EquationTestSuite, shouldSetCoefficentEqualToOneOnIndexZero)
{
    unsigned int index = 0;
    int value = 1;
    sut.setCoefficient({value, index});
    ASSERT_EQ(sut.getCoefficient(index), value);
}


TEST_F(EquationTestSuite, shouldReturnNumericLimitsMaxAfterReceivingIndexOutOfRange)
{
    unsigned int indexOutOfRange = 1000;
    ASSERT_EQ(sut.getCoefficient(indexOutOfRange), std::numeric_limits<int>::max());
}

TEST_F(EquationTestSuite, shouldSetComparisonOperatorToEqual)
{
    sut.setComparisonOperator(ComparisonOperator::Equal);
    ASSERT_EQ(sut.getComparisonOperator(), ComparisonOperator::Equal);
}

TEST_F(EquationTestSuite, shouldReturnSevenAsLastIndexofCoefficientAfterReceivingSevenIndexAsTerm)
{
    sut.setCoefficient({1,7});
    ASSERT_EQ(sut.getIndexOfLastCofficient(), 7);
}
TEST_F(EquationTestSuite, shouldReturnTrueAfterComparingSameEquations)
{
    Equation equationFirst, equationSecond;
    equationFirst.setComparisonOperator(ComparisonOperator::GreaterEqual);
    equationFirst.setCoefficient({2, 15});
    equationFirst.setCoefficient({8, 57});
    equationSecond.setComparisonOperator(ComparisonOperator::GreaterEqual);
    equationSecond.setCoefficient({2, 15});
    equationSecond.setCoefficient({8, 57});
    ASSERT_EQ(equationFirst, equationSecond);
}

TEST_F(EquationTestSuite, shouldPrintProperString)
{
    sut = Equation({-2,-12,3,2},ComparisonOperator::GreaterEqual);
    EXPECT_EQ("2x3+3x2-12x1-2<=0",sut.toString());
}

