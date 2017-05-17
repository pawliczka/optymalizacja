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
    EXPECT_CALL(*m_equationConventerMock, convert("x_1+1=3x_+5"));
    EXPECT_CALL(*m_equationConventerMock, convert("x_1+2<=3"));
    sut.convertToEquations("x_1+1=3x_+5\nx_1+2<=3");
}

TEST_F(EquationManagerTestSuite, shouldReturnObjectiveFunction)
{
    auto objFun = Equation({-4, -2}, ComparisonOperator::Equal);
    auto conFun = Equation({-1, 1}, ComparisonOperator::LessEqual);

    EXPECT_CALL(*m_equationConventerMock, convert("x_1+1=3x_1+5")).WillOnce(Return(objFun));
    EXPECT_CALL(*m_equationConventerMock, convert("x_1+2<=3")).WillOnce(Return(conFun));
    sut.convertToEquations("x_1+1=3x_1+5\nx_1+2<=3");

    ASSERT_EQ(objFun, sut.getObjectiveFunction());
}

TEST_F(EquationManagerTestSuite, shouldReturnCorrectlyConstraintFunctions)
{
    auto objFun = Equation({-4, -2}, ComparisonOperator::Equal);
    auto conFun0 = Equation({-1, 1}, ComparisonOperator::LessEqual);
    auto conFun1 = Equation({-1, 1}, ComparisonOperator::LessEqual);
    auto conFun2 = Equation({-1, 1}, ComparisonOperator::LessEqual);

    EXPECT_CALL(*m_equationConventerMock, convert("x_1+1=3x_1+5")).WillOnce(Return(objFun));
    EXPECT_CALL(*m_equationConventerMock, convert("x_1+1<=0")).WillOnce(Return(conFun0));
    EXPECT_CALL(*m_equationConventerMock, convert("x_1+2<=0")).WillOnce(Return(conFun1));
    EXPECT_CALL(*m_equationConventerMock, convert("x_1+3<=0")).WillOnce(Return(conFun2));
    sut.convertToEquations("x_1+1=3x_1+5\nx_1+1<=0\nx_1+2<=0\nx_1+3<=0");

    auto conFuns = sut.getConstraintFunctions();
    ASSERT_EQ(conFun0, conFuns[0]);
    ASSERT_EQ(conFun1, conFuns[1]);
    ASSERT_EQ(conFun2, conFuns[2]);
}

TEST_F(EquationManagerTestSuite, shouldResizeFunctions)
{
    auto objFun = Equation({-4, -2}, ComparisonOperator::Equal);
    auto conFun0 = Equation({-1, 1, 0, 0, 1}, ComparisonOperator::LessEqual);
    auto objFunReturned = Equation({-4, -2, 0, 0, 0}, ComparisonOperator::Equal);

    EXPECT_CALL(*m_equationConventerMock, convert("x_1+1=3x_1+5")).WillOnce(Return(objFun));
    EXPECT_CALL(*m_equationConventerMock, convert("x_4+x_1-1<=0")).WillOnce(Return(conFun0));
    sut.convertToEquations("x_1+1=3x_1+5\nx_4+x_1-1<=0");

    ASSERT_EQ(objFunReturned, sut.getObjectiveFunction());
}
