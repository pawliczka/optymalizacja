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
    sut.setCoefficient({1, 7});
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

TEST_F(EquationTestSuite, shouldPrintEquationWithoutZeroCoefficients)
{
    sut = Equation({-2, -12, 3, 2}, ComparisonOperator::GreaterEqual);
    EXPECT_EQ("2x_3+3x_2-12x_1-2>=0", sut.toString());
}

TEST_F(EquationTestSuite, shouldPrintLastTermWithSign)
{
    sut = Equation({2, -12, 3, 2}, ComparisonOperator::GreaterEqual);
    EXPECT_EQ("2x_3+3x_2-12x_1+2>=0", sut.toString());
}

TEST_F(EquationTestSuite, shouldNotPrintEquationWithZeroCoefficients)
{
    sut = Equation({-2, -12, 0, 2}, ComparisonOperator::Equal);
    EXPECT_EQ("2x_3-12x_1-2=0", sut.toString());
}

TEST_F(EquationTestSuite, shouldNotPrintEquationWithZeroCoefficientsIndex0)
{
    sut = Equation({0, -12, 0, 2}, ComparisonOperator::GreaterEqual);
    EXPECT_EQ("2x_3-12x_1>=0", sut.toString());
}

TEST_F(EquationTestSuite, shouldNotPrintEquationWithZeroCoefficientsIndexLast)
{
    sut = Equation({0, -12}, ComparisonOperator::GreaterEqual);
    EXPECT_EQ("-12x_1>=0", sut.toString());
}

TEST_F(EquationTestSuite, pronto1)
{
    sut = Equation({0, -1}, ComparisonOperator::GreaterEqual);
    EXPECT_EQ("-x_1>=0", sut.toString());
}

TEST_F(EquationTestSuite, pronto2)
{
    sut = Equation({0, 1}, ComparisonOperator::GreaterEqual);
    EXPECT_EQ("x_1>=0", sut.toString());
}

TEST_F(EquationTestSuite, shouldNotPrintEquationCoefficientWithCoefficientOne)
{
    sut = Equation({1, -1, 1, 5,0,0,0,0,0,0,1}, ComparisonOperator::GreaterEqual);
    EXPECT_EQ("x_10+5x_3+x_2-x_1+1>=0", sut.toString());
}

TEST_F(EquationTestSuite, shouldCorrectlyConvertFloatCoefficionts)
{
    sut = Equation({0.1, -1.1, 1.32, 0.1123}, ComparisonOperator::GreaterEqual);
    auto result = sut.toString();
    EXPECT_EQ("0.1123x_3+1.32x_2-1.1x_1+0.1>=0", result);
}

TEST_F(EquationTestSuite, shouldCorrectlyConvertFloatCoefficiontsToStringWithResize)
{
    sut = Equation({0.1, -1.1, 1.32, 0.1123}, ComparisonOperator::GreaterEqual);
    sut.resizeEquation(10);
    auto result = sut.toString();
    EXPECT_EQ("+0.1123x_3+1.32x_2-1.1x_1+0.1>=0", result);
}

TEST_F(EquationTestSuite, shouldCorrectlyResizeEquation)
{
    sut = Equation({0.1, -1.1, 1.32}, ComparisonOperator::GreaterEqual);
    auto sut2 = Equation({0.1, -1.1, 1.32, 0, 0, 0}, ComparisonOperator::GreaterEqual);
    EXPECT_EQ(2, sut.getIndexOfLastCofficient());
    sut.resizeEquation(5);
    EXPECT_EQ(5, sut.getIndexOfLastCofficient());
    EXPECT_EQ(sut, sut2);
}

TEST_F(EquationTestSuite, shouldClearAllCoefficients)
{
    sut = Equation({1, -1, 14}, ComparisonOperator::GreaterEqual);

    EXPECT_EQ(1,sut.getCoefficient(0));
    EXPECT_EQ(-1,sut.getCoefficient(1));
    EXPECT_EQ(14.,sut.getCoefficient(2));

    sut.clear();

    EXPECT_EQ(0,sut.getCoefficient(0));
    EXPECT_EQ(0,sut.getCoefficient(1));
    EXPECT_EQ(0,sut.getCoefficient(2));
    EXPECT_EQ(ComparisonOperator::None,sut.getComparisonOperator());
}
