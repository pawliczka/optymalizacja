#include "EquationConventerMock.hpp"
#include "EquationManager.hpp"
#include <gmock/gmock.h>

using namespace testing;

class EquationManagerTestSuite : public testing::Test
{
public:
    EquationManagerTestSuite() : sut(m_equationConventerMock)
    {
    }

    std::shared_ptr<StrictMock<EquationConventerMock>> m_equationConventerMock =
        std::make_shared<StrictMock<EquationConventerMock>>();

    EquationManager sut;
};

TEST_F(EquationManagerTestSuite, shouldSplitEquationsByNewLineSign)
{
    EXPECT_CALL(*m_equationConventerMock, convert("x1+1=3x+5"));
    EXPECT_CALL(*m_equationConventerMock, convert("x1+2<=3"));
    sut.convertToEquations("x1+1=3x+5\nx1+2<=3");
}

TEST_F(EquationManagerTestSuite, shouldReturnObjectiveFunction)
{
    auto objFun = Equation({-4, -2}, ComparisonOperator::Equal);
    auto conFun = Equation({-1, 1}, ComparisonOperator::LessEqual);

    EXPECT_CALL(*m_equationConventerMock, convert("x1+1=3x1+5")).WillOnce(Return(objFun));
    EXPECT_CALL(*m_equationConventerMock, convert("x1+2<=3")).WillOnce(Return(conFun));
    sut.convertToEquations("x1+1=3x1+5\nx1+2<=3");

    ASSERT_EQ(objFun, sut.getObjectiveFunction());
}

TEST_F(EquationManagerTestSuite, shouldReturnCorrectlyConstraintFunctions)
{
    auto objFun = Equation({-4, -2}, ComparisonOperator::Equal);
    auto conFun0 = Equation({-1, 1}, ComparisonOperator::LessEqual);
    auto conFun1 = Equation({-1, 1}, ComparisonOperator::LessEqual);
    auto conFun2 = Equation({-1, 1}, ComparisonOperator::LessEqual);

    EXPECT_CALL(*m_equationConventerMock, convert("x1+1=3x1+5")).WillOnce(Return(objFun));
    EXPECT_CALL(*m_equationConventerMock, convert("x1+1<=0")).WillOnce(Return(conFun0));
    EXPECT_CALL(*m_equationConventerMock, convert("x1+2<=0")).WillOnce(Return(conFun1));
    EXPECT_CALL(*m_equationConventerMock, convert("x1+3<=0")).WillOnce(Return(conFun2));
    sut.convertToEquations("x1+1=3x1+5\nx1+1<=0\nx1+2<=0\nx1+3<=0");

    auto conFuns = sut.getConstraintFunctions();
    ASSERT_EQ(conFun0, *conFuns[0]);
    ASSERT_EQ(conFun1, *conFuns[1]);
    ASSERT_EQ(conFun2, *conFuns[2]);
}
