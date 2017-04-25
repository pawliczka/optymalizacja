#include "EquationManager.hpp"
#include "EquationConventerMock.hpp"
#include <gmock/gmock.h>

using namespace testing;

class EquationManagerTestSuite : public testing::Test
{
public:
    EquationManagerTestSuite()
        : sut(m_equationConventerMock)
    {
    }

    std::shared_ptr<StrictMock<EquationConventerMock>> m_equationConventerMock =
        std::make_shared<StrictMock<EquationConventerMock>>();

    EquationManager sut;
};

TEST_F(EquationManagerTestSuite, init)
{
    EXPECT_CALL(*m_equationConventerMock, convert("x1+1=3x+5"));
    EXPECT_CALL(*m_equationConventerMock, convert("x1+2=3"));
    sut.convertToEquations("x1+1=3x+5\nx1+2=3");
}
