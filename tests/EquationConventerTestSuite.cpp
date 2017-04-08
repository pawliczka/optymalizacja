#include "EquationConventer.hpp"
#include "TermConverterMock.hpp"
#include "Equation.hpp"
#include <gmock/gmock.h>
#include <list>
#include <memory>
#include <iostream>

using namespace testing;

namespace
{
    std::ostream& operator<<(std::ostream& stream, Equation const& equation)
    {
        for(int i=equation.getIndexOfLastCofficient();i>=0;i--)
            stream << equation.getCoefficient(i)<<"x"<<i<<" ";
    }
}

class EquationConventerTestSuite : public Test
{
    using ExpectCallsList = std::list<std::pair<std::string, Term>>;

public:
    EquationConventerTestSuite()
        : sut(termConverter)
    {
        EXPECT_CALL(*termConverter,convert("")).WillRepeatedly(Return(Term(0,0)));
    }
    std::shared_ptr<TermConverterMock> termConverter = std::make_shared<testing::StrictMock<TermConverterMock>>();
    EquationConventer sut;
    Equation equation;

    void expectTermConverterCalls(ExpectCallsList expectCallsList)
    {
        for (const auto& expectCall : expectCallsList)
        {
            EXPECT_CALL(*termConverter, convert(expectCall.first)).WillOnce(Return(expectCall.second));
        }
    }
};

TEST_F(EquationConventerTestSuite, ZeroEqualZero)
{
    EXPECT_CALL(*termConverter,convert("0")).Times(2).WillRepeatedly(Return(Term({0,0})));
    equation.setComparisonOperator(ComparisonOperator::Equal);
    equation.setCoefficient({0,0});
    ASSERT_EQ(equation,sut.convert(("0=0")));
}

TEST_F(EquationConventerTestSuite, ZeroOnTheRightSide)
{
    expectTermConverterCalls({{"2x3", Term(2, 3)}, {"-2x2", Term(-2, 2)}, {"x1", Term(1, 1)}, {"1", Term(1, 0)}});
    expectTermConverterCalls({{"0", Term(0,0)}});
    equation.setComparisonOperator(ComparisonOperator::GreaterEqual);
    equation.setCoefficient({1,0});
    equation.setCoefficient({1,1});
    equation.setCoefficient({-2,2});
    equation.setCoefficient({2,3});
    ASSERT_EQ(equation,sut.convert("2x3-2x2+x1+1>=0"));
}

TEST_F(EquationConventerTestSuite, SevenOnTheRightSide)
{
    expectTermConverterCalls({{"2x3", Term(2, 3)},
                              {"-2x2", Term(-2, 2)}, \
                              {"x1", Term(1, 1)},
                              {"1", Term(1, 0)}});
    expectTermConverterCalls({{"7", Term(7,0)}});
    equation.setComparisonOperator(ComparisonOperator::GreaterEqual);
    equation.setCoefficient({-6,0});
    equation.setCoefficient({1,1});
    equation.setCoefficient({-2,2});
    equation.setCoefficient({2,3});
    ASSERT_EQ(equation,sut.convert("2x3-2x2+x1+1>=7"));
}

TEST_F(EquationConventerTestSuite, MinusSevenOnTheRightSide)
{
    expectTermConverterCalls({{"2x3", Term(2, 3)},
                              {"-2x2", Term(-2, 2)}, \
                              {"x1", Term(1, 1)},
                              {"1", Term(1, 0)}});
    expectTermConverterCalls({{"-7", Term(-7,0)}});
    equation.setComparisonOperator(ComparisonOperator::GreaterEqual);
    equation.setCoefficient({8,0});
    equation.setCoefficient({1,1});
    equation.setCoefficient({-2,2});
    equation.setCoefficient({2,3});
    ASSERT_EQ(equation,sut.convert("2x3-2x2+x1+1>=-7"));
}

TEST_F(EquationConventerTestSuite, WyjebaneWKosmosRownanko)
{
    expectTermConverterCalls({{"2x3", Term(2, 3)},
                              {"-2x2", Term(-2, 2)},
                              {"x1", Term(1, 1)},
                              {"1", Term(1, 0)},
                              {"-3x6", Term(-3,6)},
                              {"-3x2", Term(-3,2)},
                              {"5x1", Term(5,1)},
                              {"-4", Term(-4,0)}});
    equation.setComparisonOperator(ComparisonOperator::GreaterEqual);
    equation.setCoefficient({5,0});
    equation.setCoefficient({-4,1});
    equation.setCoefficient({1,2});
    equation.setCoefficient({2,3});
    equation.setCoefficient({3,6});

    ASSERT_EQ(equation,sut.convert("2x3-2x2+x1+1>=-3x6-3x2+5x1-4"));
}
